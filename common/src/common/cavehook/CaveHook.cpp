#include "CaveHook.h"

#include <hde64.h>
#include "Allocator.h"

int lastError = 0;

BYTE* CreateDirectJmp(ULONG_PTR target) {
   BYTE* buffer = new BYTE[14];
   buffer[0] = 0xFF;
   buffer[1] = 0x25;
   buffer[2] = 0x00;
   buffer[3] = 0x00;
   buffer[4] = 0x00;
   buffer[5] = 0x00;
   memcpy(buffer + 6, &target, sizeof(target));

   return buffer;
}

bool PlaceDetourJmp(ULONG_PTR target, LPVOID detour) {
   DWORD oldProtect;
   VirtualProtect(reinterpret_cast<LPVOID>(target), 6, PAGE_EXECUTE_READWRITE, &oldProtect);

   LPVOID readdress = VirtualAlloc(FindFreeRegion(reinterpret_cast<LPVOID>(target)), 15, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
   if (!readdress) {
       lastError = BUFFER_NOT_ALLOCATED;
       return false;
   }
   memcpy(readdress, CreateDirectJmp(reinterpret_cast<ULONG_PTR>(detour)), 14);

   *reinterpret_cast<BYTE*>(target) = 0xE9;
   *reinterpret_cast<DWORD*>(target + 1) = reinterpret_cast<DWORD>(readdress) - static_cast<DWORD>(target) - 5;

   VirtualProtect(reinterpret_cast<LPVOID>(target), 6, oldProtect, &oldProtect);
   return true;
}

std::vector<BYTE> FindPrologue(ULONG_PTR address, SIZE_T jmpLength) {
   BYTE* data = reinterpret_cast<BYTE*>(address);
   SIZE_T prologueLength = 0;
   SIZE_T offset = 0;

   while (prologueLength < jmpLength) {
       hde64s hs;
       unsigned int instructionLength = hde64_disasm(data + offset, &hs);

       if (hs.flags & F_ERROR) {
           break;
       }

       prologueLength += instructionLength;
       offset += instructionLength;
   }

   std::vector<BYTE> buffer(prologueLength);
   memcpy(buffer.data(), reinterpret_cast<LPCVOID>(address), prologueLength);

   return buffer;
}

bool IsRipRelativeInstruction(const hde64s& hs) {
   if (!(hs.flags & F_MODRM)) return false;

   if (hs.modrm_mod == 0 && hs.modrm_rm == 5) {
       return true;
   }

   return false;
}

bool IsRelativeJump(const hde64s& hs) {
   BYTE opcode = hs.opcode;

   if (opcode == 0xE9 || opcode == 0xEB) return true;

   if (opcode >= 0x70 && opcode <= 0x7F) return true;

   if (hs.opcode2) {
       if (hs.opcode2 >= 0x80 && hs.opcode2 <= 0x8F) return true;
   }

   return false;
}

void RelocateInstructions(ULONG_PTR oldAddress, LPVOID trampoline, SIZE_T prologueLength) {
   BYTE* data = reinterpret_cast<BYTE*>(trampoline);
   SIZE_T offset = 0;

   while (offset < prologueLength) {
       hde64s hs;
       unsigned int instructionLength = hde64_disasm(data + offset, &hs);

       if (hs.flags & F_ERROR) {
           break;
       }

       if (IsRipRelativeInstruction(hs)) {
           ULONG_PTR currentRip = reinterpret_cast<ULONG_PTR>(trampoline) + offset;
           ULONG_PTR oldRip = oldAddress + offset;

           LONG displacement = 0;
           if (hs.flags & F_DISP32) {
               displacement = static_cast<LONG>(hs.disp.disp32);
           }

           ULONG_PTR calculatedValue = oldRip + displacement + instructionLength;
           DWORD result = static_cast<DWORD>(calculatedValue - currentRip - instructionLength);

           SIZE_T dispOffset = offset;
           if (hs.flags & F_MODRM) dispOffset += 2;
           if (hs.flags & F_SIB) dispOffset += 1;

           memcpy(reinterpret_cast<LPVOID>(reinterpret_cast<ULONG_PTR>(trampoline) + dispOffset), &result, sizeof(result));
       }
       else if (IsRelativeJump(hs)) {
           LONG originalDisplacement = 0;

           if (hs.flags & F_IMM8) {
               originalDisplacement = static_cast<LONG>(static_cast<signed char>(hs.imm.imm8));
           }
           else if (hs.flags & F_IMM32) {
               originalDisplacement = static_cast<LONG>(hs.imm.imm32);
           }

           ULONG_PTR originalTarget = oldAddress + offset + instructionLength + originalDisplacement;
           ULONG_PTR newRip = reinterpret_cast<ULONG_PTR>(trampoline) + offset;
           LONG newDisplacement = static_cast<LONG>(originalTarget - newRip - instructionLength);

           SIZE_T immOffset = offset + 1;
           if (hs.opcode2) immOffset += 1;

           if (hs.flags & F_IMM8) {
               if (newDisplacement >= -128 && newDisplacement <= 127) {
                   signed char shortDisp = static_cast<signed char>(newDisplacement);
                   memcpy(reinterpret_cast<LPVOID>(reinterpret_cast<ULONG_PTR>(trampoline) + immOffset), &shortDisp, 1);
               }
           }
           else if (hs.flags & F_IMM32) {
               memcpy(reinterpret_cast<LPVOID>(reinterpret_cast<ULONG_PTR>(trampoline) + immOffset), &newDisplacement, sizeof(newDisplacement));
           }
       }

       offset += instructionLength;
   }
}

bool CreateTrampoline(ULONG_PTR target, std::vector<BYTE>& prologue, LPVOID* lpTrampoline) {
   LPVOID trampoline = VirtualAlloc(FindFreeRegion(reinterpret_cast<LPVOID>(target)), prologue.size() + 14, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
   if (!trampoline) {
       lastError = BUFFER_NOT_ALLOCATED;
       return false;
   }

   memcpy(trampoline, prologue.data(), prologue.size());
   memcpy(reinterpret_cast<LPVOID>(reinterpret_cast<ULONG_PTR>(trampoline) + prologue.size()), CreateDirectJmp(target + prologue.size()), 14);
   *lpTrampoline = trampoline;

   return true;
}

bool CaveHookEx(ULONG_PTR target, LPVOID detour, LPVOID* original, HOOK_DATA* hookData) {
   std::vector<BYTE> prologue = FindPrologue(target, 5);
   if (!PlaceDetourJmp(target, detour))
       return false;

   LPVOID trampoline;
   if (!CreateTrampoline(target, prologue, &trampoline))
       return false;

   RelocateInstructions(target, trampoline, prologue.size());

   if (original)
       *original = trampoline;

   hookData->Target = target;
   hookData->Detour = detour;
   hookData->Trampoline = trampoline;
   hookData->Prologue = prologue;

   return true;
}

bool CaveHook(ULONG_PTR target, LPVOID detour, LPVOID* original) {
   HOOK_DATA ignored{};
   return CaveHookEx(target, detour, original, &ignored);
}

int CaveLastError() {
   return lastError;
}

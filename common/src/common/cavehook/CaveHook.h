#pragma once

#include <Windows.h>
#include <vector>
#include "Errors.h"

typedef struct HOOK_DATA_ {
    ULONG_PTR Target;
    LPVOID Detour;
    LPVOID Trampoline;
    std::vector<BYTE> Prologue;
} HOOK_DATA, *PHOOK_DATA, *LPHOOK_DATA;

bool CaveHookEx(ULONG_PTR target, LPVOID detour, LPVOID* original, HOOK_DATA* hookData);

bool CaveHook(ULONG_PTR target, LPVOID detour, LPVOID* original);

int CaveLastError();

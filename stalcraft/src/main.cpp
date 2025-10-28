#include <Windows.h>
#include <cheat/stalcraft.h>

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID keyEncrypted) {
    if (reason == DLL_PROCESS_ATTACH) {
        stalcraft* cheat = new stalcraft;
        const int code = cheat->start();

        return code;
    }

    return TRUE;
}

#include "process.h"

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

namespace common::util {

    pid_t pid_by_name(const std::string_view& name) {
        pid_t id = 0;
        if (const handle tlhelp_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0)) {
            PROCESSENTRY32 process_entry{};
            process_entry.dwSize = sizeof(process_entry);
            if (!Process32First(tlhelp_handle, &process_entry))
                goto exit;

            do {
                if (process_entry.szExeFile == name) {
                    id = process_entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(tlhelp_handle, &process_entry));

exit:
            CloseHandle(tlhelp_handle);
        }

        return id;
    }

    std::optional<module_t> find_module(pid_t pid, const std::string_view& name) {
        std::optional<module_t> module = std::nullopt;

        if (const handle tlhelp_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, pid)) {
            MODULEENTRY32 module_entry{};
            module_entry.dwSize = sizeof(module_entry);
            if (!Module32First(tlhelp_handle, &module_entry))
                goto exit;

            do {
                if (module_entry.szModule == name) {
                    module = { module_entry.modBaseAddr, module_entry.modBaseSize };
                    break;
                }
            } while (Module32Next(tlhelp_handle, &module_entry));

exit:
            CloseHandle(tlhelp_handle);
        }

        return module;
    }
}

#include "windows_impl.h"

#include <Windows.h>
#include <stdexcept>
#include <common/util/process.h>

namespace common {

    windows_memory::windows_memory(pid_t process_id) : process_handle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id)) {
        if (process_id == 0 || process_id == 1)
            throw std::invalid_argument("Invalid process id");

        if (process_handle == invalid_handle)
            throw std::invalid_argument("Invalid process handle");
    }

    windows_memory::windows_memory(const std::string_view& name) : windows_memory(util::pid_by_name(name)) {}

    windows_memory::~windows_memory() {
        if (process_handle != invalid_handle)
            CloseHandle(process_handle);
    }

    bool windows_memory::read_raw(ptr address, ptr buffer, size_t size) {
        size_t read;
        return ReadProcessMemory(process_handle, address, buffer, size, &read);
    }

    pid_t windows_memory::pid() {
        return GetProcessId(process_handle);
    }

    handle windows_memory::raw_handle() const {
        return process_handle;
    }
}

#pragma once

#include <string_view>
#include <common/memory/memory.h>

namespace common {

    /**
     * Представляет управление памятью через Win32 API
     */
    class windows_memory final : public memory {
    public:
        explicit windows_memory(pid_t process_id);

        explicit windows_memory(const std::string_view& name);

        ~windows_memory() override;
    public:
        bool read_raw(ptr address, ptr buffer, size_t size) override;

        pid_t pid() override;
    public:
        /**
         * Возвращает сырой handle на процесс
         *
         * @return Handle процесса
         */
        handle raw_handle() const;
    private:
        handle process_handle;
    };
}

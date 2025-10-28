#pragma once

#include <string_view>
#include <optional>

namespace common {

    /**
     * @brief Представляет структуру, описывающую модуль
     */
    struct module_t {
        ptr base; ///< Адрес на начало модуля
        size_t size; ///< Размер модуля
    };
}

namespace common::util {

    /**
     * @brief Ищет идентификатор процесса по имени
     *
     * @param name Имя процесса
     * @return ID процесса если нашел, иначе 0
     */
    pid_t pid_by_name(const std::string_view& name);

    /**
     * @brief Ищет модуль в удаленном процессе
     *
     * @param pid Идентификатор процесса
     * @param name Имя модуля
     * @return `std::optional<module_t>` с найденным модулем или пустой, если не нашел
     */
    std::optional<module_t> find_module(pid_t pid, const std::string_view& name);
}

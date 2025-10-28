#pragma once

#include <string>
#include <vector>
#include <optional>
#include <common/memory/remote_ptr.h>
#include <common/memory/local_ptr.h>
#include <source/schema/c_schema_class.h>

namespace source {

    /**
     * @brief Представляет модуль в schemasystem
     */
    class c_type_scope {
    public:
        /**
         * @brief Возвращает имя модуля
         *
         * @return Имя модуля в виде `std::string`
         */
        std::string name() const;

        /**
         * @brief Ищет класс в модуле
         *
         * @param string Имя класса
         * @return `std::optional<common::remote_ptr<c_schema_class>>` с найденным классом или пустой, если не найдено
         */
        std::optional<common::remote_ptr<c_schema_class>> get(const std::string_view& string) const;

        /**
         * @brief Возвращает список классов
         *
         * @return Список из `common::remote_ptr<c_schema_class>` в виде `std::vector`
         */
        std::vector<common::remote_ptr<c_schema_class>> classes() const;
    private:
        struct c_declared_class {
            ptr vtable; ///< Виртуальная таблица функций
            cstr name; ///< Название класса
            common::local_ptr<c_type_scope> owner; ///< Указатель на модуль
            ptr unknown;
            common::remote_ptr<c_schema_class> class_ptr; ///< Указатель на класс
        };

        struct c_declared_entry {
            qword hash[2]; ///< Хеш
            common::remote_ptr<c_declared_class> declared_class; ///< Указатель на задекларированный класс
        };
    };
}

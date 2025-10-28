#pragma once

#include <string>
#include <vector>
#include <optional>
#include <source/schema/c_schema_field.h>

namespace source {

    /**
     * @brief Представляет класс в schemasystem
     */
    class c_schema_class {
    public:
        c_schema_class();
    public:
        /**
         * @brief Возвращает имя класса
         *
         * @return Имя класса в виде `std::string`
         */
        std::string name() const;

        /**
         * @brief Возвращает имя модуля
         *
         * @return Имя модуля в виде `std::string`
         */
        std::string scope_name() const;

        /**
         * @brief Ищет поле в классе
         *
         * @param string Имя поля
         * @return `std::optional<c_schema_field>` с найденным полем или пустой, если не найдено
         */
        std::optional<c_schema_field> field(const std::string_view& string) const;

        /**
         * @brief Возвращает поля в классе
         *
         * @return Список из `c_schema_field` в виде `std::vector`
         */
        std::vector<c_schema_field> fields() const;
    private:
        ptr vtable; ///< Виртуальная таблица функций
        ptr name_ptr; ///< Указатель на имя класса
        ptr scope_name_ptr; ///< Указатель на имя модуля
        dword size; ///< Размер класса
        word field_count; ///< Количество полей
        word unknown0;
        word unknown1;
        word unknown2;
        dword unknown3;
        ptr declared_fields; ///< Указатель на поля
    };
}

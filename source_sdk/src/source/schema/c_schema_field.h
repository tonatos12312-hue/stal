#pragma once

#include <string>

namespace source {

    /**
     * @brief Представляет поле в классе
     */
    class c_schema_field {
    public:
        c_schema_field();
    public:
        /**
         * @brief Возвращает имя поля
         *
         * @return Имя поля в виде `std::string`
         */
        std::string name() const;

        /**
         * @brief Возвращает имя владельца
         *
         * @return Имя класса в виде `std::string`
         */
        std::string owner() const;

        /**
         * @brief Возвращает смещение поля внутри структуры
         *
         * @return Смещение в байтах от начала класса
         */
        dword offset() const;
    private:
        ptr name_ptr; ///< Указатель на имя поля
        ptr owner_name_ptr; ///< Указатель на имя класса владельца
        dword memory_offset; ///< Смещение в памяти
        dword metadata_size;
        ptr metadata;
    };
}

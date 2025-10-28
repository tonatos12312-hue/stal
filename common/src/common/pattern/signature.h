#pragma once

#include <string_view>
#include <common/memory/remote_ptr.h>
#include <common/util/process.h>

#define hex_character_to_byte(character) (character >= '0' && character <= '9' ? character - '0' : character >= 'A' && character <= 'F' ? character - 'A' + 10 : character >= 'a' && character <= 'f' ? character - 'a' + 10 : 0)

namespace common {

    /**
     * @brief Представляет поиск и обработку сигнатур в удаленном процессе
     */
    class signature {
    public:
        signature();

        explicit signature(const std::string_view& string);
    public:
        /**
         * @brief Ищет сигнатуру по адресу `base` с размером региона `size`
         *
         * @param base Адрес в удаленном процессе
         * @param size Размер региона для поиска
         * @return `signature&` Ссылка на обновленный signature
         */
        signature& find(ptr base, size_t size);

        /**
         * @brief Ищет сигнатуру в модуле процесса
         *
         * @param module Модуль в удаленном процессе
         * @return `signature&` Ссылка на обновленный signature
         */
        signature& find(module_t module);
    public:
        /**
         * @brief Возвращает адрес последней найденной сигнатуры
         *
         * @return Адрес в удаленном процессе
         */
        qword address() const;

        /**
         * @brief Возвращает удаленный указатель на адрес найденной сигнатуры
         *
         * @return Умный указатель в виде `common::remote_ptr<ptr>`
         */
        remote_ptr<ptr> remote() const;

        /**
         * @brief Указывает, найдена ли сигнатура
         * 
         * @return `true`, если сигнатура нашлась
         */
        bool is_found() const;

        /**
         * @brief Высчитывает конечный адрес displacement 32
         *
         * Пример для сигнатуры:
         * 48 8B 05 43 3D 01 00    mov rax, cs:some_addr
         * Функция автоматически высчитывает `some_addr`
         *
         * @param opcode_length Длина опкода инструкции до оффсета
         * @return Итоговый адрес
         */
        qword resolve_disp32(int opcode_length) const;
    private:
        struct Data {
            byte buffer[256];
            size_t size = 0;
        };

        /**
         * @brief Переводит строку состоящую из байтов и wildcard (? или ??) в массив байтов
         *
         * @param string Строка
         * @return Массив `buffer` и `size` размер массива
         */
        static constexpr auto hex_to_bytes(const std::string_view string) {
            Data result;
            for (size_t i = 0; i < string.length() && result.size < 256; i++) {
                if (string[i] == '?') {
                    result.buffer[result.size++] = 0xFF;
                    if (i + 1 < string.length() && string[i + 1] == '?')
                        i++;

                    i++;
                    continue;
                }

                if (i + 1 >= string.length())
                    break;

                result.buffer[result.size++] = (hex_character_to_byte(string[i]) << 4) | hex_character_to_byte(string[i + 1]);
                i += 2;
            }

            return result;
        }

        Data data; ///< Буфер байтов и его размер
        qword found_address; ///< Найденный адрес в удаленном процессе
    };
}

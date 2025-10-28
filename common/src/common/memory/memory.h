#pragma once

namespace common {

    /**
     * @brief Предоставляет управление памятью
     */
    class memory {
    public:
        virtual ~memory() = default;
    public:
        /**
         * @brief Считывает данные в буффер по адресу
         *
         * @param address Адрес в удаленном процессе
         * @param buffer Буффер
         * @param size Размер данных
         * @return `true` если успешно считалось
         */
        virtual bool read_raw(ptr address, ptr buffer, size_t size) = 0;

        /**
         * @brief Возвращает идентификатор процесса
         *
         * @return id процесса
         */
        virtual pid_t pid() = 0;
    public:
        /**
         * @brief Считывает данные в объект
         *
         * @tparam T Тип объекта
         * @param address Адрес в удаленном процессе
         * @return Объект типа `T`
         */
        template<typename T>
        T read(ptr address) {
            T buffer;
            read_raw(address, &buffer, sizeof(T));

            return buffer;
        }

        /**
         * @brief Считывает данные в объект
         *
         * @tparam T Тип объекта
         * @param address Адрес в удаленном процессе
         * @return Объект типа `T`
         */
        template<typename T>
        T read(const qword address) {
            return read<T>(reinterpret_cast<ptr>(address));
        }
    };
}

namespace shared {
    inline extern common::memory* memory = nullptr; ///< Общий указатель на `common::memory*`
}

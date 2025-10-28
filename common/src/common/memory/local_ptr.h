#pragma once

#include <common/memory/memory.h>

namespace common {

    /**
     * @brief Умный указатель на объект в локальной памяти (AKA локальный указатель)
     *
     * Предоставляет интерфейс, похожий на обычный указатель,
     * но читает данные из локального экземпляра объекта
     *
     * @tparam T Тип объекта
     */
    template<typename T>
    class local_ptr {
    public:
        local_ptr() = default;

        /**
         * @brief Создает локальный указатель
         *
         * @param address Адрес объекта
         */
        explicit local_ptr(ptr address) : address(address) {}

        /**
         * @brief Создает локальный указатель
         *
         * @param address Адрес объекта
         */
        explicit local_ptr(qword address) : local_ptr(reinterpret_cast<ptr>(address)) {}
    public:
        /**
         * @brief Возвращает адрес объекта
         *
         * @return ptr Адрес объекта
         */
        ptr get() const {
            return address;
        }

        /**
         * @brief Возвращает новый локальный указатель с другим типом
         *
         * @tparam U Тип трансформации
         * @return `local_ptr` с типом `U`
         */
        template<typename U>
        local_ptr<U> cast() const {
            return local_ptr<U>(address);
        }
    public:
        /**
         * @brief Читает объект по адресу
         *
         * @return T Копия объекта `T`, прочитанного из памяти
         */
        T operator*() const {
            return shared::memory->read<T>(address);
        }

        /**
         * @brief Оператор -> для доступа к членам объекта
         *
         * @return `T*` Указатель на объект `T`
         */
        T* operator->() const {
            return static_cast<T*>(address);
        }

        /**
          * @brief Возвращает новый `local_ptr`, сдвинутый на число
          *
          * @param offset Число байт смещения
          * @return `local_ptr` Новый указатель, сдвинутый на `offset`
          */
        local_ptr operator+(qword offset) const {
            return local_ptr(address + offset);
        }

        /**
          * @brief Смещает текущий указатель на число
          *
          * @param offset Число байт смещения
          * @return `local_ptr&` Ссылка на обновленный указатель
          */
        local_ptr& operator+=(qword offset) {
            address += offset;
            return *this;
        }

        /**
         * @brief Индексация как у массива
         *
         * Вызывает `operator[]` на объекте `T`
         *
         * @param index Индекс элемента
         * @return auto Элемент
         */
        auto operator[](size_t index) const {
            return (*this)->operator[](index);
        }
    private:
        ptr address; ///< Адрес объекта в памяти процесса
    };
}

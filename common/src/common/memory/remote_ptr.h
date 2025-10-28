#pragma once

#include <common/memory/memory.h>

namespace common {

    /**
     * @brief Прокси для удаленного объекта.
     *
     * Позволяет обращаться к объекту типа `T`, расположенного в памяти
     * удаленного процесса, через оператор `->` и `->*`, кэшируя локальную копию
     *
     * @tparam T Тип удаленного объекта
     */
    template<typename T>
    class remote_proxy {
    public:
        /**
         * @brief Создает прокси для удаленного объекта
         *
         * @param address Адрес объекта в памяти удаленного процесса
         */
        explicit remote_proxy(ptr address) : address(address) {}
    public:
        /**
         * @brief Доступ к члену удаленного объекта через указатель на член
         *
         * @tparam U Тип члена `U T::*`
         * @param member Указатель на член класса `T`
         * @return Ссылка на член объекта
         */
        template<typename U>
        const U& operator->*(U T::*member) const {
            ensure_cached();
            return cached_object.*member;
        }

        /**
         * @brief Оператор -> для доступа к членам объекта
         *
         * @return T* Указатель на закешированный объект
         */
        T* operator->() const {
            ensure_cached();
            return &cached_object;
        }

        /**
         * @brief Преобразование в копию удаленного объекта
         *
         * Читает объект из памяти процесса и возвращает его копию
         *
         * @return T Кэшированная копия удаленного объекта
         */
        explicit operator T() const {
            ensure_cached();
            return cached_object;
        }
    private:
        /**
         * @brief Читает объект из удаленной памяти, если он еще не закеширован
         */
        void ensure_cached() const {
            if (!is_cached) {
                cached_object = shared::memory->read<T>(address);
                is_cached = true;
            }
        }
    private:
        ptr address; ///< Адрес объекта в памяти процесса
        mutable T cached_object; ///< Локальная закешированная копия удаленного объекта
        mutable bool is_cached = false; ///< Флаг, указывающий, закеширована ли копия
    };

    /**
     * @brief Умный указатель на объект в удаленной памяти (AKA удаленный указатель)
     *
     * Предоставляет интерфейс похожий на обычный указатель,
     * но читает данные из памяти удаленного процесса
     *
     * @tparam T Тип объекта
     */
    template<typename T>
    class remote_ptr {
    public:
        remote_ptr() = default;

        /**
         * @brief Создает указатель на удаленный объект
         *
         * @param address Адрес объекта в памяти удаленного процесса
         */
        explicit remote_ptr(ptr address) : address(address) {}

        /**
         * @brief Создает указатель на удаленный объект
         *
         * @param address Адрес объекта в памяти удаленного процесса
         */
        explicit remote_ptr(qword address) : remote_ptr(reinterpret_cast<ptr>(address)) {}
    public:
        /**
         * @brief Возвращает адрес в удаленном процессе
         *
         * @return ptr Адрес в памяти
         */
        ptr get() const {
            return address;
        }

        /**
         * @brief Возвращает новый удаленный указатель с другим типом
         *
         * @tparam U Тип трансформации
         * @return `remote_ptr` с типом `U`
         */
        template<typename U>
        remote_ptr<U> cast() const {
            return remote_ptr<U>(address);
        }
    public:
        /**
         * @brief Читает объект из памяти
         *
         * @return T Копия объекта `T`
         */
        T operator*() const {
            return shared::memory->read<T>(address);
        }

        /**
         * @brief Возвращает прокси для доступа к членам объекта
         *
         * @return `remote_proxy<T>` Прокси для работы с удаленным объектом
         */
        remote_proxy<T> operator->() const {
            return remote_proxy<T>(address);
        }

        /**
         * @brief Возвращает новый `remote_ptr`, сдвинутый на число
         *
         * @param offset Число байт смещения
         * @return `remote_ptr` Новый указатель, сдвинутый на `offset`
         */
        remote_ptr operator+(qword offset) const {
            return remote_ptr(address + offset);
        }

        /**
         * @brief Смещает текущий указатель на число
         *
         * @param offset Число байт смещения
         * @return `remote_ptr&` Ссылка на обновленный указатель
         */
        remote_ptr& operator+=(qword offset) {
            address += offset;
            return *this;
        }

        /**
         * @brief Индексация как у массива
         *
         * Вызывает `operator[]` на удаленном объекте
         *
         * @param index Индекс элемента
         * @return auto Элемент
         */
        auto operator[](size_t index) const {
            return (*this)->operator[](index);
        }

        /**
         * @brief Итератор на начало контейнера
         *
         * @return auto Итератор, указывающий на первый элемент
         */
        auto begin() const {
            return (*this)->begin();
        }

        /**
         * @brief Итератор на конец контейнера
         *
         * @return auto Итератор, указывающий на элемент за последним
         */
        auto end() const {
            return (*this)->end();
        }
    private:
        ptr address; ///< Адрес объекта в памяти процесса
    };
}

#pragma once

#include <common/memory/memory.h>

namespace source {

    /**
     * @brief Представляет управление списком из `CUtlVector` в source2
     *
     * @tparam T Тип элемента
     */
    template<typename T>
    class c_utl_vector final {
    public:
        c_utl_vector() = default;
    public:
        /**
         * @brief Возвращает количество элементов
         *
         * @return Количество элементов в списке
         */
        size_t size() const {
            return shared::memory->read<size_t>(reinterpret_cast<qword>(this));
        }
    public:
        /**
         * @brief Возвращает элемент в списке
         *
         * @param index Индекс элемента
         * @return Элемент из списка
         */
        T operator[](size_t index) const {
            const qword buffer_address = shared::memory->read<qword>(reinterpret_cast<qword>(this) + sizeof(size_t));
            return shared::memory->read<T>(buffer_address + index * sizeof(T));
        }
    };
}

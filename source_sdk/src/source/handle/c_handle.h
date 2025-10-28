#pragma once

#include <source/handle/c_base_handle.h>

namespace source {

    template<typename T>
    class c_handle : public c_base_handle {
    public:
        c_handle() = default;

        explicit c_handle(unsigned int index) : c_base_handle(index) {}
    public:
        common::local_ptr<T> operator*() {
            return get().cast<T>();
        }
    };
}

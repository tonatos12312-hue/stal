#pragma once

#include <source/handle/c_base_handle.h>

namespace source {

    struct resource_binding {
        ptr data;
    };

    template<typename T>
    class c_strong_handle : public c_base_handle {
    public:
        c_strong_handle() : binding(nullptr) {}

        explicit c_strong_handle(const resource_binding* binding) : binding(binding) {}
    public:
        T* get() const {
            return static_cast<T*>(binding->data);
        }
    public:
        T* operator*() {
            return static_cast<T*>(get());
        }
    private:
        const resource_binding* binding;
    };
}

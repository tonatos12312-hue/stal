#pragma once

#include "element.h"

class toggle final : public element {
public:
    explicit toggle(const std::string_view& name, bool value = false) : element(name), value(value) {}
public:
    bool get() const {
        return value;
    }

    void set(bool value) {
        this->value = value;
    }
private:
    bool value;
};

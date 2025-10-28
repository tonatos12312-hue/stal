#pragma once

#include "element.h"

class slider final : public element {
public:
    explicit slider(const std::string_view& name, float value, float minimum, float maximum) : element(name), value(value), minimum_value(minimum), maximum_value(maximum) {}
public:
    float number() const {
        return value;
    }

    void set(float number) {
        value = number;
    }

    float minimum() const {
        return minimum_value;
    }

    float maximum() const {
        return maximum_value;
    }
private:
    float value;
    float minimum_value;
    float maximum_value;
};

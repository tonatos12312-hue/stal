#pragma once

#include <string_view>

class element {
public:
    explicit element(const std::string_view& name) : name(name) {}

    virtual ~element() = default;
public:
    std::string_view display_name() const {
        return name;
    }
private:
    std::string_view name;
};

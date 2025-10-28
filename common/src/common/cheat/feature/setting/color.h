#pragma once

#include <algorithm>
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <imgui.h>
#include "element.h"

class color final : public element {
public:
    color(const std::string_view& name, std::initializer_list<float> color_values) : element(name) {
        if (color_values.size() != 4)
            throw std::invalid_argument("color must have exactly 4 float values");

        std::copy(color_values.begin(), color_values.end(), colors.begin());
    }
public:
    std::array<float, 4>& get_color() {
        return colors;
    }

    ImColor get_imcolor() const {
        return ImColor(colors[0], colors[1], colors[2], colors[3]);
    }
private:
    std::array<float, 4> colors{};
};

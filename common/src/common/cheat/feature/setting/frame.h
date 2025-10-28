#pragma once

#include <vector>
#include "element.h"
#include "slider.h"
#include "toggle.h"
#include "combobox.h"
#include "color.h"
#include "bind.h"

enum class frame_position {
    left,
    right
};

class frame {
public:
    explicit frame(const std::string_view& title, frame_position pos) : title(title), pos(pos) {}
public:
    void add(element* element) {
        element_vector.push_back(element);
    }

    std::vector<element*> elements() const {
        return element_vector;
    }

    std::string_view display_name() const {
        return title;
    }

    frame_position position() const {
        return pos;
    }
private:
    std::string_view title;
    frame_position pos;
    std::vector<element*> element_vector;
};

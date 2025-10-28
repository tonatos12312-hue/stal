#pragma once

#include <vector>
#include <string>
#include "element.h"

class combobox final : public element {
public:
    explicit combobox(const std::string_view& name, const std::vector<std::string>& selected_vector, const std::vector<std::string_view>& modes) : element(name), selected_vector(selected_vector), modes(modes) {}
public:
    bool is(const std::string_view& mode) {
        return std::count(selected_vector.begin(), selected_vector.end(), mode);
    }

    std::vector<std::string> selected() const {
        return selected_vector;
    }

    std::vector<std::string_view> all() const {
        return modes;
    }

    void select(const std::string_view& mode) {
        selected_vector.clear();
        selected_vector.push_back(std::string(mode));
    }
private:
    std::vector<std::string> selected_vector;
    const std::vector<std::string_view> modes;
};

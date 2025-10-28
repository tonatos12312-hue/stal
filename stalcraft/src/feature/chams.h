#pragma once

#include <common/cheat/feature/feature.h>

class chams_feature final : public common::feature {
public:
    chams_feature();
public:
    void tick() override {}
public:
    combobox* material_setting;
    color* color_setting;
    keybind* bind;
    combobox* state_type_setting;
};

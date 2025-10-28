#pragma once

#include <common/cheat/cheat.h>
#include <common/math/vector2.h>
#include <common/overlay/renderer.h>
#include "feature_renderer.h"
#include "gui_state.h"

class sidebar {
public:
    explicit sidebar(const vector2f& size, common::cheat* cheat, gui_state* state);
public:
    void render(const renderer& renderer);
private:
    void select_feature(feature_renderer& feature);
private:
    vector2f size;
    common::cheat* cheat;
    std::vector<feature_renderer> feature_renderers;
    gui_state* state;
};

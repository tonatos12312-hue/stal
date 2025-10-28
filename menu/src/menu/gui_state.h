#pragma once

#include <common/cheat/feature/feature.h>
#include <menu/element/frame_renderer.h>
#include <common/util/easings.h>

class gui_state {
public:
    explicit gui_state(common::feature* feature) : selected(nullptr) {
        select_feature(feature);
    }
public:
    common::feature* selected_feature() const {
        return selected;
    }

    void select_feature(common::feature* feature) {
        if (selected == feature)
            return;

        animation = 0.0f;
        selected = feature;
        frames.clear();
        for (const frame& feature_frame : feature->frames())
            frames.push_back(frame_renderer(feature_frame));
    }

    void tick() {
        animation = lerp(animation, 1.0f, ImGui::GetIO().DeltaTime * 10);
    }

    std::vector<frame_renderer>& frame_renderers() {
        return frames;
    }
public:
    float animation = 0.0f;
private:
    common::feature* selected;
    std::vector<frame_renderer> frames;
};

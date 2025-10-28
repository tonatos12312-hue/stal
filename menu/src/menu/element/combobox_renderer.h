#pragma once

#include <common/cheat/feature/setting/combobox.h>
#include "element_renderer.h"

class combobox_renderer final : public element_renderer {
public:
    explicit combobox_renderer(combobox* combo);
public:
    void render(const renderer& renderer, bool interactions_blocked = false) override;

    void render_overlay(const renderer& renderer) override;

    bool has_overlay() const override;

    bool is_blocking_interactions() const override;

    float height() const override;
private:
    combobox* combo;
    bool opened = false;
    float animation = 0.0f;
    float width_animation = 0.0f;
};

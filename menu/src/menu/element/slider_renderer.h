#pragma once

#include <common/cheat/feature/setting/slider.h>
#include <common/overlay/renderer.h>
#include "element_renderer.h"

class slider_renderer final : public element_renderer {
public:
    explicit slider_renderer(slider* owner);
public:
    void render(const renderer& renderer, bool interactions_blocked = false) override;

    float height() const override;
private:
    slider* owner;
    bool sliding = false;
    float animation = 0.0f;
    float circle_animation = 0.0f;
};

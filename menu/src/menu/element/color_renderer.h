#pragma once

#include <common/cheat/feature/setting/color.h>
#include <common/overlay/renderer.h>
#include "element_renderer.h"

class color_renderer final : public element_renderer {
public:
    explicit color_renderer(color* owner);
public:
    void render(const renderer& renderer, bool interactions_blocked = false) override;

    float height() const override;
private:
    color* owner;
};


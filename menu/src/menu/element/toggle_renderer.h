#pragma once

#include <common/cheat/feature/setting/toggle.h>
#include "element_renderer.h"

class toggle_renderer final : public element_renderer {
public:
    explicit toggle_renderer(toggle* owner);
public:
    void render(const renderer& renderer, bool interactions_blocked = false) override;

    float height() const override;
private:
    toggle* owner;
    float animation = 0.0f;
};

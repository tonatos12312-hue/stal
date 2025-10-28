#pragma once

#include <common/cheat/feature/setting/bind.h>
#include "element_renderer.h"

class bind_renderer final : public element_renderer {
public:
    explicit bind_renderer(keybind* owner);
public:
    void render(const renderer& renderer, bool interactions_blocked = false) override;

    float height() const override;
private:
    keybind* owner;
    bool waiting = false;
};

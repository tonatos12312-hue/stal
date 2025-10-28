#pragma once

#include "esp_element.h"

class fade_esp_element final : public esp_element {
public:
    fade_esp_element() : esp_element("Fade") {}
public:
    void render(const esp_info& info, const renderer& renderer) override {
        renderer.gradient(info.position + vector2f(1, 0), info.size - vector2f(2, 1), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), ImColor(141, 75, 255, 150), ImColor(141, 75, 255, 150));
    }

    esp_hitbox hitbox(const vector2f& position, const vector2f& size, const renderer& renderer) override {
        esp_hitbox hitbox;
        hitbox.position = position + vector2f(0, size.y / 2);
        hitbox.size = vector2f(size.x, size.y / 2);

        return hitbox;
    }
};

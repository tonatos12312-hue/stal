#pragma once

#include <resources.h>
#include "esp_element.h"

class box_esp_element final : public esp_element {
public:
    box_esp_element() : esp_element("Box") {}
public:
    void render(const esp_info& info, const renderer& renderer) override {
        renderer.stroke(info.position, info.size, IM_COL32_WHITE);
    }

    esp_hitbox hitbox(const vector2f& position, const vector2f& size, const renderer& renderer) override {
        esp_hitbox hitbox;
        hitbox.position = position;
        hitbox.size = size;

        return hitbox;
    }
};

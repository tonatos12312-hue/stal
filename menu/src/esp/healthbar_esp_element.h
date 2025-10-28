#pragma once

#include <resources.h>
#include "esp_element.h"

class healthbar_esp_element final : public esp_element {
public:
    healthbar_esp_element() : esp_element("Health bar") {}
public:
    void render(const esp_info& info, const renderer& renderer) override {
        const vector2f health_bar_pos(info.position.x - 10, info.position.y);
        const float health_bar_height = info.size.y * info.health;

        char buffer[32]{};
        sprintf_s(buffer, sizeof(buffer), "%.0f", info.health * 100);

        renderer.rect(health_bar_pos, vector2f(5, info.size.y), IM_COL32_BLACK);
        renderer.gradient(health_bar_pos + vector2f(2, info.size.y - health_bar_height + 1), vector2f(2, health_bar_height), ImColor(0, 255, 0), ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(255, 0, 0));
    }

    esp_hitbox hitbox(const vector2f& position, const vector2f& size, const renderer& renderer) override {
        esp_hitbox hitbox;
        hitbox.position = vector2f(position.x - 10, position.y);
        hitbox.size = vector2f(5, size.y);

        return hitbox;
    }
};

#pragma once

#include "esp_element.h"

class corner_box_esp_element final : public esp_element {
public:
    corner_box_esp_element() : esp_element("Corner box") {}
public:
    void render(const esp_info& info, const renderer& renderer) override {
        const vector2f corner_length(info.size.x * 0.3f, info.size.y * 0.2f);

        renderer.rect(info.position, vector2f(corner_length.x, 1), IM_COL32_WHITE);
        renderer.rect(info.position, vector2f(1, corner_length.y), IM_COL32_WHITE);
        renderer.rect(info.position + vector2f(info.size.x - corner_length.x, 0), vector2f(corner_length.x, 1), IM_COL32_WHITE);
        renderer.rect(info.position + vector2f(info.size.x, 0), vector2f(1, corner_length.y), IM_COL32_WHITE);

        renderer.rect(info.position + vector2f(0, info.size.y - 1), vector2f(corner_length.x, 1), IM_COL32_WHITE);
        renderer.rect(info.position + vector2f(0, info.size.y - corner_length.y), vector2f(1, corner_length.y), IM_COL32_WHITE);
        renderer.rect(info.position + vector2f(info.size.x - corner_length.x, info.size.y - 1), vector2f(corner_length.x, 1), IM_COL32_WHITE);
        renderer.rect(info.position + vector2f(info.size.x, info.size.y - corner_length.y), vector2f(1, corner_length.y), IM_COL32_WHITE);
    }
};

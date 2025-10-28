#pragma once

#include <resources.h>
#include "esp_element.h"

class name_esp_element final : public esp_element {
public:
    name_esp_element() : esp_element("Name") {}
public:
    void render(const esp_info& info, const renderer& renderer) override {
        ImFont* font = static_cast<ImFont*>(generated::font_inter_medium_14->get_font());
        renderer.text(font, info.name, info.position + vector2f(info.size.x / 2 - renderer.text_size(font, info.name).x / 2, -18));
    }

    esp_hitbox hitbox(const vector2f& position, const vector2f& size, const renderer& renderer) override {
        ImFont* font = static_cast<ImFont*>(generated::font_inter_medium_14->get_font());

        esp_hitbox hitbox;
        hitbox.position = position + vector2f(size.x / 2 - renderer.text_size(font, "anfisov").x / 2, -18);
        hitbox.size = renderer.text_size(font, "anfisov");

        return hitbox;
    }
};

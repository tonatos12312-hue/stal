#pragma once

#include <string_view>
#include <common/math/vector2.h>
#include <common/overlay/renderer.h>
#include <resources.h>

struct esp_info {
    vector2f position;
    vector2f size;
    float health;
    std::string_view name;
};

struct esp_hitbox {
    vector2f position;
    vector2f size;
};

class esp_element {
public:
    explicit esp_element(const std::string_view& title) : title(title), enabled(false) {}

    virtual ~esp_element() = default;
public:
    virtual void render(const esp_info& info, const renderer& renderer) = 0;

    virtual esp_hitbox hitbox(const vector2f& position, const vector2f& size, const renderer& renderer) = 0;
public:
    void render_menu(const vector2f& element_position, const renderer& renderer) const {
        const vector2f text_size = renderer.text_size(static_cast<ImFont*>(generated::font_inter_medium_14->get_font()), title);
        const vector2f box_size = menu_size(renderer);

        renderer.rect(element_position, box_size, HEX_TO_IMCOL32("#252428"), 4);
        renderer.text(static_cast<const ImFont*>(generated::font_inter_medium_14->get_font()), title, element_position + box_size / 2 - text_size / 2);
    }

    vector2f menu_size(const renderer& renderer) const {
        const vector2f text_size = renderer.text_size(static_cast<ImFont*>(generated::font_inter_medium_14->get_font()), title);
        return text_size + vector2f(10, 6);
    }
public:
    std::string_view display_name() const {
        return title;
    }

    bool is_enabled() const {
        return enabled;
    }

    void set_enabled(bool enabled) {
        this->enabled = enabled;
    }
private:
    std::string_view title;
    bool enabled;
};

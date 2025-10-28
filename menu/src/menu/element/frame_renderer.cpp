#include "frame_renderer.h"

#include <esp/esp_preview.h>
#include <resources.h>
#include "bind_renderer.h"
#include "slider_renderer.h"
#include "toggle_renderer.h"
#include "combobox_renderer.h"
#include "color_renderer.h"
#include "esp_preview_renderer.h"

frame_renderer::frame_renderer(const frame& feature_frame) : feature_frame(feature_frame) {
    for (element* element : feature_frame.elements()) {
        if (slider* slider_element = dynamic_cast<slider*>(element))
            element_renderers.push_back(new slider_renderer(slider_element));
        else if (toggle* toggle_element = dynamic_cast<toggle*>(element))
            element_renderers.push_back(new toggle_renderer(toggle_element));
        else if (combobox* combobox_element = dynamic_cast<combobox*>(element))
            element_renderers.push_back(new combobox_renderer(combobox_element));
        else if (color* color_element = dynamic_cast<color*>(element))
            element_renderers.push_back(new color_renderer(color_element));
        else if (keybind* bind_element = dynamic_cast<keybind*>(element))
            element_renderers.push_back(new bind_renderer(bind_element));
        else if (esp_preview* preview_element = dynamic_cast<esp_preview*>(element))
            element_renderers.push_back(new esp_preview_renderer(preview_element));
    }
}

void frame_renderer::render(const renderer& renderer) const {
    renderer.stroke(vector2f(0, 0), vector2f(width(), height()), HEX_TO_IMCOL32("#212121"), 10);
    renderer.image(generated::image_menu_header->get_texture(), vector2f(16, 16), vector2f(16, 16), IM_COL32_WHITE);
    renderer.text(static_cast<ImFont*>(generated::font_inter_medium_16->get_font()), feature_frame.display_name(), vector2f(44, 15));

    if (!element_renderers.empty())
        renderer.rect(vector2f(0, 48), vector2f(width(), 1), HEX_TO_IMCOL32("#212121"));

    bool any_blocking = false;
    for (element_renderer* elem_renderer : element_renderers) {
        if (elem_renderer->is_blocking_interactions()) {
            any_blocking = true;
            break;
        }
    }

    float offset = 48 + 16;
    for (element_renderer* elem_renderer : element_renderers) {
        const bool interactions_blocked = any_blocking && !elem_renderer->is_blocking_interactions();
        elem_renderer->render(renderer.translated(vector2f(16, offset)), interactions_blocked);
        offset += elem_renderer->height() + 12;
    }
}

void frame_renderer::render_overlays(const renderer& renderer) const {
    float offset = 48 + 16;
    for (element_renderer* elem_renderer : element_renderers) {
        elem_renderer->render_overlay(renderer.translated(vector2f(16, offset)));
        offset += elem_renderer->height() + 12;
    }
}

bool frame_renderer::has_overlay() const {
    for (element_renderer* elem_renderer : element_renderers)
        if (elem_renderer->has_overlay())
            return true;

    return false;
}

float frame_renderer::height() const {
    float size = 47 + (element_renderers.empty() ? 0 : 20);
    for (const element_renderer* elem_renderer : element_renderers)
        size += elem_renderer->height() + 12;

    return size;
}

frame_position frame_renderer::position() const {
    return feature_frame.position();
}

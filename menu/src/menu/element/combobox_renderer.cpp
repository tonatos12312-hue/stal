#include "combobox_renderer.h"

#include <sstream>
#include <common/util/easings.h>
#include <resources.h>

combobox_renderer::combobox_renderer(combobox* combo) : element_renderer(combo), combo(combo) {}

void combobox_renderer::render(const renderer& renderer, bool interactions_blocked) {
    element_renderer::render(renderer, interactions_blocked);

    std::stringstream stream;
    if (combo->selected().empty())
        stream << "None";
    for (size_t i = 0; i < combo->selected().size(); i++) {
        stream << combo->selected()[i];
        if (i != combo->selected().size() - 1)
            stream << ", ";
    }

    width_animation = lerp(width_animation, 10 + renderer.text_size(static_cast<ImFont*>(generated::font_inter_medium_13->get_font()), stream.str().c_str()).x, ImGui::GetIO().DeltaTime * 8);
    const vector2f size(max(width_animation, 80.0f), 20);
    const vector2f position(width() - size.x, 0);
    renderer.rect(position, size, HEX_TO_IMCOL32("#252428"), 4);
    renderer.text(static_cast<ImFont*>(generated::font_inter_medium_13->get_font()), stream.str().c_str(), position + vector2f(5, 4));

    if (!interactions_blocked && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(position, size))
        opened = !opened;
}

void combobox_renderer::render_overlay(const renderer& renderer) {
    animation = ease_out_quart(animation, opened ? 1.0f : 0.0f, ImGui::GetIO().DeltaTime * 8);
    if (animation <= 0.01f)
        return;

    std::stringstream stream;
    for (size_t i = 0; i < combo->selected().size(); i++) {
        stream << combo->selected()[i];
        if (i != combo->selected().size() - 1)
            stream << ", ";
    }

    const vector2f size(max(width_animation, 80.0f), 20);
    const vector2f position(width() - size.x, 0);

    const float dropdown_height = combo->all().size() * size.y;
    const float animated_height = dropdown_height * animation;

    ImGui::PushClipRect(
        ImVec2(renderer.anchor().x + position.x, renderer.anchor().y + position.y + size.y + 6),
        ImVec2(renderer.anchor().x + position.x + size.x, renderer.anchor().y + position.y + size.y + 6 + animated_height),
        true
    );

    float offset = size.y + 6;
    for (size_t i = 0; i < combo->all().size(); i++) {
        const std::string_view mode = combo->all()[i];
        const vector2f mode_position(width() - size.x, offset);
        const ImDrawFlags flags = (i == 0) ? ImDrawFlags_RoundCornersTop : (i == combo->all().size() - 1) ? ImDrawFlags_RoundCornersBottom : ImDrawFlags_RoundCornersNone;

        renderer.rect(mode_position, size, HEX_TO_IMCOL32(combo->is(mode) ? "#333333" : "#252428"), 4, flags);
        renderer.text(static_cast<ImFont*>(generated::font_inter_medium_13->get_font()), std::string(mode).c_str(), mode_position + vector2f(5, 4));
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(mode_position, size) && animation > 0.9f)
            combo->select(mode);

        offset += size.y;
    }

    ImGui::PopClipRect();

    const vector2f full_dropdown_area(size.x, size.y + 6 + dropdown_height);
    const vector2f full_dropdown_pos(width() - size.x, 0);
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !renderer.hovering(full_dropdown_pos, full_dropdown_area)) {
        opened = false;
    }
}

bool combobox_renderer::has_overlay() const {
    return animation > 0.01f;
}

bool combobox_renderer::is_blocking_interactions() const {
    return opened;
}

float combobox_renderer::height() const {
    return 17;
}

#include "slider_renderer.h"

#include <algorithm>
#include <imgui_internal.h>
#include <resources.h>
#include <common/util/easings.h>

slider_renderer::slider_renderer(slider* owner) : element_renderer(owner), owner(owner) {}

void slider_renderer::render(const renderer& renderer, bool interactions_blocked) {
    element_renderer::render(renderer, interactions_blocked);

    const vector2f number_container_size(35, 20);
    const vector2f number_container_pos = vector2f(width() - number_container_size.x, -2);

    char buffer[32]{};
    sprintf_s(buffer, sizeof(buffer), "%.0f", owner->number());

    renderer.stroke(number_container_pos, number_container_size, HEX_TO_IMCOL32("#424242"), 6);
    renderer.text(static_cast<ImFont*>(generated::font_inter_medium_14->get_font()), buffer, number_container_pos + number_container_size / 2 - renderer.text_size(static_cast<ImFont*>(generated::font_inter_medium_14->get_font()), buffer) / 2);


    constexpr float full_line_width = 130;
    const float maximum_calculated = owner->maximum() - owner->minimum();
    const float diff = full_line_width / maximum_calculated;
    const float line_width = (owner->number() * diff) - owner->minimum() * diff;
    animation = lerp(animation, line_width, ImGui::GetIO().DeltaTime * 8);

    const vector2f full_line_size = vector2f(full_line_width, 4);
    const vector2f full_line_pos = vector2f(number_container_pos.x - full_line_size.x - 8, height() / 2 - full_line_size.y / 2);

    renderer.rect(full_line_pos, full_line_size, HEX_TO_IMCOL32("#3A3740"), 2);
    renderer.rect(full_line_pos, vector2f(animation, full_line_size.y), HEX_TO_IMCOL32("#8D4BFF"), 2);

    const vector2f hitbox_expand(8, 6);
    const vector2f hitbox_pos = full_line_pos - hitbox_expand;
    const vector2f hitbox_size = full_line_size + hitbox_expand;
    const bool hovered = renderer.hovering(hitbox_pos, hitbox_size);

    constexpr float circle_radius = 6;
    const vector2f circle_pos = vector2f(full_line_pos.x + animation, full_line_pos.y + full_line_size.y / 2);
    circle_animation = lerp(circle_animation, sliding || hovered ? 3 : 0, ImGui::GetIO().DeltaTime * 8);
    renderer.circle(circle_pos, circle_radius + circle_animation, IM_COL32_WHITE);

    if (!interactions_blocked && ImGui::IsMouseDown(ImGuiMouseButton_Left) && hovered)
        sliding = true;
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        sliding = false;

    if (sliding) {
        owner->set(std::clamp((ImGui::GetMousePos().x - renderer.anchor().x - full_line_pos.x) * (owner->maximum() / full_line_width) + owner->minimum(), owner->minimum(), owner->maximum()));

        ImGui::GetCurrentWindow()->Flags |= ImGuiWindowFlags_NoMove;
    }
}

float slider_renderer::height() const {
    return 17;
}

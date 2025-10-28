#include "toggle_renderer.h"

#include <algorithm>
#include <common/util/easings.h>

toggle_renderer::toggle_renderer(toggle* owner) : element_renderer(owner), owner(owner) {}

void toggle_renderer::render(const renderer& renderer, bool interactions_blocked) {
    element_renderer::render(renderer, interactions_blocked);
    animation = ease_out_quart(animation, owner->get() ? 1 : 0, ImGui::GetIO().DeltaTime * 5);

    const vector2f size(30, 18);
    const vector2f static_pos(width() - size.x, 0);
    const vector2f circle_pos = static_pos + vector2f(3 + animation * 12, 3);
    renderer.rect(static_pos, size, ImColor(std::clamp(58 + static_cast<int>(animation * 28), 0, 255), 55, std::clamp(64 + static_cast<int>(animation * 78), 0, 255)), 10);
    renderer.rect(circle_pos, vector2f(12, 12), ImColor(std::clamp(97 + static_cast<int>(animation * 158), 0, 255), std::clamp(97 + static_cast<int>(animation * 158), 0, 255), std::clamp(97 + static_cast<int>(animation * 158), 0, 255)), 12);

    if (!interactions_blocked && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(static_pos, size))
        owner->set(!owner->get());
}

float toggle_renderer::height() const {
    return 17;
}

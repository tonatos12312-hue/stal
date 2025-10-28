#include "esp_preview_renderer.h"

#include <imgui_internal.h>
#include <resources.h>

esp_preview_renderer::esp_preview_renderer(esp_preview* preview) : element_renderer(preview), preview(preview), drag(nullptr) {}

void esp_preview_renderer::render(const renderer& renderer, bool interactions_blocked) {
    const vector2f size(150, 300);
    const vector2f position = vector2f(width() / 2 - size.x / 2, 100);

    vector2f elements_size(0, 0);
    for (const esp_element* element : preview->elements())
        elements_size += vector2f(element->menu_size(renderer).x + 5, 0);

    const common::image* vazelin = generated::image_vazelin;
    renderer.image(vazelin->get_texture(), position, size);

    vector2f element_position(width() / 2 - elements_size.x / 2, height() - elements_size.y - 20);
    for (esp_element* element : preview->elements()) {
        element->render_menu(element_position, renderer);
        if (!element->is_enabled() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(element_position, element->menu_size(renderer))) {
            drag = element;
            previous = vector2f(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y) - element_position;
        }

        const esp_hitbox hitbox = element->hitbox(position, size, renderer);
        if (element->is_enabled() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(hitbox.position, hitbox.size)) {
            drag = element;
            previous = renderer.anchor();
        }

        element_position += vector2f(element->menu_size(renderer).x + 5, 0);
    }

    if (drag) {
        ImGui::GetCurrentWindow()->Flags |= ImGuiWindowFlags_NoMove;
        drag_position = vector2f(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y) - previous;

        drag->render_menu(drag_position, renderer);
        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            drag->set_enabled(renderer.hovering(position, size));
            drag = nullptr;
        }
    }

    preview->render_preview(renderer, position, size);
}

float esp_preview_renderer::height() const {
    return 560;
}

#include "color_renderer.h"

#include <resources.h>

color_renderer::color_renderer(color* owner) : element_renderer(owner), owner(owner) {}

void color_renderer::render(const renderer& renderer, bool interactions_blocked) {
    element_renderer::render(renderer, interactions_blocked);

    const float x = renderer::text_size(static_cast<ImFont*>(generated::font_inter_medium_16->get_font()), owner->display_name().data()).x + 10;
    renderer.rect(vector2f(x, 0), vector2f(16, 16), ImColor(owner->get_color()[0], owner->get_color()[1], owner->get_color()[2], owner->get_color()[3]), 3);

    if (!interactions_blocked) {
        const char* popup_id = owner->display_name().data();

        ImGui::PushID(popup_id);
        ImVec2 button_pos(renderer.anchor().x + x, renderer.anchor().y);
        ImGui::SetCursorScreenPos(button_pos);
        if (ImGui::InvisibleButton(popup_id, ImVec2(16, 16)))
            ImGui::OpenPopup(popup_id);

        ImGui::SetNextWindowPos(ImVec2(button_pos.x, button_pos.y + 16));

        if (ImGui::BeginPopup(popup_id)) {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
            ImGui::ColorPicker4(popup_id, owner->get_color().data(),
                               ImGuiColorEditFlags_AlphaBar |
                               ImGuiColorEditFlags_DisplayRGB |
                               ImGuiColorEditFlags_DisplayHex |
                               ImGuiColorEditFlags_NoSidePreview |
                               ImGuiColorEditFlags_NoSmallPreview
            );

            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();

            ImGui::PopStyleColor(6);
            ImGui::EndPopup();
        }

        ImGui::PopID();
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y + 16 + 8));
    }
}

float color_renderer::height() const {
    return 17;
}

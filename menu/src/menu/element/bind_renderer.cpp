#include "bind_renderer.h"

#include <resources.h>

cstr key_to_string(int key) {
    static char buffer[32];

    if (key >= ImGuiKey_A && key <= ImGuiKey_Z) {
        buffer[0] = 'A' + (key - ImGuiKey_A);
        buffer[1] = '\0';
        return buffer;
    } else if (key >= ImGuiKey_0 && key <= ImGuiKey_9) {
        buffer[0] = '0' + (key - ImGuiKey_0);
        buffer[1] = '\0';
        return buffer;
    } else if (key == ImGuiKey_Space)
        return "Space";
    else if (key == ImGuiKey_Enter)
        return "Enter";
    else if (key == ImGuiKey_Tab)
        return "Tab";
    else if (key == ImGuiKey_LeftShift || key == ImGuiKey_RightShift)
        return "Shift";
    else if (key == ImGuiKey_LeftControl || key == ImGuiKey_RightControl)
        return "Ctrl";
    else if (key == ImGuiKey_LeftAlt || key == ImGuiKey_RightAlt)
        return "Alt";
    else if (key == ImGuiKey_Backspace)
        return "Backspace";
    else if (key == ImGuiKey_Delete)
        return "Delete";

    return "";
}

PCSTR mouse_to_string(int mouse) {
    switch (mouse) {
        case ImGuiMouseButton_Left:
            return "LBM";
        case ImGuiMouseButton_Right:
            return "RMB";
        case ImGuiMouseButton_Middle:
            return "MMB";
        case 3:
            return "MB4";
        case 4:
            return "MB5";
        default:
            return "Unknown";
    }
}

bind_renderer::bind_renderer(keybind* owner) : element_renderer(owner), owner(owner) {}

void bind_renderer::render(const renderer& renderer, bool interactions_blocked) {
    element_renderer::render(renderer, interactions_blocked);

    cstr string = "None";
    if (owner->kb() != -1)
        string = key_to_string(owner->kb());
    else if (owner->mb() != -1)
        string = mouse_to_string(owner->mb());

    const vector2f text_size = renderer.text_size(static_cast<ImFont*>(generated::font_inter_medium_13->get_font()), string);
    const vector2f box_size(text_size.x + 10, 20);
    const vector2f position(width() - box_size.x, 0);

    renderer.rect(position, box_size, HEX_TO_IMCOL32(waiting ? "#333333" : "#252428"), 4);
    renderer.text(static_cast<ImFont*>(generated::font_inter_medium_13->get_font()), string, position + box_size / 2 - text_size / 2);

    if (waiting) {
        for (int i = ImGuiMouseButton_Left; i < ImGuiMouseButton_COUNT; i++) {
            if (ImGui::IsMouseClicked(i)) {
                owner->set_kb(-1);
                owner->set_mb(i);
                waiting = false;
                return;
            }
        }

        for (int i = ImGuiKey_NamedKey_BEGIN; i < ImGuiKey_NamedKey_END; i++) {
            if (ImGui::IsKeyPressed(i)) {
                if (i == ImGuiKey_Escape) {
                    waiting = false;
                    return;
                }

                owner->set_kb(i);
                owner->set_mb(-1);
                waiting = false;
                return;
            }
        }
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(position, box_size))
        waiting = true;
}

float bind_renderer::height() const {
    return 15;
}

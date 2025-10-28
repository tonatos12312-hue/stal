#pragma once

#include <imgui.h>
#include <map>
#include <Windows.h>
#include <vector>
#include <string>
#include "element.h"

static std::map<int, int> imGuiKeyToVk = {
    { ImGuiKey_Tab, VK_TAB },
    { ImGuiKey_LeftArrow, VK_LEFT },
    { ImGuiKey_RightArrow, VK_RIGHT },
    { ImGuiKey_UpArrow, VK_UP },
    { ImGuiKey_DownArrow, VK_DOWN },
    { ImGuiKey_PageUp, VK_PRIOR },
    { ImGuiKey_PageDown, VK_NEXT },
    { ImGuiKey_Home, VK_HOME },
    { ImGuiKey_End, VK_END },
    { ImGuiKey_Insert, VK_INSERT },
    { ImGuiKey_Delete, VK_DELETE },
    { ImGuiKey_Backspace, VK_BACK },
    { ImGuiKey_Space, VK_SPACE },
    { ImGuiKey_Enter, VK_RETURN },
    { ImGuiKey_Escape, VK_ESCAPE },
    { ImGuiKey_A, 0x41 }, // 'A'
    { ImGuiKey_B, 0x42 }, // 'B'
    { ImGuiKey_C, 0x43 },
    { ImGuiKey_D, 0x44 },
    { ImGuiKey_E, 0x45 },
    { ImGuiKey_F, 0x46 },
    { ImGuiKey_G, 0x47 },
    { ImGuiKey_H, 0x48 },
    { ImGuiKey_I, 0x49 },
    { ImGuiKey_J, 0x4A },
    { ImGuiKey_K, 0x4B },
    { ImGuiKey_L, 0x4C },
    { ImGuiKey_M, 0x4D },
    { ImGuiKey_N, 0x4E },
    { ImGuiKey_O, 0x4F },
    { ImGuiKey_P, 0x50 },
    { ImGuiKey_Q, 0x51 },
    { ImGuiKey_R, 0x52 },
    { ImGuiKey_S, 0x53 },
    { ImGuiKey_T, 0x54 },
    { ImGuiKey_U, 0x55 },
    { ImGuiKey_V, 0x56 },
    { ImGuiKey_W, 0x57 },
    { ImGuiKey_X, 0x58 },
    { ImGuiKey_Y, 0x59 },
    { ImGuiKey_Z, 0x5A },
    { ImGuiKey_0, 0x30 },
    { ImGuiKey_1, 0x31 },
    { ImGuiKey_2, 0x32 },
    { ImGuiKey_3, 0x33 },
    { ImGuiKey_4, 0x34 },
    { ImGuiKey_5, 0x35 },
    { ImGuiKey_6, 0x36 },
    { ImGuiKey_7, 0x37 },
    { ImGuiKey_8, 0x38 },
    { ImGuiKey_9, 0x39 },
    { ImGuiKey_LeftControl, VK_LCONTROL },
    { ImGuiKey_RightControl, VK_RCONTROL },
    { ImGuiKey_LeftShift, VK_LSHIFT },
    { ImGuiKey_RightShift, VK_RSHIFT },
    { ImGuiKey_LeftAlt, VK_LMENU },
    { ImGuiKey_RightAlt, VK_RMENU },
     { ImGuiKey_LeftSuper, VK_LWIN },
    { ImGuiKey_RightSuper, VK_RWIN },
    { ImGuiKey_Menu, VK_APPS },
    { ImGuiKey_F1, VK_F1 },
    { ImGuiKey_F2, VK_F2 },
    { ImGuiKey_F3, VK_F3 },
    { ImGuiKey_F4, VK_F4 },
    { ImGuiKey_F5, VK_F5 },
    { ImGuiKey_F6, VK_F6 },
    { ImGuiKey_F7, VK_F7 },
    { ImGuiKey_F8, VK_F8 },
    { ImGuiKey_F9, VK_F9 },
    { ImGuiKey_F10, VK_F10 },
    { ImGuiKey_F11, VK_F11 },
    { ImGuiKey_F12, VK_F12 },
    {ImGuiKey_CapsLock, VK_CAPITAL},

    { ImGuiMouseButton_Left, VK_LBUTTON },
    { ImGuiMouseButton_Right, VK_RBUTTON },
    { 3, VK_XBUTTON1 },
    { 4, VK_XBUTTON2 },
    { ImGuiMouseButton_Middle, VK_MBUTTON }
};

class keybind final : public element {
public:
    explicit keybind(const int keyboard_button = -1, const int mouse_button = -1) : element("Keybind"), keyboard_button(keyboard_button), mouse_button(mouse_button), hold(false) {}
public:
    bool check_hold() const {
        return GetAsyncKeyState(keyboard_button != -1 ? imGuiKeyToVk[keyboard_button] : mouse_button != -1 ? imGuiKeyToVk[mouse_button] : -1);
    }

    bool check_toggle() {
        bool current_key_state = GetAsyncKeyState(keyboard_button != -1 ? imGuiKeyToVk[keyboard_button] : mouse_button != -1 ? imGuiKeyToVk[mouse_button] : -1);

        if (current_key_state && !prev_key_state)
            toggle_state = !toggle_state;

        prev_key_state = current_key_state;
        return toggle_state;
    }

    int kb() const {
        return keyboard_button;
    }

    int mb() const {
        return mouse_button;
    }

    void set_kb(const int keyboard_button) {
        this->keyboard_button = keyboard_button;
    }

    void set_mb(const int mouse_button) {
        this->mouse_button = mouse_button;
    }
private:
    int keyboard_button;
    int mouse_button;
    bool hold;
private:
    bool toggle_state;
    bool prev_key_state;
};

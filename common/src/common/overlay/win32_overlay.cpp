#include "win32_overlay.h"

#include <stdexcept>
#include <dwmapi.h>
#include <imgui_impl_win32.h>

namespace common {

    win32_overlay::win32_overlay(render_fn render_function, WNDPROC wnd_proc) : overlay(render_function), window_handle(nullptr), wnd_proc(wnd_proc) {}

    win32_overlay::~win32_overlay() {
        if (window_handle)
            DestroyWindow(window_handle);
    }

    void win32_overlay::create() {
        overlay::create();
        ImGui_ImplWin32_EnableDpiAwareness();

        const HMODULE module_handle = GetModuleHandleA(nullptr);
        const WNDCLASSEX window_class_ex = {
            sizeof(window_class_ex),
            CS_CLASSDC,
            wnd_proc,
            0,
            0,
            module_handle,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            ("Pantheon"),
            nullptr
        };
        RegisterClassExA(&window_class_ex);

        RECT rect{};
        if (!GetWindowRect(GetDesktopWindow(), &rect))
            throw std::exception("Cannot get screen size");

        window_handle = CreateWindowEx(
            WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
            window_class_ex.lpszClassName,
            window_class_ex.lpszClassName,
            WS_POPUP,
            rect.left,
            rect.top,
            rect.right,
            rect.bottom,
            nullptr,
            nullptr,
            window_class_ex.hInstance,
            nullptr
        );
        if (window_handle == INVALID_HANDLE_VALUE)
            throw std::exception("Cannot create window");

        SetLayeredWindowAttributes(window_handle, RGB(0, 0, 0), 255, LWA_ALPHA);
        constexpr MARGINS margin = { -1 };
        if (FAILED(DwmExtendFrameIntoClientArea(window_handle, &margin)))
            throw std::exception("Cannot make window transparent");
    }
}

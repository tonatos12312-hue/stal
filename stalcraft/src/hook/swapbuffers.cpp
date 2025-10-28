#include "swapbuffers.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <resources.h>
#include <common/cavehook/CaveHook.h>
#include <common/resource/imgui/imgui_font_resource_manager.h>
#include <common/resource/opengl3/opengl3_image_resource_manager.h>
#include <menu/gui.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool imgui_context_created = false;
WNDPROC origin_wndproc = nullptr;
HWND current_window = nullptr;
bool window_hooked = false;

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (window_hooked && IsWindow(hWnd) && shared::menu)
        if (shared::menu->is_opened() && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

    if (origin_wndproc && IsWindow(hWnd))
        return CallWindowProcA(origin_wndproc, hWnd, msg, wParam, lParam);

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

void CleanupWindow() {
    if (window_hooked && current_window && IsWindow(current_window))
        if (origin_wndproc)
            SetWindowLongPtrW(current_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(origin_wndproc));

    if (window_hooked) {
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
    }

    window_hooked = false;
    current_window = nullptr;
    origin_wndproc = nullptr;
}

bool InitializeWindow(HWND window_handle, common::cheat* cheat) {
    if (!window_handle || !IsWindow(window_handle))
        return false;

    if (current_window == window_handle && window_hooked)
        return true;

    CleanupWindow();

    if (!imgui_context_created) {
        ImGui::CreateContext();
        imgui_context_created = true;
    }

    if (!ImGui_ImplWin32_Init(window_handle))
        return false;

    if (!ImGui_ImplOpenGL3_Init()) {
        ImGui_ImplWin32_Shutdown();
        return false;
    }

    origin_wndproc = reinterpret_cast<WNDPROC>(GetWindowLongPtrW(window_handle, GWLP_WNDPROC));
    if (!origin_wndproc) {
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        return false;
    }

    common::opengl3_image_resource_manager image_resource_manager;
    common::imgui_font_resource_manager font_resource_manager;
    common::resource_manager resource_manager(&image_resource_manager, &font_resource_manager);
    generated_sc::setup_resources(&resource_manager);

    shared::menu = new gui(&resource_manager, vector2f(550, 420), cheat);

    SetWindowLongPtrW(window_handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));

    current_window = window_handle;
    window_hooked = true;
    return true;
}

PVOID original_wgl_swapbuffers = nullptr;

BOOL WINAPI detour_wgl_swapbuffers(HDC hDc) {
    HWND window_handle = WindowFromDC(hDc);
    if (!window_handle)
        window_handle = FindWindowA("GLFW30", nullptr);

    if (window_handle && IsWindow(window_handle)) {
        if (!window_hooked || current_window != window_handle)
            if (!InitializeWindow(window_handle, swapbuffers_hook::sc_cheat))
                return reinterpret_cast<decltype(&detour_wgl_swapbuffers)>(original_wgl_swapbuffers)(hDc);

        if (window_hooked) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            shared::menu->render();

            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    return reinterpret_cast<decltype(&detour_wgl_swapbuffers)>(original_wgl_swapbuffers)(hDc);
}

void swapbuffers_hook::setup() {
    CaveHook(reinterpret_cast<ULONG_PTR>(GetProcAddress(GetModuleHandleA("OPENGL32.dll"), "wglSwapBuffers")), detour_wgl_swapbuffers, &original_wgl_swapbuffers);
}

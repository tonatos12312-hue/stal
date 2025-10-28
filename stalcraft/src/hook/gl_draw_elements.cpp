#include "gl_draw_elements.h"

#include <Windows.h>
#include <gl/GL.h>
#include <common/cavehook/CaveHook.h>
#include "gl_constants.h"
#include "material/material_set.h"

PVOID original_gl_draw_elements = nullptr;

void WINAPI detour_gl_draw_elements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    auto original_func = reinterpret_cast<decltype(&detour_gl_draw_elements)>(original_gl_draw_elements);

    return original_func(mode, count, type, indices);
}

PVOID original_wgl_get_proc_address = nullptr;

PROC WINAPI detour_wgl_get_proc_address(LPCSTR lpszProc) {
    if (!original_wgl_get_proc_address || !lpszProc)
        return nullptr;

    auto original_func = reinterpret_cast<decltype(&detour_wgl_get_proc_address)>(original_wgl_get_proc_address);
    PROC proc_address = original_func(lpszProc);

    if (!proc_address) {
        return nullptr;
    }

    if (strcmp(lpszProc, "glDrawElements") == 0) {
        static bool hook_installed = false;
        if (!hook_installed) {
            hook_installed = true;

            if (!CaveHook(reinterpret_cast<ULONG_PTR>(proc_address), detour_gl_draw_elements, &original_gl_draw_elements))
                hook_installed = false;
        }
    }

    return proc_address;
}

void gl_draw_elements_hook::setup() {
    CaveHook(reinterpret_cast<ULONG_PTR>(wglGetProcAddress), detour_wgl_get_proc_address, &original_wgl_get_proc_address);
}

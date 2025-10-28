#pragma once

#include <Windows.h>
#include <common/overlay/overlay.h>

namespace common {

    /**
     * @brief Представляет базовый оверлей через Win32 API
     */
    class win32_overlay : public overlay {
    public:
        explicit win32_overlay(render_fn render_function, WNDPROC wnd_proc);

        ~win32_overlay() override;
    public:
        void create() override;
    protected:
        HWND window_handle; ///< Handle на окно
    private:
        WNDPROC wnd_proc;
    };
}

#pragma once

#include <d3d11.h>
#include <common/overlay/win32_overlay.h>

namespace common {

    /**
     * @brief Представляет оверлей с использованием Win32 API + DirectX 11
     */
    class directx11_win32_overlay final : public win32_overlay {
    public:
        explicit directx11_win32_overlay(render_fn render_function);

        ~directx11_win32_overlay() override;
    public:
        void create() override;

        void loop() override;
    public:
        ID3D11Device* dx11_device() const {
            return device;
        }
    private:
        ID3D11DeviceContext* context; ///< DirectX11 context
        ID3D11Device* device; ///< DirectX11 device
        IDXGISwapChain* swapchain; ///< SwapChain
        ID3D11RenderTargetView* render_framebuffer; ///< DirectX11 render target view
    };
}

#include "directx11_win32_overlay.h"

#include <stdexcept>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param) {
    if (ImGui_ImplWin32_WndProcHandler(window_handle, message, w_param, l_param))
        return true;

    if (message == WM_DESTROY) {
        PostQuitMessage(0);
        ExitProcess(0);
    }

    return DefWindowProc(window_handle, message, w_param, l_param);
}

namespace common {

    directx11_win32_overlay::directx11_win32_overlay(render_fn render_function) : win32_overlay(render_function, window_procedure),
        context(nullptr), device(nullptr), swapchain(nullptr), render_framebuffer(nullptr) {}

    directx11_win32_overlay::~directx11_win32_overlay() {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (render_framebuffer)
            render_framebuffer->Release();
        if (swapchain)
            swapchain->Release();
        if (context)
            context->Release();
        if (device)
            device->Release();
    }

    void directx11_win32_overlay::create() {
        win32_overlay::create();

        DXGI_SWAP_CHAIN_DESC swapchain_descriptor{};
        swapchain_descriptor.BufferCount = 2;
        swapchain_descriptor.BufferDesc.Width = 0;
        swapchain_descriptor.BufferDesc.Height = 0;
        swapchain_descriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapchain_descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        swapchain_descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapchain_descriptor.OutputWindow = window_handle;
        swapchain_descriptor.SampleDesc.Count = 1;
        swapchain_descriptor.SampleDesc.Quality = 0;
        swapchain_descriptor.Windowed = TRUE;
        swapchain_descriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL feature_level;
        constexpr D3D_FEATURE_LEVEL feature_levels[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, feature_levels, 2, D3D11_SDK_VERSION, &swapchain_descriptor, &swapchain, &device, &feature_level, &context);
        if (result == DXGI_ERROR_UNSUPPORTED)
            result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, feature_levels, 2, D3D11_SDK_VERSION, &swapchain_descriptor, &swapchain, &device, &feature_level, &context);
        if (result != S_OK)
            throw std::exception("Cannot create DirectX11 device");

        ID3D11Texture2D* framebuffer_texture;
        if (FAILED(swapchain->GetBuffer(0, IID_PPV_ARGS(&framebuffer_texture))))
            throw std::exception("Cannot get framebuffer texture");

        if (FAILED(device->CreateRenderTargetView(framebuffer_texture, nullptr, &render_framebuffer)))
            throw std::exception("Cannot create framebuffer view");

        framebuffer_texture->Release();

        ShowWindow(window_handle, SW_SHOWDEFAULT);
        UpdateWindow(window_handle);

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(window_handle);
        ImGui_ImplDX11_Init(device, context);
    }

    void directx11_win32_overlay::loop() {
        overlay::loop();
        constexpr float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

        while (true) {
            MSG msg;
            while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            if (is_interactable())
                SetWindowLong(window_handle, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT);
            else
                SetWindowLong(window_handle, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED);

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            {
                render_function(this);
            }

            ImGui::EndFrame();
            ImGui::Render();

            context->OMSetRenderTargets(1, &render_framebuffer, nullptr);
            context->ClearRenderTargetView(render_framebuffer, clearColor);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            swapchain->Present(0, 0);
        }
    }
}

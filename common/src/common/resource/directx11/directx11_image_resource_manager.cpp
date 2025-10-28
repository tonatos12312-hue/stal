#include "directx11_image_resource_manager.h"

#include <stdexcept>
#include <d3dx11.h>
#include "directx11_image.h"

namespace common {

    directx11_image_resource_manager::directx11_image_resource_manager(ID3D11Device* device) : device(device) {}

    image* directx11_image_resource_manager::create_image_from_file(const std::string_view& file_path) {
        D3DX11_IMAGE_LOAD_INFO image_info{};
        ID3DX11ThreadPump* thread_pump = nullptr;
        ID3D11ShaderResourceView* shader_resource_view = nullptr;

        HRESULT result = D3DX11CreateShaderResourceViewFromFileA(device, std::string(file_path).c_str(), &image_info, thread_pump, &shader_resource_view, nullptr);
        if (FAILED(result))
            throw std::exception("Cannot create shader resource view from file");

        ID3D11Resource* resource = nullptr;
        shader_resource_view->GetResource(&resource);

        ID3D11Texture2D* texture = nullptr;
        resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture));

        D3D11_TEXTURE2D_DESC texture_desc;
        texture->GetDesc(&texture_desc);

        vector2i size(static_cast<int>(texture_desc.Width), static_cast<int>(texture_desc.Height));

        texture->Release();
        resource->Release();

        return new directx11_image(shader_resource_view, size);
    }

    image* directx11_image_resource_manager::create_image_from_bytes(const std::vector<uint8_t>& bytes) {
        D3DX11_IMAGE_LOAD_INFO image_info{};
        ID3DX11ThreadPump* thread_pump = nullptr;
        ID3D11ShaderResourceView* shader_resource_view = nullptr;

        HRESULT result = D3DX11CreateShaderResourceViewFromMemory(device, bytes.data(), static_cast<SIZE_T>(bytes.size()), &image_info, thread_pump, &shader_resource_view, nullptr);
        if (FAILED(result))
            throw std::exception("Cannot create shader resource view from bytes");

        ID3D11Resource* resource = nullptr;
        shader_resource_view->GetResource(&resource);

        ID3D11Texture2D* texture = nullptr;
        resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture));

        D3D11_TEXTURE2D_DESC texture_desc;
        texture->GetDesc(&texture_desc);

        vector2i size(static_cast<int>(texture_desc.Width), static_cast<int>(texture_desc.Height));

        texture->Release();
        resource->Release();

        return new directx11_image(shader_resource_view, size);
    }
}

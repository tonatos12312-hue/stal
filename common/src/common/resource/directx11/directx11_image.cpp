#include "directx11_image.h"

namespace common {

    directx11_image::directx11_image(ID3D11ShaderResourceView* shader_resource_view, const vector2i& size) : shader_resource_view(shader_resource_view), size(size) {}

    directx11_image::~directx11_image() {
        if (shader_resource_view)
            shader_resource_view->Release();
    }

    vector2i directx11_image::get_size() const {
        return size;
    }

    ID3D11ShaderResourceView* directx11_image::get_shader_resource_view() const {
        return shader_resource_view;
    }

    ptr directx11_image::get_texture() const {
        return get_shader_resource_view();
    }
}

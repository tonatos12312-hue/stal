#pragma once

#include <d3d11.h>
#include <common/resource/image/image.h>

namespace common {

    class directx11_image final : public image {
    public:
        explicit directx11_image(ID3D11ShaderResourceView* shader_resource_view, const vector2i& size);

        ~directx11_image() override;
    public:
        vector2i get_size() const override;

        ID3D11ShaderResourceView* get_shader_resource_view() const;

        ptr get_texture() const override;
    private:
        ID3D11ShaderResourceView* shader_resource_view;
        vector2i size;
    };
}

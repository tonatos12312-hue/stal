#pragma once

#include <d3d11.h>
#include <common/resource/image/image_resource_manager.h>

namespace common {

    class directx11_image_resource_manager final : public image_resource_manager {
    public:
        explicit directx11_image_resource_manager(ID3D11Device* device);

        ~directx11_image_resource_manager() override = default;
    public:
        image* create_image_from_file(const std::string_view& file_path) override;

        image* create_image_from_bytes(const std::vector<uint8_t>& bytes) override;
    private:
        ID3D11Device* device;
    };
}

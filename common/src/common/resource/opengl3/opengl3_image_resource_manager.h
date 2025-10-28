#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <common/resource/image/image_resource_manager.h>

namespace common {

    class opengl3_image_resource_manager final : public image_resource_manager {
    public:
        opengl3_image_resource_manager() = default;

        ~opengl3_image_resource_manager() override = default;
    public:
        image* create_image_from_file(const std::string_view& file_path) override;

        image* create_image_from_bytes(const std::vector<uint8_t>& bytes) override;
    };
}

#pragma once

#include <string_view>
#include <vector>
#include <cstdint>
#include <common/resource/image/image_resource_manager.h>
#include <common/resource/font/font_resource_manager.h>

namespace common {

    class resource_manager {
    public:
        explicit resource_manager(image_resource_manager* image_manager, font_resource_manager* font_manager);

        ~resource_manager() = default;
    public:
        image* create_image_from_file(const std::string_view& file_path);
        image* create_image_from_bytes(const std::vector<uint8_t>& bytes);

        font* create_font_from_file(const std::string_view& file_path, float size);
        font* create_font_from_bytes(const std::vector<uint8_t>& bytes, float size);
    private:
        image_resource_manager* image_manager;
        font_resource_manager* font_manager;
    };
}

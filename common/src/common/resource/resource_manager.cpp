#include "resource_manager.h"

namespace common {

    resource_manager::resource_manager(image_resource_manager* image_manager, font_resource_manager* font_manager) : image_manager(image_manager), font_manager(font_manager) {}

    image* resource_manager::create_image_from_file(const std::string_view& file_path) {
        return image_manager->create_image_from_file(file_path);
    }

    image* resource_manager::create_image_from_bytes(const std::vector<uint8_t>& bytes) {
        return image_manager->create_image_from_bytes(bytes);
    }

    font* resource_manager::create_font_from_file(const std::string_view& file_path, float size) {
        return font_manager->create_font_from_file(file_path, size);
    }

    font* resource_manager::create_font_from_bytes(const std::vector<uint8_t>& bytes, float size) {
        return font_manager->create_font_from_bytes(bytes, size);
    }
}

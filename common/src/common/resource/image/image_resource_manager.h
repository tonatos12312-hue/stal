#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "image.h"

namespace common {

    class image_resource_manager {
    public:
        virtual ~image_resource_manager() = default;
    public:
        virtual image* create_image_from_file(const std::string_view& file_path) = 0;

        virtual image* create_image_from_bytes(const std::vector<uint8_t>& bytes) = 0;
    };
}

#pragma once

#include <string_view>
#include <vector>
#include "font.h"

namespace common {

    class font_resource_manager {
    public:
        virtual ~font_resource_manager() = default;
    public:
        virtual font* create_font_from_file(const std::string_view& file_path, float size) = 0;

        virtual font* create_font_from_bytes(const std::vector<uint8_t>& bytes, float size) = 0;
    };
}

#pragma once

#include <imgui.h>
#include <common/resource/font/font_resource_manager.h>

namespace common {

    class imgui_font_resource_manager final : public font_resource_manager {
    public:
        imgui_font_resource_manager();

        ~imgui_font_resource_manager() override = default;
    public:
        font* create_font_from_file(const std::string_view& file_path, float size) override;

        font* create_font_from_bytes(const std::vector<uint8_t>& bytes, float size) override;
    };
}

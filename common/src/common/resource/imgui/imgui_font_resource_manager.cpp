#include "imgui_font_resource_manager.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include "imgui_font.h"

namespace common {

    imgui_font_resource_manager::imgui_font_resource_manager() {}

    font* imgui_font_resource_manager::create_font_from_file(const std::string_view& file_path, float size) {
        std::ifstream file(std::string(file_path), std::ios::binary | std::ios::ate);
        if (!file.is_open())
            throw std::runtime_error("Cannot open font file");

        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(file_size);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), file_size))
            throw std::runtime_error("Cannot read font file");

        return create_font_from_bytes(buffer, size);
    }

    font* imgui_font_resource_manager::create_font_from_bytes(const std::vector<uint8_t>& bytes, float size) {
        ImGuiIO& io = ImGui::GetIO();
        
        ptr font_data = IM_ALLOC(bytes.size());
        if (!font_data)
            throw std::runtime_error("Cannot allocate memory for font data");
        
        memcpy(font_data, bytes.data(), bytes.size());
        
        ImFont* font = io.Fonts->AddFontFromMemoryTTF(font_data, static_cast<int>(bytes.size()), size);
        if (!font) {
            IM_FREE(font_data);
            throw std::runtime_error("Cannot create font from bytes");
        }
        
        io.Fonts->Build();
        return new imgui_font(font);
    }
}

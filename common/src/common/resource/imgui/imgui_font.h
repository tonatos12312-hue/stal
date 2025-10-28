#pragma once

#include <imgui.h>
#include <common/resource/font/font.h>

namespace common {

    class imgui_font final : public font {
    public:
        explicit imgui_font(ImFont* font);
    public:
        ptr get_font() const override;
    private:
        ImFont* font;
    };
}

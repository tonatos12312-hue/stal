#include "imgui_font.h"

namespace common {

    imgui_font::imgui_font(ImFont* font) : font(font) {}

    ptr imgui_font::get_font() const {
        return font;
    }
}

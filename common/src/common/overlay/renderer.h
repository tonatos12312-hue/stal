#pragma once

#include <string_view>
#include <string>
#include <imgui.h>
#include <common/math/vector2.h>

// Credits for HEX_TO_IMCOL32 to Basic
#define IM_TRUNC(_VAL) ((float)(int)(_VAL)) // ImTrunc() is not inl…

constexpr byte HEX_LUT[256] = {
    0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00-0x0F
    0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x10-0x1F
    0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x20-0x2F
    0, 1,  2,  3,  4,  5,  6,  7, 8, 9, 0, 0, 0, 0, 0, 0, // 0x30-0x3F ('0'-'9')
    0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x40-0x4F ('A'-'F')
    0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x50-0x5F
    0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x60-0x6F ('a'-'f')
    0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x70-0x7F
    // Rest filled with zeros...
};

constexpr byte HEX_TO_DEC(char c) {
    return HEX_LUT[static_cast<unsigned char>(c)];
}

constexpr byte HEX_PAIR_TO_DEC(char c1, char c2) {
    return (HEX_TO_DEC(c1) << 4) | HEX_TO_DEC(c2);
}

constexpr ImU32 HEX_TO_IMCOL32(const char* hex) {
    const char* p = hex[0] == '#' ? hex + 1 : hex;

    // Verify we have at least 6 characters for RGB
    if (!p[0] || !p[1] || !p[2] || !p[3] || !p[4] || !p[5]) {
        return IM_COL32(0, 0, 0, 255);
    }

    const byte r = HEX_PAIR_TO_DEC(p[0], p[1]);
    const byte g = HEX_PAIR_TO_DEC(p[2], p[3]);
    const byte b = HEX_PAIR_TO_DEC(p[4], p[5]);
    const byte a = p[6] && p[7] ? HEX_PAIR_TO_DEC(p[6], p[7]) : 255;

    return IM_COL32(r, g, b, a);
}

class renderer {
public:
   explicit renderer(ImDrawList* list, const vector2f& origin, float alpha_modifier = 1.0f) : list(list), origin(origin), alpha_modifier(alpha_modifier) {}
public:
   void circle(const vector2f& position, float radius, ImColor color) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddCircleFilled(ImVec2(origin.x + position.x, origin.y + position.y), radius, modified_color);
   }

   void stroke_circle(const vector2f& position, float radius, ImColor color) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddCircle(ImVec2(origin.x + position.x, origin.y + position.y), radius, modified_color);
   }

    void rect(const vector2f& position, const vector2f& size, ImColor color, float rounding = 0.0f, ImDrawFlags flags = 0) const {
        ImU32 modified_color = apply_alpha_modifier(color);
        list->AddRectFilled(ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y), modified_color, rounding, flags);
    }

    void gradient(const vector2f& position, const vector2f& size, ImColor top_left_color, ImColor top_right_color, ImColor bottom_left_color, ImColor bottom_right_color) const {
        ImU32 top_left = apply_alpha_modifier(top_left_color);
        ImU32 top_right = apply_alpha_modifier(top_right_color);
        ImU32 bottom_left = apply_alpha_modifier(bottom_left_color);
        ImU32 bottom_right = apply_alpha_modifier(bottom_right_color);
        list->AddRectFilledMultiColor(ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y), top_left, top_right, bottom_left, bottom_right);
    }

   void stroke(const vector2f& position, const vector2f& size, ImColor color, float rounding = 0.0f) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddRect(ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y), modified_color, rounding);
   }

   bool hovering(const vector2f& position, const vector2f& size) const {
       return ImGui::IsMouseHoveringRect(ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y));
   }

   void image(ImTextureID texture, const vector2f& position, const vector2f& size, ImColor color = IM_COL32_WHITE) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddImage(texture, ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y), ImVec2(0, 0), ImVec2(1, 1), modified_color);
   }

   void image_rounded(ImTextureID texture, const vector2f& position, const vector2f& size, float rounding, ImColor color = IM_COL32_WHITE) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddImageRounded(texture, ImVec2(origin.x + position.x, origin.y + position.y), ImVec2(origin.x + position.x + size.x, origin.y + position.y + size.y), ImVec2(0, 0), ImVec2(1, 1), modified_color, rounding);
   }

   void text(const ImFont* font, const std::string_view& text, const vector2f& position, ImColor color = IM_COL32_WHITE) const {
       ImU32 modified_color = apply_alpha_modifier(color);
       list->AddText(font, font->FontSize, ImVec2(origin.x + position.x, origin.y + position.y), modified_color, std::string(text).c_str());
   }

   static vector2f text_size(ImFont* font, const std::string_view& text) {
       ImGui::PushFont(font);
       const ImVec2 size = ImGui::CalcTextSize(std::string(text).c_str());
       ImGui::PopFont();

       return vector2f(size.x, size.y);
   }
public:
   renderer translated(const vector2f& offset, float modifier = 1.0f) const {
       return renderer(list, origin + offset, alpha_modifier * modifier);
   }

   vector2f anchor() const {
       return origin;
   }

   void set_alpha_modifier(float alpha_modifier) {
       this->alpha_modifier = alpha_modifier;
   }
private:
    ImU32 apply_alpha_modifier(ImColor color) const {
        const float r = color >> IM_COL32_R_SHIFT & 0xFF;
        const float g = color >> IM_COL32_G_SHIFT & 0xFF;
        const float b = color >> IM_COL32_B_SHIFT & 0xFF;
        const float a = color >> IM_COL32_A_SHIFT & 0xFF;

        return IM_COL32(
            static_cast<int>(r),
            static_cast<int>(g),
            static_cast<int>(b),
            static_cast<int>(a * alpha_modifier)
        );
    }
private:
   ImDrawList* list;
   vector2f origin;
   float alpha_modifier;
};

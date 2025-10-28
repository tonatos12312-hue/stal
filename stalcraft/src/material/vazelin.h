#pragma once

#include <imgui.h>

#include "material.h"

class glow_material final : public material {
public:
    glow_material() = default;
public:
    const std::string_view name() const override;

    void draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) override;
};

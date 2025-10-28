#pragma once

#include <string_view>
#include <Windows.h>
#include <gl/GL.h>
#include <imgui.h>

typedef void(*gl_draw_elements_fn)(GLenum, GLsizei, GLenum, const void*);

class material {
public:
    virtual ~material() = default;
public:
    virtual const std::string_view name() const = 0;

    virtual void draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) = 0;
};

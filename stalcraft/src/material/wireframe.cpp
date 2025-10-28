#include "wireframe.h"

#include <algorithm>
#include <string>
#include <vector>
#include "gl_constants.h"

const std::string_view wireframe_material::name() const {
    return "Wireframe";
}

void wireframe_material::draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) {
    if (!original) {
        return;
    }

    if (shaderProgram == 0) {
        return;
    }

    if (count <= 0 || !indices) {
        return;
    }

    if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT) {
        return;
    }

    GLint current_program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
    if (current_program != shaderProgram) {
        return;
    }

    GLint emission_color_location = glGetUniformLocation(shaderProgram, "emissionColor");
    GLint diffuse_color_location = glGetUniformLocation(shaderProgram, "diffuseColor");
    GLint specular_color_location = glGetUniformLocation(shaderProgram, "specularColor");
    GLint light_sun_color_location = glGetUniformLocation(shaderProgram, "g_LightSunColor");

    GLfloat backup_emission_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_diffuse_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_specular_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_light_sun_color[3] = {0.0f, 0.0f, 0.0f};

    GLfloat backup_depth_range[2] = {0.0f, 1.0f};
    GLint backup_depth_func = GL_LESS;
    GLfloat backup_line_width = 1.0f;
    GLint backup_texture = 0;

    constexpr GLint MAX_TEXTURES = 32;
    GLint num_textures = min(MAX_TEXTURES, 99);
    std::vector<GLint> saved_samplers(num_textures, -1);
    std::vector<GLuint> saved_textures(num_textures, 0);

    GLfloat backup_blend_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLint backup_blend_src = GL_ONE;
    GLint backup_blend_dst = GL_ZERO;
    GLboolean backup_blend_enabled = GL_FALSE;
    GLboolean backup_depth_enabled = GL_TRUE;

    glGetFloatv(GL_BLEND_COLOR, backup_blend_color);
    glGetIntegerv(GL_BLEND_SRC, &backup_blend_src);
    glGetIntegerv(GL_BLEND_DST, &backup_blend_dst);
    backup_blend_enabled = glIsEnabled(GL_BLEND);
    backup_depth_enabled = glIsEnabled(GL_DEPTH_TEST);

    if (emission_color_location != -1) {
        glGetUniformfv(shaderProgram, emission_color_location, backup_emission_color);
    }
    if (diffuse_color_location != -1) {
        glGetUniformfv(shaderProgram, diffuse_color_location, backup_diffuse_color);
    }
    if (specular_color_location != -1) {
        glGetUniformfv(shaderProgram, specular_color_location, backup_specular_color);
    }
    if (light_sun_color_location != -1) {
        glGetUniformfv(shaderProgram, light_sun_color_location, backup_light_sun_color);
    }

    glGetFloatv(GL_DEPTH_RANGE, backup_depth_range);
    glGetIntegerv(GL_DEPTH_FUNC, &backup_depth_func);
    glGetFloatv(GL_LINE_WIDTH, &backup_line_width);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &backup_texture);

    float r = std::clamp(color.Value.x, 0.0f, 1.0f);
    float g = std::clamp(color.Value.y, 0.0f, 1.0f);
    float b = std::clamp(color.Value.z, 0.0f, 1.0f);
    float a = std::clamp(color.Value.w, 0.0f, 1.0f);

    {
        static GLuint wireframe_texture = 0;
        if (!wireframe_texture) {
            glGenTextures(1, &wireframe_texture);
            if (!wireframe_texture) {
                return;
            }
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        GLfloat safe_blend_r = std::clamp(r * 0.0f, 0.0f, 1.0f);
        GLfloat safe_blend_g = std::clamp(g * 1.0f, 0.0f, 1.0f);
        GLfloat safe_blend_b = std::clamp(b * 0.5f, 0.0f, 1.0f);
        GLfloat safe_blend_a = std::clamp(a * 1.0f, 0.0f, 1.0f);
        glBlendColor(safe_blend_r, safe_blend_g, safe_blend_b, safe_blend_a);

        if (emission_color_location != -1) {
            GLfloat safe_emission_r = std::clamp(r * 0.5f, 0.0f, 10.0f);
            GLfloat safe_emission_g = std::clamp(g * 2.0f, 0.0f, 10.0f);
            GLfloat safe_emission_b = std::clamp(b * 1.0f, 0.0f, 10.0f);
            glUniform3f(emission_color_location, safe_emission_r, safe_emission_g, safe_emission_b);
        }

        if (diffuse_color_location != -1) {
            GLfloat safe_diffuse_r = std::clamp(r * 0.1f, 0.0f, 1.0f);
            GLfloat safe_diffuse_g = std::clamp(g * 0.8f, 0.0f, 1.0f);
            GLfloat safe_diffuse_b = std::clamp(b * 0.4f, 0.0f, 1.0f);
            glUniform3f(diffuse_color_location, safe_diffuse_r, safe_diffuse_g, safe_diffuse_b);
        }

        if (specular_color_location != -1) {
            GLfloat safe_specular_r = std::clamp(r * 0.3f, 0.0f, 1.0f);
            GLfloat safe_specular_g = std::clamp(g * 1.5f, 0.0f, 1.0f);
            GLfloat safe_specular_b = std::clamp(b * 0.8f, 0.0f, 1.0f);
            glUniform3f(specular_color_location, safe_specular_r, safe_specular_g, safe_specular_b);
        }

        if (light_sun_color_location != -1) {
            GLfloat safe_light_r = std::clamp(r * 0.8f, 0.0f, 10.0f);
            GLfloat safe_light_g = std::clamp(g * 2.5f, 0.0f, 10.0f);
            GLfloat safe_light_b = std::clamp(b * 1.2f, 0.0f, 10.0f);
            glUniform3f(light_sun_color_location, safe_light_r, safe_light_g, safe_light_b);
        }

        unsigned char wireframe_color[4] = {
            static_cast<unsigned char>(std::clamp(r * 255.0f, 0.0f, 255.0f)),
            static_cast<unsigned char>(std::clamp(g * 255.0f, 0.0f, 255.0f)),
            static_cast<unsigned char>(std::clamp(b * 255.0f, 0.0f, 255.0f)),
            static_cast<unsigned char>(std::clamp(a * 255.0f, 0.0f, 255.0f))
        };

        glDepthRange(0.0, 0.0);

        num_textures = 99;

        for (GLint i = 0; i < num_textures; ++i) {
            std::string uniform_name = "usedTextures[" + std::to_string(i) + "]";
            if (uniform_name.length() > 256) {
                break;
            }

            GLint location = glGetUniformLocation(shaderProgram, uniform_name.c_str());
            if (location == -1) {
                continue;
            }

            GLint sampler = -1;
            glGetUniformiv(shaderProgram, location, &sampler);

            if (sampler < 0) {
                continue;
            }

            glActiveTexture(GL_TEXTURE0 + sampler);

            GLint bound_texture = 0;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);
            saved_samplers[i] = sampler;
            saved_textures[i] = bound_texture;

            glBindTexture(GL_TEXTURE_2D, wireframe_texture);

            GLenum error = glGetError();
            if (error == GL_NO_ERROR) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, wireframe_color);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
        }

        glDisable(GL_DEPTH_TEST);
        GLfloat safe_line_width = std::clamp(1.0f, 0.1f, 10.0f);
        glLineWidth(safe_line_width);

        GLenum error = glGetError();
        if (error == GL_NO_ERROR) {
            original(GL_LINES, count, type, indices);
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        safe_line_width = std::clamp(0.5f, 0.1f, 10.0f);
        glLineWidth(safe_line_width);

        error = glGetError();
        if (error == GL_NO_ERROR) {
            original(GL_LINES, count, type, indices);
        }
    }

    if (emission_color_location != -1) {
        glUniform3f(emission_color_location, backup_emission_color[0], backup_emission_color[1], backup_emission_color[2]);
    }
    if (diffuse_color_location != -1) {
        glUniform3f(diffuse_color_location, backup_diffuse_color[0], backup_diffuse_color[1], backup_diffuse_color[2]);
    }
    if (specular_color_location != -1) {
        glUniform3f(specular_color_location, backup_specular_color[0], backup_specular_color[1], backup_specular_color[2]);
    }
    if (light_sun_color_location != -1) {
        glUniform3f(light_sun_color_location, backup_light_sun_color[0], backup_light_sun_color[1], backup_light_sun_color[2]);
    }

    glDepthRange(backup_depth_range[0], backup_depth_range[1]);
    glDepthFunc(backup_depth_func);
    glLineWidth(backup_line_width);

    if (backup_blend_enabled) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }

    glBlendColor(backup_blend_color[0], backup_blend_color[1], backup_blend_color[2], backup_blend_color[3]);
    glBlendFunc(backup_blend_src, backup_blend_dst);

    for (GLint i = 0; i < num_textures; ++i) {
        GLint sampler = saved_samplers[i];
        GLuint texture = saved_textures[i];

        if (sampler >= 0) {
            glActiveTexture(GL_TEXTURE0 + sampler);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
    }

    if (!backup_depth_enabled) {
        glDisable(GL_DEPTH_TEST);
    }
}

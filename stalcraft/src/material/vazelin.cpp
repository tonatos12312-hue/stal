#include "vazelin.h"

#include "stb_image.h"

#include <algorithm>
#include <string>
#include <vector>
#include "gl_constants.h"

static GLuint player_texture = 0;
static bool texture_initialized = false;

const char* replacement_fragment_shader = R"(
#version 330 core

in vec2 textureCoordsVert;

uniform sampler2D playerTexture;
uniform vec3 glowColor;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(playerTexture, textureCoordsVert);
    FragColor = vec4(texColor.rgb * glowColor, texColor.a);
}
)";

void initialize_player_texture() {
    if (!texture_initialized) {
        if (!dataaa || sizeof(dataaa) == 0) {
            return;
        }

        int width, height, channels;
        unsigned char* image_data = stbi_load_from_memory(dataaa, sizeof(dataaa), &width, &height, &channels, 4);

        if (!image_data) {
            return;
        }

        if (width <= 0 || height <= 0 || width > 8192 || height > 8192) {
            stbi_image_free(image_data);
            return;
        }

        glGenTextures(1, &player_texture);
        if (!player_texture) {
            stbi_image_free(image_data);
            return;
        }

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            stbi_image_free(image_data);
            return;
        }

        glBindTexture(GL_TEXTURE_2D, player_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

        error = glGetError();
        if (error != GL_NO_ERROR) {
            glDeleteTextures(1, &player_texture);
            player_texture = 0;
            stbi_image_free(image_data);
            return;
        }

        stbi_image_free(image_data);
        texture_initialized = true;
    }
}

const std::string_view glow_material::name() const {
    return "Vazelin";
}

void glow_material::draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) {
    if (!original) {
        return;
    }

    if (shaderProgram == 0) {
        return;
    }

    if (count <= 0) {
        return;
    }

    if (!indices) {
        return;
    }

    initialize_player_texture();

    if (!texture_initialized || !player_texture) {
        return;
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        return;
    }

    GLint backup_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &backup_texture);

    const GLint MAX_TEXTURES = 32;
    GLint num_textures = min(MAX_TEXTURES, 10);
    std::vector<GLint> saved_samplers(num_textures, -1);
    std::vector<GLuint> saved_textures(num_textures, 0);

    for (GLint i = 0; i < num_textures; ++i) {
        std::string uniformName = "usedTextures[" + std::to_string(i) + "]";
        GLint location = glGetUniformLocation(shaderProgram, uniformName.c_str());
        if (location == -1)
            continue;

        GLint sampler = -1;
        glGetUniformiv(shaderProgram, location, &sampler);

        if (sampler < 0) {
            continue;
        }

        GLint bound_texture = 0;
        glActiveTexture(GL_TEXTURE0 + sampler);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);

        saved_samplers[i] = sampler;
        saved_textures[i] = bound_texture;

        glBindTexture(GL_TEXTURE_2D, player_texture);

        error = glGetError();
        if (error != GL_NO_ERROR) {
            goto cleanup;
        }
    }

    GLint glow_color_location = glGetUniformLocation(shaderProgram, "diffuseColor");
    if (glow_color_location != -1) {
        float r = std::clamp(color.Value.x, 0.0f, 1.0f);
        float g = std::clamp(color.Value.y, 0.0f, 1.0f);
        float b = std::clamp(color.Value.z, 0.0f, 1.0f);

        glUniform3f(glow_color_location, r, g, b);
    }

    error = glGetError();
    if (error != GL_NO_ERROR) {
        goto cleanup;
    }

    original(mode, count, type, indices);

cleanup:
    for (GLint i = 0; i < num_textures; ++i) {
        GLint sampler = saved_samplers[i];
        GLuint texture = saved_textures[i];

        if (sampler >= 0) {
            glActiveTexture(GL_TEXTURE0 + sampler);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
    }

    glBindTexture(GL_TEXTURE_2D, backup_texture);
}

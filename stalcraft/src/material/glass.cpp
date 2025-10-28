#include "glass.h"

#include <algorithm>
#include <string>
#include <vector>
#include "gl_constants.h"

const std::string_view glass_material::name() const {
    return "Glass";
}

void glass_material::draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) {
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

    GLint emission_color_location = glGetUniformLocation(shaderProgram, "emissionColor");
    GLint diffuse_color_location = glGetUniformLocation(shaderProgram, "diffuseColor");
    GLint specular_color_location = glGetUniformLocation(shaderProgram, "specularColor");
    GLint light_sun_color_location = glGetUniformLocation(shaderProgram, "g_LightSunColor");
    GLint light_exposure_location = glGetUniformLocation(shaderProgram, "g_LightExposure");
    GLint lightmap_color_location = glGetUniformLocation(shaderProgram, "lightmapColorAndSkylight");

    if (emission_color_location == -1 || diffuse_color_location == -1 || 
        specular_color_location == -1 || light_sun_color_location == -1) {
        return;
    }

    GLfloat backup_emission_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_diffuse_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_specular_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_light_sun_color[3] = {0.0f, 0.0f, 0.0f};
    GLfloat backup_light_exposure = 1.0f;
    GLfloat backup_lightmap_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    GLfloat backup_depth_range[2] = {0.0f, 1.0f};
    GLint backup_depth_func = GL_LESS;

    GLint backup_texture = 0;

    const GLint MAX_TEXTURES = 32;
    GLint num_textures = min(MAX_TEXTURES, 99);
    std::vector<GLint> saved_samplers(num_textures, -1);
    std::vector<GLuint> saved_textures(num_textures, 0);

    GLfloat backup_blend_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLint backup_blend_src = GL_ONE;
    GLint backup_blend_dst = GL_ZERO;

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        return;
    }

    glGetFloatv(GL_BLEND_COLOR, backup_blend_color);
    glGetIntegerv(GL_BLEND_SRC, &backup_blend_src);
    glGetIntegerv(GL_BLEND_DST, &backup_blend_dst);

    glGetUniformfv(shaderProgram, emission_color_location, backup_emission_color);
    glGetUniformfv(shaderProgram, diffuse_color_location, backup_diffuse_color);
    glGetUniformfv(shaderProgram, specular_color_location, backup_specular_color);
    glGetUniformfv(shaderProgram, light_sun_color_location, backup_light_sun_color);

    if (light_exposure_location != -1)
        glGetUniformfv(shaderProgram, light_exposure_location, &backup_light_exposure);
    if (lightmap_color_location != -1)
        glGetUniformfv(shaderProgram, lightmap_color_location, backup_lightmap_color);

    glGetFloatv(GL_DEPTH_RANGE, backup_depth_range);
    glGetIntegerv(GL_DEPTH_FUNC, &backup_depth_func);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &backup_texture);

    float r = std::clamp(color.Value.x, 0.0f, 1.0f);
    float g = std::clamp(color.Value.y, 0.0f, 1.0f);
    float b = std::clamp(color.Value.z, 0.0f, 1.0f);
    float a = std::clamp(color.Value.w, 0.0f, 1.0f);

    {
        static GLuint glow_texture = 0;
        if (!glow_texture) {
            glGenTextures(1, &glow_texture);
            if (!glow_texture) {
                return;
            }
        }

        error = glGetError();
        if (error != GL_NO_ERROR) {
            return;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBlendColor(r * 0.3f, g * 0.4f, b * 1.0f, a * 0.8f);

        glUniform3f(diffuse_color_location, r * 0.05f, g * 0.15f, b * 0.4f);
        glUniform3f(emission_color_location, 
                   min(r * 0.3f, 1.0f), 
                   min(g * 0.7f, 1.0f), 
                   min(b * 1.8f, 1.0f));
        glUniform3f(specular_color_location, 
                   min(r * 0.4f, 1.0f), 
                   min(g * 0.8f, 1.0f), 
                   min(b * 1.5f, 1.0f));
        glUniform3f(light_sun_color_location, 
                   min(r * 0.6f, 1.0f), 
                   min(g * 1.2f, 1.0f), 
                   min(b * 2.0f, 1.0f));

        if (light_exposure_location != -1)
            glUniform1f(light_exposure_location, 2.5f);
        if (lightmap_color_location != -1)
            glUniform4f(lightmap_color_location, 
                       min(r * 0.4f, 1.0f), 
                       min(g * 0.8f, 1.0f), 
                       min(b * 1.6f, 1.0f), 
                       1.0f);

        unsigned char glow_gradient[64];
        for (int i = 0; i < 16; i++) {
            if (i >= 16) break;
            
            float intensity = 1.0f - (i / 15.0f);
            intensity = std::clamp(intensity * intensity, 0.0f, 1.0f);

            glow_gradient[i * 4 + 0] = (unsigned char)std::clamp(r * 255.0f * intensity, 0.0f, 255.0f);
            glow_gradient[i * 4 + 1] = (unsigned char)std::clamp(g * 255.0f * intensity, 0.0f, 255.0f);
            glow_gradient[i * 4 + 2] = (unsigned char)std::clamp(b * 255.0f * intensity, 0.0f, 255.0f);
            glow_gradient[i * 4 + 3] = (unsigned char)std::clamp(a * 255.0f * intensity, 0.0f, 255.0f);
        }

        glDepthRange(0.0, 0.0);

        error = glGetError();
        if (error != GL_NO_ERROR) {
            goto cleanup;
        }

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

            glActiveTexture(GL_TEXTURE0 + sampler);

            GLint bound_texture = 0;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);
            saved_samplers[i] = sampler;
            saved_textures[i] = bound_texture;

            glBindTexture(GL_TEXTURE_2D, glow_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, glow_gradient);
            
            error = glGetError();
            if (error != GL_NO_ERROR) {
                goto cleanup;
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }

    error = glGetError();
    if (error != GL_NO_ERROR) {
        goto cleanup;
    }

    original(mode, count, type, indices);

cleanup:
    if (emission_color_location != -1)
        glUniform3f(emission_color_location, backup_emission_color[0], backup_emission_color[1], backup_emission_color[2]);
    if (diffuse_color_location != -1)
        glUniform3f(diffuse_color_location, backup_diffuse_color[0], backup_diffuse_color[1], backup_diffuse_color[2]);
    if (specular_color_location != -1)
        glUniform3f(specular_color_location, backup_specular_color[0], backup_specular_color[1], backup_specular_color[2]);
    if (light_sun_color_location != -1)
        glUniform3f(light_sun_color_location, backup_light_sun_color[0], backup_light_sun_color[1], backup_light_sun_color[2]);

    if (light_exposure_location != -1)
        glUniform1f(light_exposure_location, backup_light_exposure);
    if (lightmap_color_location != -1)
        glUniform4f(lightmap_color_location, backup_lightmap_color[0], backup_lightmap_color[1], backup_lightmap_color[2], backup_lightmap_color[3]);

    glDepthRange(backup_depth_range[0], backup_depth_range[1]);
    glDepthFunc(backup_depth_func);

    glEnable(GL_BLEND);
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

    glBindTexture(GL_TEXTURE_2D, backup_texture);
}

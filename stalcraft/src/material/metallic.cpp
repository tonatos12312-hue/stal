#include "metallic.h"

#include <string>
#include <vector>
#include "gl_constants.h"

const std::string_view metallic_material::name() const {
    return "Metallic";
}

void metallic_material::draw(gl_draw_elements_fn original, GLint shaderProgram, ImColor color, GLenum mode, GLsizei count, GLenum type, const void* indices) {
    GLint emissionColorLocation = glGetUniformLocation(shaderProgram, "emissionColor");
    GLint diffuseColorLocation = glGetUniformLocation(shaderProgram, "diffuseColor");
    GLint specularColorLocation = glGetUniformLocation(shaderProgram, "specularColor");
    GLint lightSunColorLocation = glGetUniformLocation(shaderProgram, "g_LightSunColor");
    GLint specularExponentLocation = glGetUniformLocation(shaderProgram, "specularExponent");
    GLint lightExposureLocation = glGetUniformLocation(shaderProgram, "g_LightExposure");
    if (emissionColorLocation == -1 || diffuseColorLocation == -1 || specularColorLocation == -1 || lightSunColorLocation == -1 || specularExponentLocation == -1 || lightExposureLocation == -1)
        return;

    GLfloat backup_emission_color[3];
    GLfloat backup_diffuse_color[3];
    GLfloat backup_specular_color[3];
    GLfloat backup_light_sun_color[3];
    GLfloat backup_specular_exponent;
    GLfloat backup_light_exposure;

    GLfloat backup_depth_range[2];
    GLint backup_depth_func;

    GLint backup_texture;

    GLint texturedCount = 99;
    std::vector<GLint> saved_samplers(texturedCount);
    std::vector<GLuint> saved_textures(texturedCount);

    GLfloat backup_blend_color[4];
    GLint backup_blend_src, backup_blend_dst;

    glGetFloatv(GL_BLEND_COLOR, backup_blend_color);
    glGetIntegerv(GL_BLEND_SRC, &backup_blend_src);
    glGetIntegerv(GL_BLEND_DST, &backup_blend_dst);

    glGetUniformfv(shaderProgram, emissionColorLocation, backup_emission_color);
    glGetUniformfv(shaderProgram, diffuseColorLocation, backup_diffuse_color);
    glGetUniformfv(shaderProgram, specularColorLocation, backup_specular_color);
    glGetUniformfv(shaderProgram, lightSunColorLocation, backup_light_sun_color);

    glGetUniformfv(shaderProgram, specularExponentLocation, &backup_specular_exponent);
    glGetUniformfv(shaderProgram, lightExposureLocation, &backup_light_exposure);

    glGetFloatv(GL_DEPTH_RANGE, backup_depth_range);
    glGetIntegerv(GL_DEPTH_FUNC, &backup_depth_func);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &backup_texture);

    float r = color.Value.x;
    float g = color.Value.y;
    float b = color.Value.z;

    static GLuint metallic_texture = 0;
    if (!metallic_texture)
        glGenTextures(1, &metallic_texture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendColor(r * 0.8f, g * 0.8f, b * 0.8f, 0.9f);

    glUniform3f(diffuseColorLocation, r * 0.6f, g * 0.6f, b * 0.6f);
    glUniform3f(specularColorLocation, r + 0.3f, g + 0.3f, b + 0.3f);
    glUniform3f(emissionColorLocation, r * 0.2f, g * 0.2f, b * 0.2f);
    glUniform3f(lightSunColorLocation, 1.2f, 0.8f + r * 0.4f, 0.8f + g * 0.4f);

    glUniform1f(specularExponentLocation, 128.0f);
    glUniform1f(lightExposureLocation, 1.5f);

    unsigned char metallicData[16] = {
        (unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255), 255,
        (unsigned char)(r * 220), (unsigned char)(g * 220), (unsigned char)(b * 220), 255,
        (unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255), 255,
        (unsigned char)(r * 200), (unsigned char)(g * 200), (unsigned char)(b * 200), 255
    };

    glDepthRange(0.0, 0.0);

    for (GLint i = 0; i < texturedCount; i++) {
        GLint location = glGetUniformLocation(shaderProgram, ("usedTextures[" + std::to_string(i) + "]").c_str());
        if (location == -1)
            continue;

        GLint sampler;
        glGetUniformiv(shaderProgram, location, &sampler);
        glActiveTexture(GL_TEXTURE0 + sampler);

        GLint bound_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);
        saved_samplers[i] = sampler;
        saved_textures[i] = bound_texture;

        glBindTexture(GL_TEXTURE_2D, metallic_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, metallicData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    original(mode, count, type, indices);

    glUniform3f(emissionColorLocation, backup_emission_color[0], backup_emission_color[1], backup_emission_color[2]);
    glUniform3f(diffuseColorLocation, backup_diffuse_color[0], backup_diffuse_color[1], backup_diffuse_color[2]);
    glUniform3f(specularColorLocation, backup_specular_color[0], backup_specular_color[1], backup_specular_color[2]);
    glUniform3f(lightSunColorLocation, backup_light_sun_color[0], backup_light_sun_color[1], backup_light_sun_color[2]);

    glUniform1f(specularExponentLocation, backup_specular_exponent);
    glUniform1f(lightExposureLocation, backup_light_exposure);

    glDepthRange(backup_depth_range[0], backup_depth_range[1]);
    glDepthFunc(backup_depth_func);

    glEnable(GL_BLEND);
    glBlendColor(backup_blend_color[0], backup_blend_color[1], backup_blend_color[2], backup_blend_color[3]);
    glBlendFunc(backup_blend_src, backup_blend_dst);

    for (GLint i = 0; i < texturedCount; i++) {
        GLint sampler = saved_samplers[i];
        GLuint texture = saved_textures[i];

        if (sampler != -1) {
            glActiveTexture(GL_TEXTURE0 + sampler);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
    }
}

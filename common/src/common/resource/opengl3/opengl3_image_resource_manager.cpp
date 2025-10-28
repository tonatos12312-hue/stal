#include "opengl3_image_resource_manager.h"

#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "opengl3_image.h"

typedef void (APIENTRY *PFNGLGENERATEMIPMAPPROC) (GLenum target);
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;

namespace common {

    static void init_gl_extensions() {
        if (!glGenerateMipmap)
            glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(wglGetProcAddress("glGenerateMipmap"));
    }

    image* opengl3_image_resource_manager::create_image_from_file(const std::string_view& file_path) {
        init_gl_extensions();

        int width, height, channels;
        unsigned char* data = stbi_load(std::string(file_path).c_str(), &width, &height, &channels, 0);

        if (!data)
            throw std::runtime_error("Cannot load image from file");

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        GLenum format = GL_RGB;
        if (channels == 4)
            format = GL_RGBA;
        else if (channels == 1)
            format = GL_LUMINANCE;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        if (glGenerateMipmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        vector2i size(width, height);
        return new opengl3_image(texture_id, size);
    }

    image* opengl3_image_resource_manager::create_image_from_bytes(const std::vector<uint8_t>& bytes) {
        init_gl_extensions();

        int width, height, channels;
        unsigned char* data = stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &width, &height, &channels, 0);

        if (!data)
            throw std::runtime_error("Cannot load image from bytes");

        int row_size = width * 4;
        std::vector<unsigned char> flipped_data(width * height * 4);

        for (int y = 0; y < height; y++) {
            memcpy(&flipped_data[y * row_size], &data[(height - 1 - y) * row_size], row_size);
        }

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, flipped_data.data());
        stbi_image_free(data);

        vector2i size(width, height);
        return new opengl3_image(texture_id, size);
    }
}

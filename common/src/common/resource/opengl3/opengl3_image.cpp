#include "opengl3_image.h"

namespace common {

    opengl3_image::opengl3_image(GLuint texture_id, const vector2i& size) : texture_id(texture_id), size(size) {}

    opengl3_image::~opengl3_image() {
        if (texture_id != 0)
            glDeleteTextures(1, &texture_id);
    }

    vector2i opengl3_image::get_size() const {
        return size;
    }

    GLuint opengl3_image::get_texture_id() const {
        return texture_id;
    }

    ptr opengl3_image::get_texture() const {
        return reinterpret_cast<ptr>(texture_id);
    }
}

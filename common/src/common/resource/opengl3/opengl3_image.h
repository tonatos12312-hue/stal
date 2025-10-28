#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <common/resource/image/image.h>

namespace common {

    class opengl3_image final : public image {
    public:
        explicit opengl3_image(GLuint texture_id, const vector2i& size);

        ~opengl3_image() override;
    public:
        vector2i get_size() const override;

        GLuint get_texture_id() const;

        ptr get_texture() const override;
    private:
        GLuint texture_id;
        vector2i size;
    };
}

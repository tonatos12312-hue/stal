#pragma once

#include <common/math/vector2.h>
#include <common/resource/resource.h>

namespace common {

    class image : public resource {
    public:
        image() : resource(resource_type::image) {}

        ~image() override = default;
    public:
        virtual vector2i get_size() const = 0;

        virtual ptr get_texture() const = 0;
    };
}

#pragma once

#include <common/resource/resource.h>

namespace common {

    class font : public resource {
    public:
        font() : resource(resource_type::font) {}

        ~font() override = default;
    public:
        virtual ptr get_font() const = 0;
    };
}

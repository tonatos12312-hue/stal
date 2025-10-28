#pragma once

#include <string_view>
#include <vector>
#include <common/resource/image/image.h>
#include <common/cheat/feature/setting/frame.h>

namespace common {

    class feature {
    public:
        explicit feature(const std::string_view& name, image* icon);

        virtual ~feature();
    public:
        virtual void tick() = 0;
    public:
        std::string_view display_name() const {
            return name;
        }

        image* menu_icon() const {
            return icon;
        }

        std::vector<frame> frames() const {
            return frame_vector;
        }

        void add_frame(const frame& frame) {
            frame_vector.push_back(frame);
        }
    private:
        std::string_view name;
        image* icon;
        std::vector<frame> frame_vector;
    };
}

#pragma once

#include <vector>
#include <common/cheat/feature/feature.h>

namespace common {

    class cheat {
    public:
        virtual ~cheat() = default;
    public:
        virtual int start() = 0;

        virtual void unload() = 0;
    public:
        void register_feature(feature* feature) {
            features.push_back(feature);
        }

        std::vector<feature*> all_features() {
            return features;
        }
    public:
        std::vector<feature*> features{};
    };
}

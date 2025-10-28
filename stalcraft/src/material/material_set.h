#pragma once

#include <set>
#include <string_view>
#include <algorithm>
#include "metallic.h"
#include "glass.h"
#include "wireframe.h"
#include "vazelin.h"

namespace material_set {

    inline std::set<material*> materials;

    __forceinline material* find_by_name(std::string_view name) {
        auto it = std::find_if(materials.begin(), materials.end(), [name](const material* material) {
            return material->name() == name;
        });

        return (it != materials.end()) ? *it : nullptr;
    }

    __forceinline void init() {
        materials = {
            new metallic_material,
            new glass_material,
            new wireframe_material,
            new glow_material
        };
    }
}

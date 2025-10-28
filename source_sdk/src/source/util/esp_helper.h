#pragma once

#include <optional>
#include <common/memory/local_ptr.h>
#include <source/classes/classes.h>

namespace source::esp_helper {

    inlined std::optional<rect> make_rect(common::local_ptr<c_baseentity> entity) {
        const common::local_ptr<c_collision_property> collision = entity->collision();
        if (!collision.get())
            return std::nullopt;

        const c_transform transform = entity->scene_node()->node_to_world();
        axis_aligned_bounding_box aabb(collision->minimum(), collision->maximum());
        aabb.maximum.z = collision->surrounding_maximum().z;

        vector3f *vertices = aabb.vertices();
        for (int i = 0; i < 8; i++) {
            vector3f &point = vertices[i];

            matrix3x4 matrix{};
            common::rotate_matrix(matrix, transform.rotation);
            common::translate_matrix(matrix, transform.position);

            point = (point * matrix);
        }

        vector2f screenVertices[8];
        for (int i = 0; i < 8; i++)
            if (!common::world_to_screen(vertices[i], screenVertices[i]))
                return std::nullopt;

        const vector2f frontLeftBottom = screenVertices[0];
        float left = frontLeftBottom.x;
        float top = frontLeftBottom.y;
        float right = frontLeftBottom.x;
        float bottom = frontLeftBottom.y;

        for (int i = 1; i < 8; i++) {
            const vector2f vertex = screenVertices[i];

            if (left > vertex.x)
                left = vertex.x;
            if (top < vertex.y)
                top = vertex.y;
            if (right < vertex.x)
                right = vertex.x;
            if (bottom > vertex.y)
                bottom = vertex.y;
        }

        return rect {
            vector2f(left, bottom),
            vector2f(right - left, top - bottom)
        };
    }
}

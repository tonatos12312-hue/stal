#pragma once

#include <common/memory/remote_ptr.h>
#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"
#include "axis_aligned_bounding_box.h"
#include "matrix3x4.h"
#include "matrix4x4.h"
#include "rect.h"

#ifndef max
    #define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
    #define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define PI 3.14159f
#define PI2 (PI * 2)
#define RAD2DEG(radians) (radians * (180.0f / PI))
#define DEG2RAD(angle) (angle * (PI / 180.0f))

namespace shared {
    inline extern vector2i display_size{};
    inline extern common::remote_ptr<matrix4x4> view_matrix{};
}

namespace common {

    inlined bool world_to_screen(const vector3f& origin, vector2f& result) {
        const vector3f projected = origin * (*shared::view_matrix);
        if (projected.x == 0 && projected.y == 0 && projected.z == 0)
            return false;

        result = vector2f(
                (shared::display_size.x / 2.0f) + (projected.x * shared::display_size.x) / 2.0f,
                (shared::display_size.y / 2.0f) - (projected.y * shared::display_size.y) / 2.0f
        );
        return true;
    }

    inlined void rotate_matrix(matrix3x4& matrix, const quaternionf& orientation) {
        const __m128 x2 = _mm_set1_ps(orientation.x * orientation.x * 2.0f);
        const __m128 y2 = _mm_set1_ps(orientation.y * orientation.y * 2.0f);
        const __m128 z2 = _mm_set1_ps(orientation.z * orientation.z * 2.0f);

        const __m128 xy = _mm_set1_ps(orientation.x * orientation.y * 2.0f);
        const __m128 xz = _mm_set1_ps(orientation.x * orientation.z * 2.0f);
        const __m128 yz = _mm_set1_ps(orientation.y * orientation.z * 2.0f);

        const __m128 wx = _mm_set1_ps(orientation.w * orientation.x * 2.0f);
        const __m128 wy = _mm_set1_ps(orientation.w * orientation.y * 2.0f);
        const __m128 wz = _mm_set1_ps(orientation.w * orientation.z * 2.0f);

        matrix[0][0] = 1.0f - _mm_cvtss_f32(_mm_add_ss(y2, z2));
        matrix[1][0] = _mm_cvtss_f32(_mm_add_ss(xy, wz));
        matrix[2][0] = _mm_cvtss_f32(_mm_sub_ss(xz, wy));

        matrix[0][1] = _mm_cvtss_f32(_mm_sub_ss(xy, wz));
        matrix[1][1] = 1.0f - _mm_cvtss_f32(_mm_add_ss(x2, z2));
        matrix[2][1] = _mm_cvtss_f32(_mm_add_ss(yz, wx));

        matrix[0][2] = _mm_cvtss_f32(_mm_add_ss(xz, wy));
        matrix[1][2] = _mm_cvtss_f32(_mm_sub_ss(yz, wx));
        matrix[2][2] = 1.0f - _mm_cvtss_f32(_mm_add_ss(x2, y2));
    }

    inlined void translate_matrix(matrix3x4& matrix, const vector3f& position) {
        const __m128 pos = _mm_set_ps(0.0f, position.z, position.y, position.x);

        matrix[0][3] = _mm_cvtss_f32(pos);
        matrix[1][3] = _mm_cvtss_f32(_mm_shuffle_ps(pos, pos, _MM_SHUFFLE(1, 1, 1, 1)));
        matrix[2][3] = _mm_cvtss_f32(_mm_shuffle_ps(pos, pos, _MM_SHUFFLE(2, 2, 2, 2)));
    }
}

#pragma once

#include <immintrin.h>

struct matrix4x4 {
public:
    float* operator[](size_t index) {
        return matrix[index];
    }

    const float* operator[](size_t index) const {
        return matrix[index];
    }

    matrix4x4 operator*(const matrix4x4& other) const {
        matrix4x4 result{};

        for (int i = 0; i < 4; i++) {
            const __m128 row = _mm_load_ps(matrix[i]);
            for (int j = 0; j < 4; j++) {
                const __m128 column = _mm_set_ps(other[0][j], other[1][j], other[2][j], other[3][j]);
                __m128 res = _mm_mul_ps(row, column);
                res = _mm_hadd_ps(res, res);
                res = _mm_hadd_ps(res, res);
                result[i][j] = _mm_cvtss_f32(res);
            }
        }

        return result;
    }
private:
    float matrix[4][4]{};
};

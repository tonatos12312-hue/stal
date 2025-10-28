#pragma once

struct matrix3x4 {
public:
    float* operator[](size_t index) {
        return matrix[index];
    }

    const float* operator[](size_t index) const {
        return matrix[index];
    }
private:
    float matrix[3][4]{};
};

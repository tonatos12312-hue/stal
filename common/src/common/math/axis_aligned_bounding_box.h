#pragma once

#include "vector3.h"

class axis_aligned_bounding_box {
public:
    axis_aligned_bounding_box(const vector3f& minimum, const vector3f& maximum) : minimum(minimum), maximum(maximum) {}
public:
    vector3f* vertices() {
        const vector3f frontLeftBottom(maximum.x, minimum.y, minimum.z);
        const vector3f backRightTop(minimum.x, maximum.y, maximum.z);
        const vector3f backLeftBottom(minimum.x, minimum.y, minimum.z);
        const vector3f frontRightTop(maximum.x, maximum.y, maximum.z);
        const vector3f frontRightBottom(maximum.x, maximum.y, minimum.z);
        const vector3f backRightBottom(minimum.x, maximum.y, minimum.z);
        const vector3f backLeftTop(minimum.x, minimum.y, maximum.z);
        const vector3f frontLeftTop(maximum.x, minimum.y, maximum.z);

        vertex[0] = frontLeftBottom;
        vertex[1] = backRightTop;
        vertex[2] = backLeftBottom;
        vertex[3] = frontRightTop;
        vertex[4] = frontRightBottom;
        vertex[5] = backRightBottom;
        vertex[6] = backLeftTop;
        vertex[7] = frontLeftTop;

        return vertex;
    }
public:
    vector3f minimum, maximum;
private:
    vector3f vertex[8];
};

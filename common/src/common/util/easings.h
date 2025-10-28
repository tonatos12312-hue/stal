#pragma once

// TODO: move min and max macros to pre_include.h
#include <Windows.h>
#include <cstdio>

inlined float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

inlined float ease_out_quart(float current, float target, float speed) {
    const float diff = target - current;
    if (fabsf(diff) < 0.001f)
        return target;

    const float t = 1.0f - powf(1.0f - min(speed, 1.0f), 4.0f);
    return current + diff * t;
}

#pragma once

#include "vector3.h"

template<typename T>
class quaternion {
public:
    quaternion() : x(0), y(0), z(0), w(0) {}
    
    explicit quaternion(const vector3<T>& quaternion) : x(quaternion.x), y(quaternion.y), z(quaternion.z), w(0) {}
    
    quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
public:
    T x, y, z, w;
};

typedef quaternion<float> quaternionf;
typedef quaternion<double> quaterniond;
typedef quaternion<int> quaternioni;

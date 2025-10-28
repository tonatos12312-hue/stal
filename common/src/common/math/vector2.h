#pragma once

#include <cmath>

template<typename T>
class vector2 {
public:
    vector2() : x(0), y(0) {}

    vector2(const vector2& vector) : x(vector.x), y(vector.y) {}

    vector2(T x, T y) : x(x), y(y) {}
public:
    T dot(const vector2& other) const {
        return x * other.x + y * other.y;
    }

    T distance_to(const vector2& other) const {
        return static_cast<T>(sqrtf(powf(other.x - x, 2.0f) + powf(other.y - y, 2.0f)));
    }

    T length() const {
        return static_cast<T>(sqrtf(x * x + y * y));
    }

    T length_squared() const {
        return static_cast<T>(x * x + y * y);
    }
public:
    vector2 operator+(const vector2 other) const {
        return vector2(x + other.x, y + other.y);
    }

    vector2 operator+(float value) const {
        return vector2(x + value, y + value);
    }

    vector2 operator-(const vector2 other) const {
        return vector2(x - other.x, y - other.y);
    }

    vector2 operator-(float value) const {
        return vector2(x - value, y - value);
    }

    vector2 operator*(const vector2 other) const {
        return vector2(x * other.x, y * other.y);
    }

    vector2 operator*(float value) const {
        return vector2(x * value, y * value);
    }

    vector2 operator/(const vector2 other) const {
        return vector2(x / other.x, y / other.y);
    }

    vector2 operator/(float value) const {
        return vector2(x / value, y / value);
    }

    vector2& operator+=(const vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vector2& operator+=(float value) {
        x += value;
        y += value;
        return *this;
    }

    vector2& operator-=(const vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vector2& operator-=(float value) {
        x -= value;
        y -= value;
        return *this;
    }

    vector2& operator*=(const vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    vector2& operator*=(float value) {
        x *= value;
        y *= value;
        return *this;
    }

    vector2& operator/=(const vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    vector2& operator/=(float value) {
        x /= value;
        y /= value;
        return *this;
    }
public:
    T x, y;
};

typedef vector2<float> vector2f;
typedef vector2<double> vector2d;
typedef vector2<int> vector2i;

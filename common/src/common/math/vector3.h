#pragma once

#include <cmath>
#include "matrix3x4.h"
#include "matrix4x4.h"

template<typename T>
struct vector3 {
public:
	vector3() : x(0), y(0), z(0) {}

	vector3(const vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

	vector3(T x, T y, T z) : x(x), y(y), z(z) {}
public:
	T dot(const vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

    vector3 cross_product(const vector3& other) {
        return vector3 {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

	T distance_to(const vector3 other) const {
		return static_cast<T>(sqrtf(powf(other.x - x, 2.0f) + powf(other.y - y, 2.0f) + powf(other.z - z, 2.0f)));
	}

	T length() const {
		return static_cast<T>(sqrtf(x * x + y * y + z * z));
	}

    T length_squared() const {
        return static_cast<T>(x * x + y * y + z * z);
    }

	T length2d() const {
		return static_cast<T>(sqrtf(x * x + y * y));
	}

	vector3 normalized() {
		const T len = length();
		if (len != 0)
			return vector3(x / len, y / len, z / len);
		
		return *this;
	}
public:
	vector3 operator+(const vector3 other) const {
		return vector3(x + other.x, y + other.y, z + other.z);
	}

	vector3 operator-(const vector3 other) const {
		return vector3(x - other.x, y - other.y, z - other.z);
	}

	vector3 operator*(const vector3 other) const {
		return vector3(x * other.x, y * other.y, z * other.z);
	}

	vector3 operator/(const vector3 other) const {
		return vector3(x / other.x, y / other.y, z / other.z);
	}

    vector3& operator+=(const vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3& operator-=(const vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vector3& operator*=(const vector3& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    vector3& operator/=(const vector3& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    vector3 operator*(const matrix3x4& mat) const {
        return vector3(
                x * mat[0][0] + y * mat[0][1] + z * mat[0][2] + mat[0][3],
                x * mat[1][0] + y * mat[1][1] + z * mat[1][2] + mat[1][3],
                x * mat[2][0] + y * mat[2][1] + z * mat[2][2] + mat[2][3]
        );
    }

    vector3 operator*(const matrix4x4& mat) const {
        T new_x = x * mat[0][0] + y * mat[0][1] + z * mat[0][2] + mat[0][3];
        T new_y = x * mat[1][0] + y * mat[1][1] + z * mat[1][2] + mat[1][3];
        T new_z = x * mat[2][0] + y * mat[2][1] + z * mat[2][2] + mat[2][3];
        T w = x * mat[3][0] + y * mat[3][1] + z * mat[3][2] + mat[3][3];

        if (w < 0.001f)
            return vector3();

        new_x /= w;
        new_y /= w;
        new_z /= w;

        return vector3(new_x, new_y, new_z);
    }
public:
	T x, y, z;
};

typedef vector3<float> vector3f;
typedef vector3<double> vector3d;
typedef vector3<int> vector3i;

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstdint>

struct Vector2 {
    float x, y;
    
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    
    float Length() const {
        return sqrtf(x * x + y * y);
    }
    
    Vector2 Normalize() const {
        float len = Length();
        if (len > 0) {
            return Vector2(x / len, y / len);
        }
        return *this;
    }
};

struct Vector3 {
    float x, y, z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    float Length() const {
        return sqrtf(x * x + y * y + z * z);
    }
    
    Vector3 Normalize() const {
        float len = Length();
        if (len > 0) {
            return Vector3(x / len, y / len, z / len);
        }
        return *this;
    }
    
    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    Vector3 Cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    float Distance(const Vector3& other) const {
        return (*this - other).Length();
    }
};

struct Vector4 {
    float x, y, z, w;
    
    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct Matrix4x4 {
    float m[4][4];
    
    Matrix4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }
    
    Vector3 Transform(const Vector3& v) const {
        Vector4 result;
        result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
        
        if (result.w != 0) {
            result.x /= result.w;
            result.y /= result.w;
            result.z /= result.w;
        }
        
        return Vector3(result.x, result.y, result.z);
    }
};

#endif // VECTOR_H

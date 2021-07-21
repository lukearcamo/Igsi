#ifndef IGSI_MATH_H
#define IGSI_MATH_H

#include <iostream>
#include <cmath>

/*
TODO:
Add modulus operator overload?
Add more math functions that support vectors, beyond just floor()
Use OpenGL data types, and add support for more data types beyond floats
Swizzling?
*/

namespace Igsi {
    float toRadians = M_PI / 180.0;
    float toDegrees = 180.0 / M_PI;

    class vec2 {
    public:
        float x, y;
        vec2(float a = 0) { x = a; y = a; }
        vec2(float nx, float ny) { x = nx; y = ny; }

        vec2 &operator = (float a) { x = a; y = a; return *this; }
        vec2 &operator = (vec2 a) { x = a.x; y = a.y;  return *this; }

        vec2 operator + (float a) { return vec2(x + a, y + a); }
        vec2 operator + (vec2 a) { return vec2(x + a.x, y + a.y); }
        vec2 &operator += (float a) { x += a; y += a; return *this; }
        vec2 &operator += (vec2 a) { x += a.x; y += a.y; return *this; }

        vec2 operator - (float a) { return vec2(x - a, y - a); }
        vec2 operator - (vec2 a) { return vec2(x - a.x, y - a.y); }
        vec2 &operator -= (float a) { x -= a; y -= a; return *this; }
        vec2 &operator -= (vec2 a) { x -= a.x; y -= a.y; return *this; }

        vec2 operator * (float a) { return vec2(x * a, y * a); }
        vec2 operator * (vec2 a) { return vec2(x * a.x, y * a.y); }
        vec2 &operator *= (float a) { x *= a; y *= a; return *this; }
        vec2 &operator *= (vec2 a) { x *= a.x; y *= a.y; return *this; }

        vec2 operator / (float a) { return vec2(x / a, y / a); }
        vec2 operator / (vec2 a) { return vec2(x / a.x, y / a.y); }
        vec2 &operator /= (float a) { x /= a; y /= a; return *this; }
        vec2 &operator /= (vec2 a) { x /= a.x; y /= a.y; return *this; }

        bool operator == (vec2 a) { return x == a.x && y == a.y; }
        bool operator != (vec2 a) { return x != a.x || y != a.y; }

        vec2 operator - () { return vec2(-x, -y); }

        float &operator [] (int i) {
            return i ? y : x;
        }
    };

    class vec3 {
    public:
        float x, y, z;
        vec3(float a = 0) { x = a; y = a; z = a; }
        vec3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }

        vec3(vec2 a, float nz) { x = a.x; y = a.y; z = nz; }
        vec3(float nx, vec2 a) { x = nx; y = a.x; z = a.y; }

        vec3 &operator = (float a) { x = a; y = a; z = a; return *this; }
        vec3 &operator = (vec3 a) { x = a.x; y = a.y; z = a.z; return *this; }

        vec3 operator + (float a) { return vec3(x + a, y + a, z + a); }
        vec3 operator + (vec3 a) { return vec3(x + a.x, y + a.y, z + a.z); }
        vec3 &operator += (float a) { x += a; y += a; z += a; return *this; }
        vec3 &operator += (vec3 a) { x += a.x; y += a.y; z += a.z; return *this;  }

        vec3 operator - (float a) { return vec3(x - a, y - a, z - a); }
        vec3 operator - (vec3 a) { return vec3(x - a.x, y - a.y, z - a.z); }
        vec3 &operator -= (float a) { x -= a; y -= a; z -= a; return *this; }
        vec3 &operator -= (vec3 a) { x -= a.x; y -= a.y; z -= a.z; return *this; }

        vec3 operator * (float a) { return vec3(x * a, y * a, z * a); }
        vec3 operator * (vec3 a) { return vec3(x * a.x, y * a.y, z * a.z); }
        vec3 &operator *= (float a) { x *= a; y *= a; z *= a; return *this; }
        vec3 &operator *= (vec3 a) { x *= a.x; y *= a.y; z *= a.z; return *this; }

        vec3 operator / (float a) { return vec3(x / a, y / a, z / a); }
        vec3 operator / (vec3 a) { return vec3(x / a.x, y / a.y, z / a.z); }
        vec3 &operator /= (float a) { x /= a; y /= a; z /= a; return *this; }
        vec3 &operator /= (vec3 a) { x /= a.x; y /= a.y; z /= a.z; return *this; }

        bool operator == (vec3 a) { return x == a.x && y == a.y && z == a.z; }
        bool operator != (vec3 a) { return x != a.x || y != a.y || z != a.z; }
        // No overload for greater & less than because it doesnt make sense for a vector

        vec3 operator - () { return vec3(-x, -y, -z); }

        float &operator [] (int i) {
            if (i == 0) return x;
            else if (i == 1) return y;
            return z;
        }
    };

    class vec4 {
    public:
        float x, y, z, w;
        vec4(float a = 0) { x = a; y = a; z = a; w = a; }
        vec4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }

        vec4(vec3 a, float nw) { x = a.x; y = a.y; z = a.z; w = nw; }
        vec4(float nx, vec3 a) { x = nx; y = a.x; z = a.y; w = a.z; }
        vec4(vec2 a, float nz, float nw) { x = a.x; y = a.y; z = nz; w = nw; }
        vec4(float nx, vec2 a, float nw) { x = nx; y = a.x; z = a.y; w = nw; }
        vec4(float nx, float ny, vec2 a) { x = nx; y = ny; z = a.x; w = a.y; }

        vec4 &operator = (float a) { x = a; y = a; z = a; w = a; return *this; }
        vec4 &operator = (vec4 a) { x = a.x; y = a.y; z = a.z; w = a.w; return *this; }

        vec4 operator + (float a) { return vec4(x + a, y + a, z + a, w + a); }
        vec4 operator + (vec4 a) { return vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
        vec4 &operator += (float a) { x += a; y += a; z += a; w += a; return *this; }
        vec4 &operator += (vec4 a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this;  }

        vec4 operator - (float a) { return vec4(x - a, y - a, z - a, w - a); }
        vec4 operator - (vec4 a) { return vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
        vec4 &operator -= (float a) { x -= a; y -= a; z -= a; w -= a; return *this; }
        vec4 &operator -= (vec4 a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }

        vec4 operator * (float a) { return vec4(x * a, y * a, z * a, w * a); }
        vec4 operator * (vec4 a) { return vec4(x * a.x, y * a.y, z * a.z, w * a.w); }
        vec4 &operator *= (float a) { x *= a; y *= a; z *= a; w *= a; return *this; }
        vec4 &operator *= (vec4 a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; return *this; }

        vec4 operator / (float a) { return vec4(x / a, y / a, z / a, w / a); }
        vec4 operator / (vec4 a) { return vec4(x / a.x, y / a.y, z / a.z, w / a.w); }
        vec4 &operator /= (float a) { x /= a; y /= a; z /= a; w /= a; return *this; }
        vec4 &operator /= (vec4 a) { x /= a.x; y /= a.y; z /= a.z; w /= a.w; return *this; }

        bool operator == (vec4 a) { return x == a.x && y == a.y && z == a.z && w == a.w; }
        bool operator != (vec4 a) { return x != a.x || y != a.y || z != a.z || w != a.w; }
        // No overload for greater & less than because it doesnt make sense for a vector

        vec4 operator - () { return vec4(-x, -y, -z, -w); }

        float &operator [] (int i) {
            if (i == 0) return x;
            else if (i == 1) return y;
            else if (i == 2) return z;
            return w;
        }
    };
    
    float dot(vec2 a) { return a.x * a.x + a.y * a.y; }
    float dot(vec3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
    float dot(vec4 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }
    vec3 cross(vec3 a, vec3 b) {
        return vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
    template <typename T> float length(T a) { return std::sqrt(dot(a)); }
    template <typename T> T normalize(T a) { return a != T(0) ? a / length(a) : a; } // If vector length == 0, return vector of 0 rather than nan

    vec2 floor(vec2 a) { return vec2(std::floor(a.x), std::floor(a.y)); }
    vec3 floor(vec3 a) { return vec3(std::floor(a.x), std::floor(a.y), std::floor(a.z)); }
    vec4 floor(vec4 a) { return vec4(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w)); }

    // enum EulerOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX };

    class mat4 {
    public:
        float elements[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        // GLboolean isRowMajor = GL_FALSE;
        bool isRowMajor = false;
        mat4() {}
        mat4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15) {
            set(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
        }
        mat4 &set(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15) {
            elements[0] = a0; elements[4] = a1; elements[8] = a2; elements[12] = a3;
            elements[1] = a4; elements[5] = a5; elements[9] = a6; elements[13] = a7;
            elements[2] = a8; elements[6] = a9; elements[10] = a10; elements[14] = a11;
            elements[3] = a12; elements[7] = a13; elements[11] = a14; elements[15] = a15;
            return *this;
        }
        mat4 &identity() {
            return set(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }

        mat4 &setTranslation(float x, float y, float z) { elements[12] = x; elements[13] = y; elements[14] = z; return *this; }
        mat4 &setTranslation(vec3 a) { return setTranslation(a.x, a.y, a.z); }
        mat4 &translation(float x, float y, float z) { return identity().setTranslation(x, y, z); }
        mat4 &translation(vec3 a) { return identity().setTranslation(a); }
        
        mat4 &rotationX(float radians) {
            float c = std::cos(radians);
            float s = std::sin(radians);
            set(
                1, 0, 0, 0,
                0, c,-s, 0,
                0, s, c, 0,
                0, 0, 0, 1
            );
            return *this;
        }
        mat4 &rotationY(float radians) {
            float c = std::cos(radians);
            float s = std::sin(radians);
            set(
                c, 0, s, 0,
                0, 1, 0, 0,
               -s, 0, c, 0,
                0, 0, 0, 1
            );
            return *this;
        }
        mat4 &rotationZ(float radians) {
            float c = std::cos(radians);
            float s = std::sin(radians);
            set(
                c, s, 0, 0,
               -s, c, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
            return *this;
        }

        mat4 &scale(float x, float y, float z) {
            identity();
            elements[0] = x;
            elements[5] = y;
            elements[10] = z;
            return *this;
        }
        mat4 &scale(vec3 a) {
            identity();
            elements[0] = a.x;
            elements[5] = a.y;
            elements[10] = a.z;
            return *this;
        }

        // For debugging
        void print() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << elements[i * 4 + j] << ", ";
                }
                std::cout << std::endl;
            }
        }

        mat4 &transpose() {
            return set(
                elements[0], elements[1], elements[2], elements[3],
                elements[4], elements[5], elements[6], elements[7],
                elements[8], elements[9], elements[10], elements[11],
                elements[12], elements[13], elements[14], elements[15]
            );
        }
        mat4 lookAt(vec3 origin, vec3 target, vec3 up) {
            vec3 ww = normalize(target - origin);
            vec3 uu = normalize(cross(ww, up));
            vec3 vv = normalize(cross(uu, ww));
            return mat4(
                uu.x, uu.y, uu.z, 0,
                vv.x, vv.y, vv.z, 0,
                ww.x, ww.y, ww.z, 0,
                0,    0,    0,    1
            );
        }
        // Adapted from https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
        mat4 &rotationAxisAngle(vec3 axis, float angle) {
            vec3 s = axis * std::sin(angle);
            float c = std::cos(angle);
            vec3 t = axis * (1 - c);
            return set(
                axis.x * t.x + c,   axis.y * t.x - s.z, axis.z * t.x + s.y, 0,
                axis.x * t.y + s.z, axis.y * t.y + c,   axis.z * t.y - s.x, 0,
                axis.x * t.z - s.y, axis.y * t.z + s.x, axis.z * t.z + c,   0,
                0, 0, 0, 1
            );
        }
        mat4 &rotationEuler(vec3 radians, const char* order) {
            if (order == "XZY") return rotationX(radians.x) *= mat4().rotationZ(radians.z) *= mat4().rotationY(radians.y);
            if (order == "YXZ") return rotationY(radians.y) *= mat4().rotationX(radians.x) *= mat4().rotationZ(radians.z);
            if (order == "YZX") return rotationY(radians.y) *= mat4().rotationZ(radians.z) *= mat4().rotationX(radians.x);
            if (order == "ZXY") return rotationZ(radians.z) *= mat4().rotationX(radians.x) *= mat4().rotationY(radians.y);
            if (order == "ZYX") return rotationZ(radians.z) *= mat4().rotationY(radians.y) *= mat4().rotationX(radians.x);
            return rotationX(radians.x) *= mat4().rotationY(radians.y) *= mat4().rotationZ(radians.z); // Dafault
        }
        mat4 &orthographic(float left, float right, float bottom, float top, float near, float far) {
            float w = 1 / (right - left);
            float h = 1 / (top - bottom);
            float p = 1 / (far - near);
            return set(
                2 * w, 0, 0, (right + left) * -w,
                0, 2 * h, 0, (top + bottom) * -h,
                0, 0, -2 * p, (far + near) * -p,
                0, 0, 0, 1
            );
        }
        // Adapted from https://webglfundamentals.org/webgl/lessons/webgl-3d-perspective.html
        mat4 &perspective(float fov, float aspect, float near, float far) { // fov is vertical fov in radians
            float d = 1.0 / std::tan(fov / 2.0);
            float r = 1.0 / (near - far);
            return set(
                d / aspect, 0, 0, 0,
                0, d, 0, 0,
                0, 0, (near + far) * r, 2 * near * far * r,
                0, 0, -1, 0
            );
        }
        // Adapted from Matrix4 class in THREE.js library
        // https://github.com/mrdoob/three.js/blob/master/src/math/Matrix4.js
        mat4 &invert() {
            float
            n11 = elements[0], n21 = elements[1], n31 = elements[2], n41 = elements[3],
            n12 = elements[4], n22 = elements[5], n32 = elements[6], n42 = elements[7],
            n13 = elements[8], n23 = elements[9], n33 = elements[10], n43 = elements[11],
            n14 = elements[12], n24 = elements[13], n34 = elements[14], n44 = elements[15],
            t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44,
            t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44,
            t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44,
            t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

            float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;
            if (det == 0) return set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            float detInv = 1 / det;

            elements[0] = t11 * detInv;
            elements[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
            elements[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
            elements[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * detInv;
            elements[4] = t12 * detInv;
            elements[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
            elements[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
            elements[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * detInv;
            elements[8] = t13 * detInv;
            elements[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
            elements[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
            elements[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;
            elements[12] = t14 * detInv;
            elements[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
            elements[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
            elements[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;

            return *this;
        }

        bool operator == (mat4 a) { for (int i = 0; i < 16; i++) { if (elements[i] != a.elements[i]) return false; } return true; }
        // bool operator != (mat4 a) { for (int i = 0; i < 16; i++) { if (elements[i] == a.elements[i]) return false; } return true; }

        mat4 &operator = (mat4 a) { for (int i = 0; i < 16; i++) { elements[i] = a.elements[i]; } return *this; }

        mat4 &operator += (float a) { for (int i = 0; i < 16; i++) { elements[i] += a; } return *this; }
        mat4 &operator -= (float a) { for (int i = 0; i < 16; i++) { elements[i] -= a; } return *this; }
        mat4 &operator *= (float a) { for (int i = 0; i < 16; i++) { elements[i] *= a; } return *this; }
        mat4 &operator /= (float a) { for (int i = 0; i < 16; i++) { elements[i] /= a; } return *this; }

        mat4 &operator += (mat4 a) { for (int i = 0; i < 16; i++) { elements[i] += a.elements[i]; } return *this; }
        mat4 &operator -= (mat4 a) { for (int i = 0; i < 16; i++) { elements[i] -= a.elements[i]; } return *this; }
        mat4 &operator &= (mat4 a) { for (int i = 0; i < 16; i++) { elements[i] *= a.elements[i]; } return *this; }
        mat4 &operator /= (mat4 a) { for (int i = 0; i < 16; i++) { elements[i] /= a.elements[i]; } return *this; }

        mat4 operator + (float a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] + a; } return c; }
        mat4 operator - (float a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] - a; } return c; }
        mat4 operator * (float a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] * a; } return c; }
        mat4 operator / (float a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] / a; } return c; }

        mat4 operator + (mat4 a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] + a.elements[i]; } return c; }
        mat4 operator - (mat4 a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] - a.elements[i]; } return c; }
        mat4 operator & (mat4 a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] * a.elements[i]; } return c; }
        mat4 operator / (mat4 a) { mat4 c; for (int i = 0; i < 16; i++) { c.elements[i] = elements[i] / a.elements[i]; } return c; }

        vec4 operator * (vec4 a) {
            vec4 c;
            c.x = elements[0] * a.x + elements[4] * a.y + elements[8] * a.z + elements[12] * a.w;
		    c.y = elements[1] * a.x + elements[5] * a.y + elements[9] * a.z + elements[13] * a.w;
		    c.z = elements[2] * a.x + elements[6] * a.y + elements[10] * a.z + elements[14] * a.w;
		    c.w = elements[3] * a.x + elements[7] * a.y + elements[11] * a.z + elements[15] * a.w;
            return c;
        }
        mat4 operator * (mat4 a) {
            mat4 c;
            int e = 0;
            float sum;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    sum = 0;
                    for (int k = 0; k < 4; k++) {
                        sum += elements[i * 4 + k] * a.elements[k * 4 + j];
                    }
                    c.elements[e] = sum;
                    e++;
                }
            }
            return c;
        }
        mat4 &operator *= (mat4 a) {
            *this = *this * a;
            return *this;
        }
    };
}

#endif

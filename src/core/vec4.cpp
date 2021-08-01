#include "vec4.h"

#include <cmath>

namespace Igsi {
    vec4::vec4(float a) { x = a; y = a; z = a; w = a; }
    vec4::vec4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }

    vec4& vec4::operator = (float a) { x = a; y = a; z = a; w = a; return *this; }
    vec4& vec4::operator = (vec4 a) { x = a.x; y = a.y; z = a.z; w = a.w; return *this; }

    vec4 vec4::operator + (float a) { return vec4(x + a, y + a, z + a, w + a); }
    vec4 vec4::operator + (vec4 a) { return vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
    vec4& vec4::operator += (float a) { x += a; y += a; z += a; w += a; return *this; }
    vec4& vec4::operator += (vec4 a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }

    vec4 vec4::operator - (float a) { return vec4(x - a, y - a, z - a, w - a); }
    vec4 vec4::operator - (vec4 a) { return vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
    vec4& vec4::operator -= (float a) { x -= a; y -= a; z -= a; w -= a; return *this; }
    vec4& vec4::operator -= (vec4 a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }

    vec4 vec4::operator * (float a) { return vec4(x * a, y * a, z * a, w * a); }
    vec4 vec4::operator * (vec4 a) { return vec4(x * a.x, y * a.y, z * a.z, w * a.w); }
    vec4& vec4::operator *= (float a) { x *= a; y *= a; z *= a; w *= a; return *this; }
    vec4& vec4::operator *= (vec4 a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; return *this; }

    vec4 vec4::operator / (float a) { return vec4(x / a, y / a, z / a, w / a); }
    vec4 vec4::operator / (vec4 a) { return vec4(x / a.x, y / a.y, z / a.z, w / a.w); }
    vec4& vec4::operator /= (float a) { x /= a; y /= a; z /= a; w /= a; return *this; }
    vec4& vec4::operator /= (vec4 a) { x /= a.x; y /= a.y; z /= a.z; w /= a.w; return *this; }

    bool vec4::operator == (vec4 a) { return x == a.x && y == a.y && z == a.z && w == a.w; }
    bool vec4::operator != (vec4 a) { return x != a.x || y != a.y || z != a.z || w != a.w; }

    vec4 vec4::operator - () { return vec4(-x, -y, -z, -w); }

    float& vec4::operator [] (int i) {
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        else return w;
    }
    
    float dot(vec4 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }
    vec4 floor(vec4 a) { return vec4(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w)); }
    vec4 abs(vec4 a) { return vec4(std::fabs(a.x), std::fabs(a.y), std::fabs(a.z), std::fabs(a.w)); }
    float length(vec4 a) { return std::sqrt(dot(a)); }
    vec4 normalize(vec4 a) { // To prevent divide by zero, if len = 0 return vec of 0
        float len = length(a);
        return len != 0.0 ? a / len : a;
    }
}
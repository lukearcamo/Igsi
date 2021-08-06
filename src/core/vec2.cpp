#include "vec2.h"

#include <cmath>

namespace Igsi {
    vec2::vec2(float a) { x = a; y = a; }
    vec2::vec2(float x, float y) { this->x = x; this->y = y; }

    vec2& vec2::operator = (float a) { x = a; y = a; return *this; }
    vec2& vec2::operator = (vec2 a) { x = a.x; y = a.y; return *this; }

    vec2 vec2::operator + (float a) { return vec2(x + a, y + a); }
    vec2 vec2::operator + (vec2 a) { return vec2(x + a.x, y + a.y); }
    vec2& vec2::operator += (float a) { x += a; y += a; return *this; }
    vec2& vec2::operator += (vec2 a) { x += a.x; y += a.y; return *this; }

    vec2 vec2::operator - (float a) { return vec2(x - a, y - a); }
    vec2 vec2::operator - (vec2 a) {return vec2(x - a.x, y - a.y); }
    vec2& vec2::operator -= (float a) { x -= a; y -= a; return *this; }
    vec2& vec2::operator -= (vec2 a) { x -= a.x; y -= a.y; return *this; }

    vec2 vec2::operator * (float a) { return vec2(x * a, y * a); }
    vec2 vec2::operator * (vec2 a) { return vec2(x * a.x, y * a.y); }
    vec2& vec2::operator *= (float a) { x *= a; y *= a; return *this; }
    vec2& vec2::operator *= (vec2 a) { x *= a.x; y *= a.y; return *this; }

    vec2 vec2::operator / (float a) { return vec2(x / a, y / a); }
    vec2 vec2::operator / (vec2 a) { return vec2(x / a.x, y / a.y); }
    vec2& vec2::operator /= (float a) { x /= a; y /= a; return *this; }
    vec2& vec2::operator /= (vec2 a) { x /= a.x; y /= a.y; return *this; }

    bool vec2::operator == (vec2 a) { return x == a.x && y == a.y; }
    bool vec2::operator != (vec2 a) { return x != a.x || y != a.y; }

    vec2 vec2::operator - () { return vec2(-x, -y); }

    float& vec2::operator [] (int i) {
        return i ? y : x;
    }
    
    float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
    vec2 floor(vec2 a) { return vec2(std::floor(a.x), std::floor(a.y)); }
    vec2 abs(vec2 a) { return vec2(std::fabs(a.x), std::fabs(a.y)); }
    float length(vec2 a) { return std::sqrt(dot(a, a)); }
    vec2 normalize(vec2 a) { // To prevent divide by zero, if len = 0 return vec of 0
        float len = length(a);
        return len != 0.0 ? a / len : a;
    }
}
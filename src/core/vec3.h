#ifndef IGSI_VEC3_H
#define IGSI_VEC3_H

namespace Igsi {
    class vec3 {
    public:
        float x, y, z;

        vec3(float a = 0);
        vec3(float nx, float ny, float nz);

        vec3& operator = (float a);
        vec3& operator = (vec3 a);

        vec3 operator + (float a);
        vec3 operator + (vec3 a);
        vec3& operator += (float a);
        vec3& operator += (vec3 a);

        vec3 operator - (float a);
        vec3 operator - (vec3 a);
        vec3& operator -= (float a);
        vec3& operator -= (vec3 a);

        vec3 operator * (float a);
        vec3 operator * (vec3 a);
        vec3& operator *= (float a);
        vec3& operator *= (vec3 a);

        vec3 operator / (float a);
        vec3 operator / (vec3 a);
        vec3& operator /= (float a);
        vec3& operator /= (vec3 a);

        bool operator == (vec3 a);
        bool operator != (vec3 a);

        vec3 operator - ();

        float &operator [] (int i);
    };
    
    float dot(vec3 a);
    vec3 floor(vec3 a);
    vec3 abs(vec3 a);

    float length(vec3 a);
    vec3 normalize(vec3 a);
    vec3 cross(vec3 a, vec3 b);
}

#endif
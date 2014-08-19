#include "mat3f.h"

namespace molphene {
    mat3f::mat3f() :
    m{1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f}
    {
    }
    
    mat3f::mat3f(float m11, float m12, float m13,
                 float m21, float m22, float m23,
                 float m31, float m32, float m33) :
    m{m11, m12, m13,
        m21, m22, m23,
        m31, m32, m33}
    {
    }
    
    mat3f::mat3f(const mat4f & m4) :
    m{m4.m[0], m4.m[1], m4.m[2],
        m4.m[4], m4.m[5], m4.m[6],
        m4.m[8], m4.m[9], m4.m[10]}
    {
    }

}
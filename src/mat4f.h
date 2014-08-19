#ifndef __molphene__File__
#define __molphene__File__

#include <cmath>
#include "vec3f.h"

namespace molphene {
    struct mat4f {
        float m[16];
        
        mat4f();
        
        mat4f(float m11, float m12, float m13, float m14,
              float m21, float m22, float m23, float m24,
              float m31, float m32, float m33, float m34,
              float m41, float m42, float m43, float m44);
        
        mat4f & operator () (float m11, float m12, float m13, float m14,
                             float m21, float m22, float m23, float m24,
                             float m31, float m32, float m33, float m34,
                             float m41, float m42, float m43, float m44);
        
        mat4f & operator () ();
        
        mat4f & operator *= (const mat4f & mat4);
        
        mat4f operator * (const mat4f & mat4) const;
        
        mat4f & operator /= (const float & s);
        
        mat4f operator / (const float & s) const;
        
        mat4f & scale(const float & s);
        mat4f & scale(const float & x, const float & y, const float & z);
        mat4f & scale(const vec3f & v);
        
        mat4f & rotate(float x, float y, float z, float a);
        
        mat4f & translate(float x, float y, float z);
        mat4f & translate(const vec3f & v);
        
        mat4f & frustum(float l, float r, float b, float t, float n, float f);
        
        mat4f & adjoint();
        
        mat4f & inverse();
        
        mat4f & transpose();
    };
    
    float determinant(const mat4f & m);
}

#endif /* defined(__molphene__File__) */

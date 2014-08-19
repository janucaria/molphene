#ifndef __Molphene__mat3f__
#define __Molphene__mat3f__

#include "mat4f.h"

namespace molphene {
    struct mat3f {
        float m[9];
        
        mat3f();
        
        mat3f(float m11, float m12, float m13,
              float m21, float m22, float m23,
              float m31, float m32, float m33);
        
        mat3f(const mat4f & m4);
    };
}

#endif /* defined(__Molphene__mat3f__) */

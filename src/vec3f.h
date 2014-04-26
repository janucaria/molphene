#ifndef __molphene__vec3f__
#define __molphene__vec3f__

namespace molphene {
    struct vec3f {
        float x, y, z;
        
        vec3f();
        vec3f(float x, float y, float z);
        
        struct vec3f & operator () (const float & x, const float & y, const float & z);
        
        struct vec3f operator + (const struct vec3f & v) const;
        
        struct vec3f & operator += (const struct vec3f & v);
        
        struct vec3f operator - (const struct vec3f & v) const;
        
        struct vec3f & operator -= (const struct vec3f & v);
        
        struct vec3f operator * (const struct vec3f & v) const;
        
        struct vec3f & operator *= (const struct vec3f & v);
        
        struct vec3f operator / (const struct vec3f & v) const;
        
        struct vec3f & operator /= (const struct vec3f & v);
        
        struct vec3f operator - () const;
        
    };
}

#endif /* defined(__molphene__vec3f__) */

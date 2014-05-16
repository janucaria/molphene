#ifndef __molphene__vec3f__
#define __molphene__vec3f__

namespace molphene {
    struct vec3f {
        float x, y, z;
        
        vec3f();
        vec3f(float x, float y, float z);
        
        vec3f & operator () (const float & x, const float & y, const float & z);
        
        vec3f operator + (const vec3f & v) const;
        
        vec3f & operator += (const vec3f & v);
        
        vec3f operator - (const vec3f & v) const;
        
        vec3f & operator -= (const vec3f & v);
        
        vec3f operator * (const vec3f & v) const;
        
        vec3f & operator *= (const vec3f & v);
        
        vec3f operator / (const vec3f & v) const;
        
        vec3f & operator /= (const vec3f & v);
        
        vec3f operator - () const;
        
        vec3f operator + (const float & s) const;
        
        vec3f & operator += (const float & s);
        
        vec3f operator - (const float & s) const;
        
        vec3f & operator -= (const float & s);
        
        vec3f operator * (const float & s) const;
        
        vec3f & operator *= (const float & s);
        
        vec3f operator / (const float & s) const;
        
        vec3f & operator /= (const float & s);
        
    };
}

#endif /* defined(__molphene__vec3f__) */

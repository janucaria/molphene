#include "mat4f.h"

namespace molphene {
    mat4f::mat4f() :
        m{1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f}
    {
    }
    
    mat4f::mat4f(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44) :
    m{m11, m12, m13, m14,
        m21, m22, m23, m24,
        m31, m32, m33, m34,
        m41, m42, m43, m44}
    {
    }
    
    mat4f & mat4f::operator () (float m11, float m12, float m13, float m14,
                                float m21, float m22, float m23, float m24,
                                float m31, float m32, float m33, float m34,
                                float m41, float m42, float m43, float m44)
    {
        m[0] = m11;
        m[1] = m12;
        m[2] = m13;
        m[3] = m14;
        
        m[4] = m21;
        m[5] = m22;
        m[6] = m23;
        m[7] = m24;
        
        m[8] = m31;
        m[9] = m32;
        m[10] = m33;
        m[11] = m34;
        
        m[12] = m41;
        m[13] = m42;
        m[14] = m43;
        m[15] = m44;
        return *this;
    }
    
    mat4f & mat4f::operator () () {
        return (*this)(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    mat4f & mat4f::operator *= (const mat4f & mat4) {
        
        float m11 = m[0];
        float m12 = m[1];
        float m13 = m[2];
        float m14 = m[3];
        
        float m21 = m[4];
        float m22 = m[5];
        float m23 = m[6];
        float m24 = m[7];
        
        float m31 = m[8];
        float m32 = m[9];
        float m33 = m[10];
        float m34 = m[11];
        
        float m41 = m[12];
        float m42 = m[13];
        float m43 = m[14];
        float m44 = m[15];
        
        
        float n11 = mat4.m[0];
        float n12 = mat4.m[1];
        float n13 = mat4.m[2];
        float n14 = mat4.m[3];
        
        float n21 = mat4.m[4];
        float n22 = mat4.m[5];
        float n23 = mat4.m[6];
        float n24 = mat4.m[7];
        
        float n31 = mat4.m[8];
        float n32 = mat4.m[9];
        float n33 = mat4.m[10];
        float n34 = mat4.m[11];
        
        float n41 = mat4.m[12];
        float n42 = mat4.m[13];
        float n43 = mat4.m[14];
        float n44 = mat4.m[15];
        
        
        return (*this)(m11*n11 + m12*n21 + m13*n31 + m14*n41,
                       m11*n12 + m12*n22 + m13*n32 + m14*n42,
                       m11*n13 + m12*n23 + m13*n33 + m14*n43,
                       m11*n14 + m12*n24 + m13*n34 + m14*n44,
                         
                       m21*n11 + m22*n21 + m23*n31 + m24*n41,
                       m21*n12 + m22*n22 + m23*n32 + m24*n42,
                       m21*n13 + m22*n23 + m23*n33 + m24*n43,
                       m21*n14 + m22*n24 + m23*n34 + m24*n44,
                         
                       m31*n11 + m32*n21 + m33*n31 + m34*n41,
                       m31*n12 + m32*n22 + m33*n32 + m34*n42,
                       m31*n13 + m32*n23 + m33*n33 + m34*n43,
                       m31*n14 + m32*n24 + m33*n34 + m34*n44,
                         
                       m41*n11 + m42*n21 + m43*n31 + m44*n41,
                       m41*n12 + m42*n22 + m43*n32 + m44*n42,
                       m41*n13 + m42*n23 + m43*n33 + m44*n43,
                       m41*n14 + m42*n24 + m43*n34 + m44*n44);
    }
    
    mat4f mat4f::operator * (const mat4f & mat4) const {
        return mat4f(*this) *= mat4;
    }
    
    mat4f & mat4f::operator /= (const float & s) {
        m[0] /= s; m[1] /= s; m[2] /= s; m[3] /= s;
        
        m[4] /= s; m[5] /= s; m[6] /= s; m[7] /= s;
        
        m[8] /= s; m[9] /= s; m[10] /= s; m[11] /= s;
        
        m[12] /= s; m[13] /= s; m[14] /= s; m[15] /= s;
        
        return *this;
    }
    
    mat4f mat4f::operator / (const float & s) const {
        return mat4f(*this) /= s;
    }
    
    mat4f & mat4f::scale(const float & s) {
        return this->scale(s, s, s);
    }
    
    mat4f & mat4f::scale(const float & x, const float & y, const float & z) {
        m[0] *= x;
        m[5] *= y;
        m[10] *= z;
        return *this;
    }
    
    mat4f & mat4f::scale(const vec3f & v) {
        return this->scale(v.x, v.y, v.z);
    }
    
    mat4f & mat4f::rotate(float x, float y, float z, float a) {
        
        // zero rotation is nothing
        if(!a) return *this;
        
        float l = sqrtf(x*x + y*y + z*z);
        
        if(l == 0) {
            x = 0;
            y = 0;
            z = 1;
        } else if(l != 1) {
            x /= l;
            y /= l;
            z /= l;
        }
        
        
        float m11 = m[0];
        float m12 = m[1];
        float m13 = m[2];
        float m14 = m[3];
        
        float m21 = m[4];
        float m22 = m[5];
        float m23 = m[6];
        float m24 = m[7];
        
        float m31 = m[8];
        float m32 = m[9];
        float m33 = m[10];
        float m34 = m[11];
        
        float m41 = m[12];
        float m42 = m[13];
        float m43 = m[14];
        float m44 = m[15];
        
        float s = sinf(a);
        float c = cosf(a);
        float t = 1 - c;
        float xx = x*x;
        float xy = x*y;
        float yy = y*y;
        float yz = y*z;
        float zz = z*z;
        float zx = z*x;
        
        float n11 = c + t * xx;
        float n12 = t * xy + s * z;
        float n13 = t * zx - s * y;
        
        float n21 = t * xy - s * z;
        float n22 = c + t * yy;
        float n23 = t * yz + s * x;
        
        float n31 = t * zx + s * y;
        float n32 = t * yz - s * x;
        float n33 = c + t * zz;
        
        return (*this)(m11*n11 + m12*n21 + m13*n31,
                       m11*n12 + m12*n22 + m13*n32,
                       m11*n13 + m12*n23 + m13*n33,
                       m14,
                       
                       m21*n11 + m22*n21 + m23*n31,
                       m21*n12 + m22*n22 + m23*n32,
                       m21*n13 + m22*n23 + m23*n33,
                       m24,
                       
                       m31*n11 + m32*n21 + m33*n31,
                       m31*n12 + m32*n22 + m33*n32,
                       m31*n13 + m32*n23 + m33*n33,
                       m34,
                       
                       m41*n11 + m42*n21 + m43*n31,
                       m41*n12 + m42*n22 + m43*n32,
                       m41*n13 + m42*n23 + m43*n33,
                       m44);
    }
    
    mat4f & mat4f::translate(float x, float y, float z) {
        
        float m14 = m[3];
        float m24 = m[7];
        float m34 = m[11];
        float m44 = m[15];
        
        m[0] += m14*x;
        m[4] += m24*x;
        m[8] += m34*x;
        m[12] += m44*x;
        
        m[1] += m14*y;
        m[5] += m24*y;
        m[9] += m34*y;
        m[13] += m44*y;
        
        m[2] += m14*z;
        m[6] += m24*z;
        m[10] += m34*z;
        m[14] += m44*z;
        
        return *this;
    }
    
    mat4f & mat4f::translate(const vec3f & v) {
        return translate(v.x, v.y, v.z);
    }
    
    mat4f & mat4f::frustum(float l, float r, float b, float t, float n, float f) {
        
        m[0] = 2 * n / (r - l);
        m[5] = 2 * n / (t - b);
        m[8] = (r + l) / (r - l);
        m[9] = (t + b) / (t - b);
        m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[12] = m[13] = m[15] = 0;
        m[11] = -1;
        
        if(isfinite(f)) {
            m[10] = -(f + n) / (f - n);
            m[14] = -(2 * f * n) / (f - n);
        } else {
            m[10] = -1;
            m[14] = -2*n;
        }
        
        return *this;
    }
}
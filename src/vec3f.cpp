#include "vec3f.h"

namespace molphene {
    
    vec3f::vec3f() : x(0), y(0), z(0) {};
    
    vec3f::vec3f(float x, float y, float z) :
        x(x),
        y(y),
        z(z)
    {
    }
    
    vec3f & vec3f::operator () (const float & x, const float & y, const float & z) {
        this->x = x;
        this->y = y;
        this->z = z;
        return *this;
    }
    
    vec3f vec3f::operator + (const vec3f & v) const {
        return vec3f(*this) += v;
    }
    
    vec3f & vec3f::operator += (const vec3f & v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    
    vec3f vec3f::operator - (const vec3f & v) const {
        return vec3f(*this) -= v;
    }
    
    vec3f & vec3f::operator -= (const vec3f & v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    
    vec3f vec3f::operator * (const vec3f & v) const {
        return vec3f(*this) *= v;
    }
    
    vec3f & vec3f::operator *= (const vec3f & v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }
    
    vec3f vec3f::operator / (const vec3f & v) const {
        return vec3f(*this) /= v;
    }
    
    vec3f & vec3f::operator /= (const vec3f & v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }
    
    
    vec3f vec3f::operator - () const {
        return vec3f(-this->x, -this->y, -this->z);
    }
    
    
    vec3f vec3f::operator + (const float & s) const {
        return vec3f(*this) += s;
    }
    
    vec3f & vec3f::operator += (const float & s) {
        this->x += s;
        this->y += s;
        this->z += s;
        return *this;
    }
    
    vec3f vec3f::operator - (const float & s) const {
        return vec3f(*this) -= s;
    }
    
    vec3f & vec3f::operator -= (const float & s) {
        this->x -= s;
        this->y -= s;
        this->z -= s;
        return *this;
    }
    
    vec3f vec3f::operator * (const float & s) const {
        return vec3f(*this) *= s;
    }
    
    vec3f & vec3f::operator *= (const float & s) {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return *this;
    }
    
    
    vec3f vec3f::operator / (const float & s) const {
        return vec3f(*this) /= s;
    }
    
    vec3f & vec3f::operator /= (const float & s) {
        this->x /= s;
        this->y /= s;
        this->z /= s;
        return *this;
    }
    
    float vec3f::length() const {
        return sqrt(x * x + y * y + z * z);
    }
    
}
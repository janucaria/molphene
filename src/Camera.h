#ifndef __molphene__Camera__
#define __molphene__Camera__

#include "m3d.hpp"

namespace molphene {
    class Camera {
        float near;
        float far;
        float aspect;
        float fov;
        
        mat4f viewMatrix;
        mat4f projectionMatrix;
        
    public:
        Camera();
        
        void setFov(const float & val);
        
        void setNear(const float & val);
        
        void setFar(const float & val);
        
        void setAspect(const float & val);
        
        void updateProjectionMatrix();
        
        void translate(const float & x, const float & y, const float & z);
        
        void zoom(float z);
        
        const mat4f & getProjectionMatrix() const;
        
        const mat4f & getViewMatrix() const;
    };
}

#endif /* defined(__molphene__Camera__) */

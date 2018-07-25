#ifndef __Molphene__ColorLightRenderer__
#define __Molphene__ColorLightRenderer__

#include "logger.h"
#include "opengl.h"
#include "m3d.hpp"
#include "Renderer.h"

namespace molphene {
    class ColorLightRenderer : public Renderer {
        
    public:
        
        ColorLightRenderer();
        
        void setNormalMatrix(const mat3f & m);
        
    protected:
        const static char * vertexShaderSource;
        const static char * fragmentShaderSource;
        
        GLint gUniformNormalMatrixLocation;
        
        void setupGLProgram() override;
        
        void setupGLUniformsLocation() override;
    };
}

#endif /* defined(__Molphene__LightRenderer__) */

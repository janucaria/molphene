#ifndef __molphene__Renderer__
#define __molphene__Renderer__

#include "logger.h"
#include "opengl.h"
#include "vec3f.h"
#include "colour.h"
#include "mat4f.h"

namespace molphene {
    class Renderer {
        
    public:
        
        Renderer();
        
        bool setupGL();
        
        void setVericesSize(GLuint size);
        
        void setBufferPosition(const vec3f * data);
        
        void setBufferNormal(const vec3f * data);
        
        void setBufferColor(const colour * data);
        
        void setModelViewMatrix(const mat4f & m4);
        
        void setProjectionMatrix(const mat4f & m4);
        
        void setLightSourceAmbient(const float & r, const float & g, const float & b, const float & a);
        
        void setLightSourceDiffuse(const float & r, const float & g, const float & b, const float & a);
        
        void setLightSourceSpecular(const float & r, const float & g, const float & b, const float & a);
        
        void setLightSourcePosition(const float & x, const float & y, const float & z);
        
        void setMaterialAmbient(const float & r, const float & g, const float & b, const float & a);
        
        void setMaterialDiffuse(const float & r, const float & g, const float & b, const float & a);
        
        void setMaterialSpecular(const float & r, const float & g, const float & b, const float & a);
        
        void setMaterialShininess(const float & v);
        
        void render();
        
    private:
        const static char * vertexShaderSource;
        const static char * fragmentShaderSource;
        
        GLuint verticesSize;
        
        GLuint gProgram;
        
        GLuint gVertexShader;
        GLuint gFragmentShader;
        
        GLuint gVertexPositionLocation;
        GLuint gVertexNormalLocation;
        GLuint gVertexColorLocation;
        
        GLint gUniformModelViewMatrixLocation;
        GLint gUniformProjectionMatrixLocation;
        
        GLint gUniformLightSourceAmbientLocation;
        GLint gUniformLightSourceDiffuseLocation;
        GLint gUniformLightSourceSpecularLocation;
        GLint gUniformLightSourcePositionLocation;
        
        GLint gUniformMaterialAmbientLocation;
        GLint gUniformMaterialDiffuseLocation;
        GLint gUniformMaterialSpecularLocation;
        GLint gUniformMaterialShininessLocation;
        
        GLuint gPositionBuffer;
        GLuint gNormalBuffer;
        GLuint gColorBuffer;
        
        GLuint createShader(GLenum shaderType, const char* pSource);
        GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader);
        
    };
}

#endif /* defined(__molphene__Renderer__) */

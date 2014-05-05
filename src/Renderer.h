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
        
        void setVericesSize(GLsizei size);
        
        void setBufferPosition(const vec3f * data);
        
        void setBufferColor(const colour * data);
        
        void setModelViewMatrix(const mat4f & m4);
        
        void setProjectionMatrix(const mat4f & m4);
        
        void render();
        
    private:
        const static char * vertexShaderSource;
        const static char * fragmentShaderSource;
        
        GLsizei verticesSize;
        
        GLuint gProgram;
        
        GLuint gVertexShader;
        GLuint gFragmentShader;
        
        GLuint gVertexPositionLocation;
        GLuint gVertexColorLocation;
        
        GLint gUniformModelViewMatrixLocation;
        GLint gUniformProjectionMatrixLocation;
        
        GLuint gPositionBuffer;
        GLuint gColorBuffer;
        
        GLuint createShader(GLenum shaderType, const char* pSource);
        GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader);
        
    };
}

#endif /* defined(__molphene__Renderer__) */

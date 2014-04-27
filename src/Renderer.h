#ifndef __molphene__Renderer__
#define __molphene__Renderer__

#include "logger.h"
#include "opengl.h"
#include "vec3f.h"
#include "colour.h"

namespace molphene {
    class Renderer {
        
    public:
        
        Renderer();
        
        bool setupGL();
        
        void setVericesSize(GLsizei size);
        
        void setBufferPosition(const struct vec3f * data);
        
        void setBufferColor(const struct colour * data);
        
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
        
        GLuint gPositionBuffer;
        GLuint gColorBuffer;
        
        GLuint createShader(GLenum shaderType, const char* pSource);
        GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader);
        
    };
}

#endif /* defined(__molphene__Renderer__) */

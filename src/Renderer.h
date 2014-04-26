#ifndef __molphene__Renderer__
#define __molphene__Renderer__

#include "logger.h"
#include "opengl.h"

namespace molphene {
    class Renderer {
        
    public:
        
        Renderer();
        
        bool setupGL();
        
        void setVericesSize(GLsizei size);
        
        void setBufferPosition(const GLfloat * data);
        
        void render();
        
    private:
        const static char * vertexShaderSource;
        const static char * fragmentShaderSource;
        
        GLsizei verticesSize;
        
        GLuint gProgram;
        
        GLuint gVertexShader;
        GLuint gFragmentShader;
        
        GLuint gVertexPositionLocation;
        
        GLuint gPositionBuffer;
        
        GLuint createShader(GLenum shaderType, const char* pSource);
        GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader);
        
    };
}

#endif /* defined(__molphene__Renderer__) */

#include "Renderer.h"

namespace molphene {
    
    Renderer::Renderer() :
        gProgram(0),
        gVertexShader(0),
        gFragmentShader(0)
    {
        
    }
    
    bool Renderer::setupGL() {
        
        gVertexShader = createShader(GL_VERTEX_SHADER, Renderer::vertexShaderSource);
        gFragmentShader = createShader(GL_FRAGMENT_SHADER, Renderer::fragmentShaderSource);
        gProgram = createProgram(gVertexShader, gFragmentShader);
        
        gVertexPositionLocation = glGetAttribLocation(gProgram, "a_Position");
        
        glGenBuffers(1, &gPositionBuffer);
        
        return true;
    }
    
    
    void Renderer::setVericesSize(GLsizei size) {
        verticesSize = size;
    }
    
    void Renderer::setBufferPosition(const struct vec3f * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f) * verticesSize, data, GL_STATIC_DRAW);
    }
    
    void Renderer::render() {
        
        glUseProgram(gProgram);
        
        glEnableVertexAttribArray(gVertexPositionLocation);
        
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glVertexAttribPointer(gVertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(gVertexPositionLocation);
        
        
        glFlush();
    }
    
    GLuint Renderer::createShader(GLenum shaderType, const char* pSource) {
        GLuint shader = glCreateShader(shaderType);
        if (shader) {
            glShaderSource(shader, 1, &pSource, NULL);
            glCompileShader(shader);
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char* buf = (char*) malloc(infoLen);
                    if (buf) {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        LOG_E("Could not compile shader %d:\n%s\n", shaderType, buf);
                        free(buf);
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }
        return shader;
    }
    
    
    GLuint Renderer::createProgram(const GLuint vertexShader, const GLuint fragmentShader) {
        
        if (!vertexShader || !fragmentShader) {
            return 0;
        }
        
        GLuint program = glCreateProgram();
        if (program) {
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
            if (linkStatus != GL_TRUE) {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength) {
                    char* buf = (char*) malloc(bufLength);
                    if (buf) {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        LOG_E("Could not link program:\n%s\n", buf);
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
        return program;
    }
    
    const char * Renderer::vertexShaderSource = R"(
    attribute vec3 a_Position;
    
    void main() {
        gl_Position = vec4(a_Position, 1.0);
    }
    )";
    
    const char * Renderer::fragmentShaderSource = R"(
    
    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    
    )";
}

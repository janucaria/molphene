#include "Renderer.h"

namespace molphene {
    
    Renderer::Renderer() :
        gProgram(0),
        gVertexShader(0),
        gFragmentShader(0),
        gUniformModelViewMatrixLocation(-1)
    {
        
    }
    
    bool Renderer::setupGL() {
        
        gVertexShader = createShader(GL_VERTEX_SHADER, Renderer::vertexShaderSource);
        gFragmentShader = createShader(GL_FRAGMENT_SHADER, Renderer::fragmentShaderSource);
        gProgram = createProgram(gVertexShader, gFragmentShader);
        
        gVertexPositionLocation = glGetAttribLocation(gProgram, "a_Position");
        gVertexColorLocation = glGetAttribLocation(gProgram, "a_Color");
        
        gUniformModelViewMatrixLocation = glGetUniformLocation(gProgram, "u_ModelViewMatrix");
        
        glGenBuffers(1, &gPositionBuffer);
        glGenBuffers(1, &gColorBuffer);
        
        return true;
    }
    
    
    void Renderer::setVericesSize(GLsizei size) {
        verticesSize = size;
        
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f) * verticesSize, nullptr, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(struct colour) * verticesSize , nullptr, GL_DYNAMIC_DRAW);
    }
    
    void Renderer::setBufferPosition(const struct vec3f * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec3f) * verticesSize, data);
    }
    
    void Renderer::setBufferColor(const struct colour * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct colour) * verticesSize, data);
    }
    
    void Renderer::setModelViewMatrix(const mat4f & m4) {
        glUseProgram(gProgram);
        glUniformMatrix4fv(gUniformModelViewMatrixLocation, 1, GL_FALSE, m4.m);
    }
    
    void Renderer::render() {
        
        glUseProgram(gProgram);
        
        glEnableVertexAttribArray(gVertexPositionLocation);
        glEnableVertexAttribArray(gVertexColorLocation);
        
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glVertexAttribPointer(gVertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glVertexAttribPointer(gVertexColorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(gVertexPositionLocation);
        glDisableVertexAttribArray(gVertexColorLocation);
        
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
    attribute vec4 a_Color;
    
    uniform mat4 u_ModelViewMatrix;
    
    varying vec4 v_Color;
    void main() {
        v_Color = a_Color;
        gl_Position = u_ModelViewMatrix * vec4(a_Position, 1.0);
    }
    )";
    
    const char * Renderer::fragmentShaderSource = R"(
    varying vec4 v_Color;
    void main() {
        gl_FragColor = v_Color;
    }
    
    )";
}

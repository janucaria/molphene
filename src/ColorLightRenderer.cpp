#include "ColorLightRenderer.h"


namespace molphene {
    
    ColorLightRenderer::ColorLightRenderer() :
    gProgram(0),
    gVertexShader(0),
    gFragmentShader(0),
    gUniformModelViewMatrixLocation(-1),
    gUniformNormalMatrixLocation(-1),
    gUniformProjectionMatrixLocation(-1)
    {
        
    }
    
    bool ColorLightRenderer::setupGL() {
        
        gVertexShader = createShader(GL_VERTEX_SHADER, ColorLightRenderer::vertexShaderSource);
        gFragmentShader = createShader(GL_FRAGMENT_SHADER, ColorLightRenderer::fragmentShaderSource);
        gProgram = createProgram(gVertexShader, gFragmentShader);
        
        gVertexPositionLocation = glGetAttribLocation(gProgram, "a_Position");
        gVertexNormalLocation = glGetAttribLocation(gProgram, "a_Normal");
        gVertexColorLocation = glGetAttribLocation(gProgram, "a_Color");
        
        gUniformModelViewMatrixLocation = glGetUniformLocation(gProgram, "u_ModelViewMatrix");
        gUniformNormalMatrixLocation = glGetUniformLocation(gProgram, "u_NormalMatrix");
        gUniformProjectionMatrixLocation = glGetUniformLocation(gProgram, "u_ProjectionMatrix");
        
        gUniformLightSourceAmbientLocation = glGetUniformLocation(gProgram, "u_LightSource_ambient");
        gUniformLightSourceDiffuseLocation = glGetUniformLocation(gProgram, "u_LightSource_diffuse");
        gUniformLightSourceSpecularLocation = glGetUniformLocation(gProgram, "u_LightSource_specular");
        gUniformLightSourcePositionLocation = glGetUniformLocation(gProgram, "u_LightSource_position");
        
        gUniformMaterialAmbientLocation = glGetUniformLocation(gProgram, "u_Material_ambient");
        gUniformMaterialDiffuseLocation = glGetUniformLocation(gProgram, "u_Material_diffuse");
        gUniformMaterialSpecularLocation = glGetUniformLocation(gProgram, "u_Material_specular");
        gUniformMaterialShininessLocation = glGetUniformLocation(gProgram, "u_Material_shininess");
        
        glGenBuffers(1, &gPositionBuffer);
        glGenBuffers(1, &gNormalBuffer);
        glGenBuffers(1, &gColorBuffer);
        
        return true;
    }
    
    
    void ColorLightRenderer::setVericesSize(GLuint size) {
        verticesSize = size;
        
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * verticesSize, nullptr, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, gNormalBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * verticesSize, nullptr, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colour) * verticesSize , nullptr, GL_DYNAMIC_DRAW);
    }
    
    void ColorLightRenderer::setBufferPosition(const vec3f * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3f) * verticesSize, data);
    }
    
    void ColorLightRenderer::setBufferNormal(const vec3f * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gNormalBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3f) * verticesSize, data);
    }
    
    void ColorLightRenderer::setBufferColor(const colour * data) {
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colour) * verticesSize, data);
    }
    
    void ColorLightRenderer::setModelViewMatrix(const mat4f & m4) {
        glUniformMatrix4fv(gUniformModelViewMatrixLocation, 1, GL_FALSE, m4.m);
    }
    
    void ColorLightRenderer::setNormalMatrix(const mat3f & m) {
        glUniformMatrix3fv(gUniformNormalMatrixLocation, 1, GL_FALSE, m.m);
    }
    
    void ColorLightRenderer::setProjectionMatrix(const mat4f & m4) {
        glUniformMatrix4fv(gUniformProjectionMatrixLocation, 1, GL_FALSE, m4.m);
    }
    
    void ColorLightRenderer::setLightSourceAmbient(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformLightSourceAmbientLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setLightSourceDiffuse(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformLightSourceDiffuseLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setLightSourceSpecular(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformLightSourceSpecularLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setLightSourcePosition(const float & x, const float & y, const float & z) {
        glUniform4f(gUniformLightSourcePositionLocation, x, y, z, 1.0f);
    }
    
    void ColorLightRenderer::setMaterialAmbient(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformMaterialAmbientLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setMaterialDiffuse(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformMaterialDiffuseLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setMaterialSpecular(const float & r, const float & g, const float & b, const float & a) {
        glUniform4f(gUniformMaterialSpecularLocation, r, g, b, a);
    }
    
    void ColorLightRenderer::setMaterialShininess(const float & v) {
        glUniform1f(gUniformMaterialShininessLocation, v);
    }
    
    void ColorLightRenderer::render() {
        
        glEnableVertexAttribArray(gVertexPositionLocation);
        glEnableVertexAttribArray(gVertexColorLocation);
        glEnableVertexAttribArray(gVertexNormalLocation);
        
        glBindBuffer(GL_ARRAY_BUFFER, gPositionBuffer);
        glVertexAttribPointer(gVertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, gNormalBuffer);
        glVertexAttribPointer(gVertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, gColorBuffer);
        glVertexAttribPointer(gVertexColorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, verticesSize);
        
        glDisableVertexAttribArray(gVertexPositionLocation);
        glDisableVertexAttribArray(gVertexColorLocation);
        glDisableVertexAttribArray(gVertexNormalLocation);
        
        glFlush();
    }
    
    GLuint ColorLightRenderer::createShader(GLenum shaderType, const char* pSource) {
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
    
    
    GLuint ColorLightRenderer::createProgram(const GLuint vertexShader, const GLuint fragmentShader) {
        
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
    
    void ColorLightRenderer::useGLProgram() const {
        glUseProgram(gProgram);
    }
    
    const char * ColorLightRenderer::vertexShaderSource = R"(
    attribute vec3 a_Position;
    attribute vec3 a_Normal;
    attribute vec4 a_Color;
    
    uniform mat4 u_ModelViewMatrix;
    uniform mat3 u_NormalMatrix;
    uniform mat4 u_ProjectionMatrix;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec4 v_Color;
    void main() {
        vec4 position = vec4(a_Position, 1.0);
        position = u_ModelViewMatrix * position;
        position /= position.w;
        v_Position = position.xyz;
        v_Color = a_Color;
        v_Normal = u_NormalMatrix * a_Normal;
        gl_Position = u_ProjectionMatrix * position;
        gl_Position /= gl_Position.w;
    }
    )";
    
    const char * ColorLightRenderer::fragmentShaderSource = R"(
#ifdef GL_ES
    precision highp float;
#endif
    
    uniform vec4 u_LightSource_ambient;
    uniform vec4 u_LightSource_diffuse;
    uniform vec4 u_LightSource_specular;
    uniform vec4 u_LightSource_position;
    
    uniform vec4 u_Material_ambient;
    uniform vec4 u_Material_diffuse;
    uniform vec4 u_Material_specular;
    uniform float u_Material_shininess;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec4 v_Color;
    void main() {
        
        vec3 eyePos   = normalize(-v_Position);
        vec3 normal   = v_Normal;
        vec4 finalColor = vec4(0.0);
        
        normal = normalize(normal);
        
        finalColor += u_LightSource_ambient * u_Material_ambient;
        
        vec3 lightDir = normalize(u_LightSource_position.xyz - v_Position);
        float lambertTerm = max(0.0, dot(normal, lightDir));
        
        if(lambertTerm > 0.0) {
            vec4 diffuse = u_LightSource_diffuse * u_Material_diffuse * lambertTerm;
            
            vec3 reflection = -reflect(lightDir, normal);
            
            vec4 specular = u_LightSource_specular * u_Material_specular * pow(max(0.0, dot(reflection, eyePos)), u_Material_shininess);
            
            finalColor += diffuse + specular;
        }
        
        gl_FragColor = v_Color * finalColor;
    }
    
    )";
}
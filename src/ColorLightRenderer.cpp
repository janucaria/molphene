#include "ColorLightRenderer.h"


namespace molphene {
    
    ColorLightRenderer::ColorLightRenderer() :
    gUniformNormalMatrixLocation(-1)
    {
        
    }
    
    void ColorLightRenderer::setupGLUniformsLocation() {
        Renderer::setupGLUniformsLocation();
        gUniformNormalMatrixLocation = glGetUniformLocation(gProgram, "u_NormalMatrix");
    }
    
    void ColorLightRenderer::setupGLProgram() {
        gVertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
        gFragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        gProgram = createProgram(gVertexShader, gFragmentShader);
    }
    
    void ColorLightRenderer::setNormalMatrix(const mat3f & m) {
        glUniformMatrix3fv(gUniformNormalMatrixLocation, 1, GL_FALSE, m.m);
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
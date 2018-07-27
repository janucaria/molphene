#include "ColorLightRenderer.h"

namespace molphene {

ColorLightRenderer::ColorLightRenderer()
: gUniformNormalMatrixLocation(-1)
{
}

void
ColorLightRenderer::setupGLProgram()
{
  Renderer::setupGLProgram();

  gVertexPositionLocation = glGetAttribLocation(gProgram, "a_Position");
  gVertexNormalLocation = glGetAttribLocation(gProgram, "a_Normal");
  gVertexColorLocation = glGetAttribLocation(gProgram, "a_Color");
}

void
ColorLightRenderer::setupGLUniformsLocation()
{
  gUniformModelViewMatrixLocation =
   glGetUniformLocation(gProgram, "u_ModelViewMatrix");
  gUniformNormalMatrixLocation =
   glGetUniformLocation(gProgram, "u_NormalMatrix");
  gUniformProjectionMatrixLocation =
   glGetUniformLocation(gProgram, "u_ProjectionMatrix");

  gUniformLightSourceAmbientLocation =
   glGetUniformLocation(gProgram, "u_LightSource_ambient");
  gUniformLightSourceDiffuseLocation =
   glGetUniformLocation(gProgram, "u_LightSource_diffuse");
  gUniformLightSourceSpecularLocation =
   glGetUniformLocation(gProgram, "u_LightSource_specular");
  gUniformLightSourcePositionLocation =
   glGetUniformLocation(gProgram, "u_LightSource_position");

  g_uloc_material_ambient =
   glGetUniformLocation(gProgram, "u_Material_ambient");
  g_uloc_material_diffuse =
   glGetUniformLocation(gProgram, "u_Material_diffuse");
  g_uloc_material_specular =
   glGetUniformLocation(gProgram, "u_Material_specular");
  g_uloc_material_shininess =
   glGetUniformLocation(gProgram, "u_Material_shininess");
}

void
ColorLightRenderer::setNormalMatrix(const mat3f& m)
{
  glUniformMatrix3fv(gUniformNormalMatrixLocation, 1, GL_FALSE, m.m);
}

void
ColorLightRenderer::setModelViewMatrix(const mat4f& m4)
{
  glUniformMatrix4fv(gUniformModelViewMatrixLocation, 1, GL_FALSE, m4.m);
}

void
ColorLightRenderer::setProjectionMatrix(const mat4f& m4)
{
  glUniformMatrix4fv(gUniformProjectionMatrixLocation, 1, GL_FALSE, m4.m);
}

void
ColorLightRenderer::setLightSourceAmbient(const float& r,
                                          const float& g,
                                          const float& b,
                                          const float& a)
{
  glUniform4f(gUniformLightSourceAmbientLocation, r, g, b, a);
}

void
ColorLightRenderer::setLightSourceDiffuse(const float& r,
                                          const float& g,
                                          const float& b,
                                          const float& a)
{
  glUniform4f(gUniformLightSourceDiffuseLocation, r, g, b, a);
}

void
ColorLightRenderer::setLightSourceSpecular(const float& r,
                                           const float& g,
                                           const float& b,
                                           const float& a)
{
  glUniform4f(gUniformLightSourceSpecularLocation, r, g, b, a);
}

void
ColorLightRenderer::setLightSourcePosition(const float& x,
                                           const float& y,
                                           const float& z)
{
  glUniform4f(gUniformLightSourcePositionLocation, x, y, z, 1.0f);
}

void
ColorLightRenderer::render(color_light_buffer& buff)
{
  buff.render(GL_TRIANGLE_STRIP,
              gVertexPositionLocation,
              gVertexColorLocation,
              gVertexNormalLocation);
}

const char*
ColorLightRenderer::vert_shader_source()
{
  return R"(
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
        v_Normal = length(a_Normal) != 0.0 ? u_NormalMatrix * a_Normal : a_Normal;
        gl_Position = u_ProjectionMatrix * position;
        gl_Position /= gl_Position.w;
    }
    )";
}

const char*
ColorLightRenderer::frag_shader_source()
{
  return R"(
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
        vec4 finalColor = vec4(0.);
        vec4 ambient = u_LightSource_ambient * u_Material_ambient;
        vec4 diffuse = u_LightSource_diffuse * u_Material_diffuse;
        vec4 specular = u_LightSource_specular * u_Material_specular;
        
        finalColor += ambient;
        
        if(length(v_Normal) == 0.) {
            finalColor += diffuse + specular * pow(1., u_Material_shininess);
            gl_FragColor = v_Color * finalColor;
        } else {
            vec3 eyePos   = normalize(-v_Position);
            vec3 normal   = normalize(v_Normal);
            
            vec3 lightDir = normalize(u_LightSource_position.xyz - v_Position);
            float lambertTerm = max(0.0, dot(normal, lightDir));
            
            if(lambertTerm > 0.0) {
                vec3 reflection = -reflect(lightDir, normal);
                
                diffuse *= lambertTerm;
                specular *= pow(max(0.0, dot(reflection, eyePos)), u_Material_shininess);
                finalColor += diffuse + specular;
            }
            
            gl_FragColor = v_Color * finalColor;
        }
    }
    
    )";
}

} // namespace molphene
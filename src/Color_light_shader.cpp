#include "Color_light_shader.hpp"

namespace molphene {

Color_light_shader::Color_light_shader()
{
}

typename Color_light_shader::Attribs_location_name_type
Color_light_shader::get_attribs_location() const noexcept
{
  return {{{Attrib_location::vertex, "a_Vertex"},
           {Attrib_location::normal, "a_Normal"},
           {Attrib_location::color, "a_Color"}}};
}

void
Color_light_shader::setup_gl_uniforms_loc() noexcept
{
  g_uloc_modelview_matrix =
   glGetUniformLocation(g_program, "u_ModelViewMatrix");
  g_uloc_projection_matrix =
   glGetUniformLocation(g_program, "u_ProjectionMatrix");
  g_uloc_normal_matrix = glGetUniformLocation(g_program, "u_NormalMatrix");

  g_uloc_light_source_ambient =
   glGetUniformLocation(g_program, "u_LightSource_ambient");
  g_uloc_light_source_diffuse =
   glGetUniformLocation(g_program, "u_LightSource_diffuse");
  g_uloc_light_source_specular =
   glGetUniformLocation(g_program, "u_LightSource_specular");
  g_uloc_light_source_position =
   glGetUniformLocation(g_program, "u_LightSource_position");

  g_uloc_material_ambient =
   glGetUniformLocation(g_program, "u_Material_ambient");
  g_uloc_material_diffuse =
   glGetUniformLocation(g_program, "u_Material_diffuse");
  g_uloc_material_specular =
   glGetUniformLocation(g_program, "u_Material_specular");
  g_uloc_material_shininess =
   glGetUniformLocation(g_program, "u_Material_shininess");
}

void
Color_light_shader::setup_gl_uniforms_val() const noexcept
{
}

void
Color_light_shader::setup_gl_attribs_val() const noexcept
{
  glVertexAttrib4f(Attrib_location::vertex, 0, 0, 0, 1);
}

void
Color_light_shader::modelview_matrix(const Mat4f& m4) const noexcept
{
  glUniformMatrix4fv(
   g_uloc_modelview_matrix, 1, GL_FALSE, static_cast<const float*>(m4.m));
}

void
Color_light_shader::normal_matrix(const Mat3f& m) const noexcept
{
  glUniformMatrix3fv(
   g_uloc_normal_matrix, 1, GL_FALSE, static_cast<const float*>(m.m));
}

void
Color_light_shader::projection_matrix(const Mat4f& m4) const noexcept
{
  glUniformMatrix4fv(
   g_uloc_projection_matrix, 1, GL_FALSE, static_cast<const float*>(m4.m));
}

void
Color_light_shader::render(color_light_buffer& buff)
{
  buff.render(GL_TRIANGLE_STRIP,
              Attrib_location::vertex,
              Attrib_location::normal,
              Attrib_location::color);
}

const char*
Color_light_shader::vert_shader_source() const noexcept
{
  return R"(
    attribute vec4 a_Vertex;
    attribute vec3 a_Normal;
    attribute vec4 a_Color;
    
    uniform mat4 u_ModelViewMatrix;
    uniform mat3 u_NormalMatrix;
    uniform mat4 u_ProjectionMatrix;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec4 v_Color;
    void main() {
        vec4 position = u_ModelViewMatrix * a_Vertex;
        v_Position = position.xyz / position.w;
        v_Color = a_Color;
        v_Normal = length(a_Normal) != 0.0 ? u_NormalMatrix * a_Normal : a_Normal;
        gl_Position = u_ProjectionMatrix * position;
        gl_Position /= gl_Position.w;
    }
    )";
}

const char*
Color_light_shader::frag_shader_source() const noexcept
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
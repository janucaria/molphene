#include "Color_light_shader.hpp"

namespace molphene {

Color_light_shader::Color_light_shader() noexcept = default;

typename Color_light_shader::Attribs_location_name_type
Color_light_shader::get_attribs_location() const noexcept
{
  return {{{Attrib_location::vertex, "a_Vertex"},
           {Attrib_location::normal, "a_Normal"},
           {Attrib_location::texcoord0, "a_TexCoord0"}}};
}

void
Color_light_shader::setup_gl_uniforms_loc() noexcept
{
  g_uloc_modelview_matrix =
   glGetUniformLocation(g_program, "u_ModelViewMatrix");
  g_uloc_projection_matrix =
   glGetUniformLocation(g_program, "u_ProjectionMatrix");
  g_uloc_normal_matrix = glGetUniformLocation(g_program, "u_NormalMatrix");

  g_uloc_light_source_color =
   glGetUniformLocation(g_program, "u_LightSource_color");
  g_uloc_light_source_direction =
   glGetUniformLocation(g_program, "u_LightSource_direction");
  g_uloc_light_source_ambient_intensity =
   glGetUniformLocation(g_program, "u_LightSource_ambientIntensity");
  g_uloc_light_source_intensity =
   glGetUniformLocation(g_program, "u_LightSource_intensity");

  g_uloc_material_ambient_intensity =
   glGetUniformLocation(g_program, "u_Material_ambientIntensity");
  g_uloc_material_emissive_color =
   glGetUniformLocation(g_program, "u_Material_emissiveColor");
  g_uloc_material_diffuse_color =
   glGetUniformLocation(g_program, "u_Material_diffuseColor");
  g_uloc_material_specular_color =
   glGetUniformLocation(g_program, "u_Material_specularColor");
  g_uloc_material_shininess =
   glGetUniformLocation(g_program, "u_Material_shininess");
}

void
Color_light_shader::setup_gl_uniforms_val() const noexcept
{
  glUniform1i(glGetUniformLocation(g_program, "u_TexColor"), 0);
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
Color_light_shader::color_texture_image(GLuint texture) const noexcept
{
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, texture);
}

const char*
Color_light_shader::vert_shader_source() const noexcept
{
  return R"(
    attribute vec4 a_Vertex;
    attribute vec3 a_Normal;
    attribute vec2 a_TexCoord0;
    
    uniform mat4 u_ModelViewMatrix;
    uniform mat3 u_NormalMatrix;
    uniform mat4 u_ProjectionMatrix;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec2 v_ColorTexCoord;
    void main() {
        vec4 position = u_ModelViewMatrix * a_Vertex;
        v_Position = position.xyz / position.w;
        v_ColorTexCoord = a_TexCoord0;
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
    uniform float u_LightSource_ambientIntensity;
    uniform float u_LightSource_intensity;
    uniform vec3 u_LightSource_direction;
    uniform vec4 u_LightSource_color;
    
    uniform float u_Material_ambientIntensity;
    uniform vec4 u_Material_emissiveColor;
    uniform vec4 u_Material_diffuseColor;
    uniform vec4 u_Material_specularColor;
    uniform float u_Material_shininess;
    // uniform float u_Material_transparency

    uniform sampler2D u_TexColor;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec2 v_ColorTexCoord;
    void main() {
        vec4 texRgba = texture2D(u_TexColor, v_ColorTexCoord.st);
        vec3 ILrgb = u_LightSource_color.rgb;
        float Ii = u_LightSource_intensity;
        float Iia = u_LightSource_ambientIntensity;

        float Oa = u_Material_ambientIntensity;
        vec3 ODrgb = texRgba.rgb * u_Material_diffuseColor.rgb;
        vec3 OErgb = u_Material_emissiveColor.rgb;
        vec3 OSrgb = u_Material_specularColor.rgb;
        float shininess = u_Material_shininess;

        vec3 L = -u_LightSource_direction;
        vec3 N = normalize(v_Normal);
        vec3 V = normalize(v_Position);

        vec3 ambienti = Iia * ODrgb * Oa;
        vec3 diffusei = Ii * ODrgb * dot( N, L );
        vec3 speculari = Ii * OSrgb * pow(dot( N , ((L + V) / normalize(L + V))), shininess * 128.);

        vec3 Irgb = OErgb + (ILrgb * (ambienti + diffusei + speculari));
        float A = texRgba.a;
        gl_FragColor = vec4(Irgb, A);
    }
    
    )";
}

} // namespace molphene
#include "ColorLightShader.hpp"

namespace molphene {

ColorLightShader::ColorLightShader() noexcept = default;

typename ColorLightShader::AttribsLocationName
ColorLightShader::get_attribs_location() const noexcept
{
  return {{{ShaderAttribLocation::vertex, "a_Vertex"},
           {ShaderAttribLocation::normal, "a_Normal"},
           {ShaderAttribLocation::texcoordcolor, "a_TexCoord0"}}};
}

void
ColorLightShader::setup_gl_uniforms_loc() noexcept
{
  g_uloc_modelview_matrix =
   glGetUniformLocation(g_program, "u_ModelViewMatrix");
  g_uloc_projection_matrix =
   glGetUniformLocation(g_program, "u_ProjectionMatrix");
  g_uloc_normal_matrix = glGetUniformLocation(g_program, "u_NormalMatrix");

  g_uloc_light_source_ambient_intensity =
   glGetUniformLocation(g_program, "u_LightSource_ambientIntensity");
  g_uloc_light_source_attenuation =
   glGetUniformLocation(g_program, "u_LightSource_attenuation");
  g_uloc_light_source_color =
   glGetUniformLocation(g_program, "u_LightSource_color");
  g_uloc_light_source_direction =
   glGetUniformLocation(g_program, "u_LightSource_direction");
  g_uloc_light_source_intensity =
   glGetUniformLocation(g_program, "u_LightSource_intensity");
  g_uloc_light_source_position =
   glGetUniformLocation(g_program, "u_LightSource_position");
  g_uloc_light_source_radius =
   glGetUniformLocation(g_program, "u_LightSource_radius");
  g_uloc_light_source_beam_width =
   glGetUniformLocation(g_program, "u_LightSource_beamWidth");
  g_uloc_light_source_cut_off_angle =
   glGetUniformLocation(g_program, "u_LightSource_cutOffAngle");

  g_uloc_material_ambient_intensity =
   glGetUniformLocation(g_program, "u_Material_ambientIntensity");
  g_uloc_material_emissive_color =
   glGetUniformLocation(g_program, "u_Material_emissiveColor");
  g_uloc_material_diffuse_color =
   glGetUniformLocation(g_program, "u_Material_diffuseColor");
  g_uloc_material_shininess =
   glGetUniformLocation(g_program, "u_Material_shininess");
  g_uloc_material_specular_color =
   glGetUniformLocation(g_program, "u_Material_specularColor");

  g_uloc_fog_color = glGetUniformLocation(g_program, "u_Fog_color");
  g_uloc_fog_fog_type = glGetUniformLocation(g_program, "u_Fog_fogTypeLinear");
  g_uloc_fog_visibility_range =
   glGetUniformLocation(g_program, "u_Fog_visibilityRange");
}

void
ColorLightShader::setup_gl_uniforms_val() const noexcept
{
  glUniform1i(glGetUniformLocation(g_program, "u_TexColor"), 0);
}

void
ColorLightShader::setup_gl_attribs_val() const noexcept
{
  glVertexAttrib4f(static_cast<GLuint>(ShaderAttribLocation::vertex), 0, 0, 0, 1);
}

void
ColorLightShader::modelview_matrix(const Mat4f& m4) const noexcept
{
  glUniformMatrix4fv(
   g_uloc_modelview_matrix, 1, GL_FALSE, static_cast<const float*>(m4.m));
}

void
ColorLightShader::normal_matrix(const Mat3f& m) const noexcept
{
  glUniformMatrix3fv(
   g_uloc_normal_matrix, 1, GL_FALSE, static_cast<const float*>(m.m));
}

void
ColorLightShader::projection_matrix(const Mat4f& m4) const noexcept
{
  glUniformMatrix4fv(
   g_uloc_projection_matrix, 1, GL_FALSE, static_cast<const float*>(m4.m));
}

void
ColorLightShader::color_texture_image(GLuint texture) const noexcept
{
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, texture);
}

const char*
ColorLightShader::vert_shader_source() const noexcept
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
ColorLightShader::frag_shader_source() const noexcept
{
  return R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform float u_LightSource_ambientIntensity;
    uniform vec3 u_LightSource_attenuation;
    uniform float u_LightSource_beamWidth;
    uniform vec4 u_LightSource_color;
    uniform float u_LightSource_cutOffAngle;
    uniform vec3 u_LightSource_direction;
    uniform float u_LightSource_intensity;
    uniform vec3 u_LightSource_position;
    uniform float u_LightSource_radius;

    uniform float u_Material_ambientIntensity;
    uniform vec4 u_Material_emissiveColor;
    uniform vec4 u_Material_diffuseColor;
    uniform float u_Material_shininess;
    uniform vec4 u_Material_specularColor;
    // uniform float u_Material_transparency

    uniform vec4 u_Fog_color;
    uniform bool u_Fog_fogTypeLinear;
    uniform float u_Fog_visibilityRange;

    uniform sampler2D u_TexColor;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec2 v_ColorTexCoord;

    float fogInterpolant(float dV) {
      float fogVisibility = u_Fog_visibilityRange;

      if(fogVisibility == 0.) {
        return 1.;
      }
      
      if(u_Fog_fogTypeLinear) {
        if(dV < fogVisibility) {
          return (fogVisibility-dV) / fogVisibility;
        }
      } else if(dV < fogVisibility) {
        return exp(-dV / (fogVisibility-dV ) );
      }
      return 0.;
    }

    void main() {
      vec4 texRgba = texture2D(u_TexColor, v_ColorTexCoord.st);
      bool isDirLight = u_LightSource_radius < 0.;

      vec3 N = normalize(v_Normal);
      vec3 V = normalize(v_Position);

      float Oa = u_Material_ambientIntensity;
      vec3 ODrgb = texRgba.rgb * u_Material_diffuseColor.rgb;
      vec3 OErgb = u_Material_emissiveColor.rgb;
      vec3 OSrgb = u_Material_specularColor.rgb;
      float shininess = u_Material_shininess;

      float dV = length(v_Position);
      float f0 = fogInterpolant(dV);
      vec3 IFrgb = u_Fog_color.rgb;
      
      vec3 sumLights = vec3(0.);
      for(int i = 0; i < 1; ++i) {
        float attenuationi = 0.;
        float spoti = 1.;
        vec3 L;
        if(isDirLight) {
          L = -u_LightSource_direction;
          attenuationi = 1.;
        } else {
          vec3 distLP = u_LightSource_position - v_Position;
          float dL = length(distLP);
          L = normalize(distLP);

          if(length(u_LightSource_attenuation) != 0. && dL <= u_LightSource_radius) {
            float c1 = u_LightSource_attenuation.x;
            float c2 = u_LightSource_attenuation.y;
            float c3 = u_LightSource_attenuation.z;

            attenuationi = 1. / max(c1 + c2 * dL + c3 * (dL * dL), 1.);

            if(length(u_LightSource_direction) != 0.) {
              vec3 spotDiri = normalize(u_LightSource_direction);
              float spotAngle = acos(max(dot(-L, spotDiri), 0.));

              float spotBW = u_LightSource_beamWidth;
              float spotCO = u_LightSource_cutOffAngle;

              if(spotAngle >= spotCO) {
                spoti = 0.;
              } else if(spotAngle <= spotBW) {
                spoti = 1.;
              } else if((spotBW < spotAngle) && (spotAngle < spotCO)) {
                spoti = (spotAngle - spotCO ) / (spotBW - spotCO);
              }
            }
          }
        }

        vec3 ILrgb = u_LightSource_color.rgb;
        float Ii = u_LightSource_intensity;
        float Iia = u_LightSource_ambientIntensity;

        vec3 ambienti = Iia * ODrgb * Oa;
        vec3 diffusei = Ii * ODrgb * dot( N, L );
        vec3 speculari = Ii * OSrgb * pow(dot( N , ((L + V) / normalize(L + V))), shininess * 128.);
      
        sumLights += (attenuationi * spoti * ILrgb * (ambienti + diffusei + speculari));
      }

      vec3 Irgb = IFrgb * (1. -f0) + f0 * (OErgb + sumLights);
      float A = texRgba.a;

      gl_FragColor = vec4(vec3(Irgb), A);
    }
    
    )";
}

} // namespace molphene
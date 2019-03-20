#include "color_light_shader.hpp"

namespace molphene {

void color_light_shader::setup_gl_attribs_val() const noexcept
{
  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::vertex), 0, 0, 0, 1);

  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::transformation) + 0, 1, 0, 0, 0);

  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::transformation) + 1, 0, 1, 0, 0);

  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::transformation) + 2, 0, 0, 1, 0);

  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::transformation) + 3, 0, 0, 0, 1);
}

auto color_light_shader::vert_shader_source() const noexcept -> const GLchar*
{
  return R"(
    attribute vec4 a_Vertex;
    attribute vec3 a_Normal;
    attribute vec2 a_TexCoord0;
    attribute vec4 a_Transformation;
    attribute vec4 a_Transformation1;
    attribute vec4 a_Transformation2;
    attribute vec4 a_Transformation3;
    
    uniform mat4 u_ModelViewMatrix;
    uniform mat3 u_NormalMatrix;
    uniform mat4 u_ProjectionMatrix;
    
    varying vec3 v_Position;
    varying vec3 v_Normal;
    varying vec2 v_ColorTexCoord;
    void main() {
        mat4 transformMatrix = mat4(
          a_Transformation,
          a_Transformation1,
          a_Transformation2,
          a_Transformation3
        );
        vec4 position = u_ModelViewMatrix * transformMatrix * a_Vertex;
        v_Position = position.xyz / position.w;
        v_ColorTexCoord = a_TexCoord0;
        v_Normal = length(a_Normal) != 0.0 ? u_NormalMatrix * a_Normal : a_Normal;
        gl_Position = u_ProjectionMatrix * position;
        gl_Position /= gl_Position.w;
    }
    )";
}

auto color_light_shader::frag_shader_source() const noexcept -> const GLchar*
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

    uniform sampler2D u_TexColorImage;
    
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
      vec4 texRgba = texture2D(u_TexColorImage, v_ColorTexCoord.st);
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
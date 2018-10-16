#ifndef MOLPHENE_COLOR_LIGHT_SHADER_HPP
#define MOLPHENE_COLOR_LIGHT_SHADER_HPP

#include "stdafx.hpp"

#include "BasicShader.hpp"
#include "DirectionalLight.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include "ShaderAttribLocation.hpp"

#include "MixShaderUniforms.hpp"

namespace molphene {
  
class ColorLightShader
: public BasicShader<
    ColorLightShader,
    MixShaderUniforms<
      ColorLightShader,
      ModelViewMatrixUniform,
      NormalMatrixUniform,
      ProjectionMatrixUniform,
      LightSourceUniform,
      MaterialUniform,
      FogUniform,
      Color2dSamplerUniform
    >
  >
{
public:
  using AttribsLocationName =
   std::array<std::pair<ShaderAttribLocation, const GLchar*>, 3>;

  ColorLightShader() noexcept;

protected:

  const char*
  vert_shader_source() const noexcept;

  const char*
  frag_shader_source() const noexcept;

  AttribsLocationName
  get_attribs_location() const noexcept;

  void
  setup_gl_attribs_val() const noexcept;
};
} // namespace molphene
#endif

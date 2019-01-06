#ifndef MOLPHENE_COLOR_LIGHT_SHADER_HPP
#define MOLPHENE_COLOR_LIGHT_SHADER_HPP

#include "stdafx.hpp"

#include "BasicShader.hpp"
#include "DirectionalLight.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "MixShaderUniforms.hpp"
#include "PointLight.hpp"
#include "ShaderAttribLocation.hpp"
#include "SpotLight.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

class ColorLightShader
: public BasicShader<ColorLightShader,
                     MixShaderUniforms<ColorLightShader,
                                       ModelViewMatrixUniform,
                                       NormalMatrixUniform,
                                       ProjectionMatrixUniform,
                                       LightSourceUniform,
                                       MaterialUniform,
                                       FogUniform,
                                       Color2dSamplerUniform>> {
public:
  using AttribLocations = ShaderAttribList<ShaderAttribLocation::vertex,
                                           ShaderAttribLocation::normal,
                                           ShaderAttribLocation::texcoordcolor>;

protected:
  auto vert_shader_source() const noexcept -> const GLchar*;

  auto frag_shader_source() const noexcept -> const GLchar*;

  void setup_gl_attribs_val() const noexcept;
};
} // namespace molphene
#endif

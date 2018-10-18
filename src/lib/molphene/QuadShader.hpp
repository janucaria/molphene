#ifndef MOLPHENE_QUAD_SHADER_HPP
#define MOLPHENE_QUAD_SHADER_HPP

#include "stdafx.hpp"

#include "BasicShader.hpp"
#include "MixShaderUniforms.hpp"
#include "ShaderAttribLocation.hpp"
#include "opengl.hpp"

namespace molphene {
class QuadShader
: public BasicShader<QuadShader,
                     MixShaderUniforms<QuadShader, Color2dSamplerUniform>> {
public:
  using AttribLocations = ShaderAttribList<ShaderAttribLocation::vertex>;

protected:
  const GLchar*
  vert_shader_source() const noexcept;

  const GLchar*
  frag_shader_source() const noexcept;

  void
  setup_gl_attribs_val() const noexcept;
};
} // namespace molphene
#endif

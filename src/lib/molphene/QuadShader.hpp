#ifndef MOLPHENE_QUAD_SHADER_HPP
#define MOLPHENE_QUAD_SHADER_HPP

#include "stdafx.hpp"

#include "BasicShader.hpp"
#include "opengl.hpp"
#include "ShaderAttribLocation.hpp"
#include "MixShaderUniforms.hpp"

namespace molphene {
class QuadShader
: public BasicShader<
    QuadShader,
    MixShaderUniforms<QuadShader, Color2dSamplerUniform>
  >
{
public:
  using AttribsLocationName =
   std::array<std::pair<ShaderAttribLocation, const GLchar*>, 1>;

  QuadShader() noexcept = default;

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

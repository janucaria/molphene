#ifndef MOLPHENE_QUAD_SHADER_HPP
#define MOLPHENE_QUAD_SHADER_HPP

#include "stdafx.hpp"

#include "basic_shader.hpp"
#include "mix_shader_uniforms.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {
class quad_shader
: public basic_shader<
   quad_shader,
   mix_shader_uniforms<quad_shader, color2d_sampler_uniform>> {
public:
  using attrib_locations = shader_attrib_list<shader_attrib_location::vertex>;

protected:
  auto vert_shader_source() const noexcept -> const GLchar*;

  auto frag_shader_source() const noexcept -> const GLchar*;

  void setup_gl_attribs_val() const noexcept;
};
} // namespace molphene
#endif

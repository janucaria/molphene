#ifndef MOLPHENE_COLOR_LIGHT_SHADER_HPP
#define MOLPHENE_COLOR_LIGHT_SHADER_HPP

#include "stdafx.hpp"

#include "basic_shader.hpp"
#include "directional_light.hpp"
#include "fog.hpp"
#include "m3d.hpp"
#include "material.hpp"
#include "mix_shader_uniforms.hpp"
#include "opengl.hpp"
#include "point_light.hpp"
#include "shader_attrib_location.hpp"
#include "spot_light.hpp"

namespace molphene {

class color_light_shader
: public basic_shader<color_light_shader,
                      mix_shader_uniforms<color_light_shader,
                                          model_view_matrix_uniform,
                                          normal_matrix_uniform,
                                          projection_matrix_uniform,
                                          light_source_uniform,
                                          material_uniform,
                                          fog_uniform,
                                          color2d_sampler_uniform>> {
public:
  using attrib_locations =
   shader_attrib_list<shader_attrib_location::vertex,
                      shader_attrib_location::normal,
                      shader_attrib_location::texcoordcolor>;

protected:
  auto vert_shader_source() const noexcept -> const GLchar*;

  auto frag_shader_source() const noexcept -> const GLchar*;

  void setup_gl_attribs_val() const noexcept;
};
} // namespace molphene
#endif

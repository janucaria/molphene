#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "ballstick_representation.hpp"
#include "camera.hpp"
#include "color_light_shader.hpp"
#include "quad_shader.hpp"
#include "scene.hpp"
#include "spacefill_representation.hpp"
#include "vertex_attribs_buffer.hpp"
#include "viewport.hpp"
#include "m3d.hpp"

namespace molphene {

class gl_renderer {
public:
  using camera = typename scene::camera;

  using vec2f = vec2<GLfloat>;

  using vertex_attribs_buffer =
   vertex_attribs_buffer<vec2f, shader_attrib_location::vertex>;

  using viewport_type = viewport<std::size_t>;

  void init() noexcept;

  void render(const scene& scene, const camera& camera) noexcept;

  void change_dimension(std::size_t width, std::size_t height) noexcept;

private:
  GLuint color_light_fbo_{0};

  GLuint color_light_depth_rbo_{0};

  GLuint color_light_color_tex_{0};

  std::unique_ptr<vertex_attribs_buffer> quad_verts_buffer_;

  color_light_shader color_light_shader_;

  quad_shader quad_shader_;

  viewport_type viewport_;

  void
  render_representation_(const spacefill_representation& representation) const;

  void
  render_representation_(const ballstick_representation& representation) const;
};

} // namespace molphene

#endif
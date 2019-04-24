#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "color_light_shader.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "m3d.hpp"
#include "quad_shader.hpp"
#include "scene.hpp"
#include "vertex_attribs_buffer.hpp"
#include "viewport.hpp"

namespace molphene {

class gl_renderer {
public:
  using vec2f = vec2<GLfloat>;

  using vertex_attribs_buffer =
   vertex_attribs_buffer<vec2f, shader_attrib_location::vertex>;

  using viewport_type = viewport<std::size_t>;

  void init() noexcept;

  template<typename TDrawableRange, typename TCamera>
  void render(const scene& scene,
              const TCamera& camera,
              const TDrawableRange& drawables) noexcept
  {
    using mat3f = typename scene::mat3f;
    using mat4f = typename scene::mat4f;

    constexpr auto color_buff_bit = static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT);
    constexpr auto depth_buff_bit = static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT);

    const auto mv_matrix = scene.model_matrix() * camera.view_matrix();
    const auto norm_matrix = mat3f{mat4f{mv_matrix}.inverse().transpose()};
    const auto proj_matrix = camera.projection_matrix();

    glBindFramebuffer(GL_FRAMEBUFFER, color_light_fbo_);
    glViewport(viewport_.x, viewport_.y, viewport_.width, viewport_.height);
    glClear(color_buff_bit | depth_buff_bit);

    {
      color_light_shader_.use_program();
      color_light_shader_.projection_matrix(proj_matrix);
      color_light_shader_.modelview_matrix(mv_matrix);
      color_light_shader_.normal_matrix(norm_matrix);
      std::visit(
       [this](auto&& val) {
         color_light_shader_.light_source(std::forward<decltype(val)>(val));
       },
       scene.light_source());
      color_light_shader_.fog(scene.fog());
      color_light_shader_.material(scene.material());

      for(auto&& drawable_v : drawables) {
        drawable_v.render(color_light_shader_);
      }
    }

    glFlush();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(viewport_.x, viewport_.y, viewport_.width, viewport_.height);
    glClear(color_buff_bit | depth_buff_bit);

    {
      const auto verts_guard =
       gl_vertex_attribs_guard<shader_attrib_location::vertex>{};

      quad_shader_.use_program();
      quad_shader_.color_texture_image(color_light_color_tex_);

      quad_verts_buffer_->attrib_pointer();

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    glFlush();
  }

  void change_dimension(std::size_t width, std::size_t height) noexcept;

private:
  GLuint color_light_fbo_{0};

  GLuint color_light_depth_rbo_{0};

  GLuint color_light_color_tex_{0};

  std::unique_ptr<vertex_attribs_buffer> quad_verts_buffer_;

  color_light_shader color_light_shader_;

  quad_shader quad_shader_;

  viewport_type viewport_;
};

} // namespace molphene

#endif
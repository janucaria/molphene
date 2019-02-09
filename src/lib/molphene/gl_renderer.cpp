#include "gl_renderer.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "molecule_display.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {

void gl_renderer::init() noexcept
{
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);

  color_light_shader_.init_program();
  quad_shader_.init_program();

  glGenFramebuffers(1, &color_light_fbo_);

  glGenTextures(1, &color_light_color_tex_);
  glBindTexture(GL_TEXTURE_2D, color_light_color_tex_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glGenRenderbuffers(1, &color_light_depth_rbo_);

  glBindFramebuffer(GL_FRAMEBUFFER, color_light_fbo_);
  glBindTexture(GL_TEXTURE_2D, color_light_color_tex_);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0 + 0,
                         GL_TEXTURE_2D,
                         color_light_color_tex_,
                         0);

  glBindFramebuffer(GL_FRAMEBUFFER, color_light_fbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, color_light_depth_rbo_);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                            GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER,
                            color_light_depth_rbo_);

  quad_verts_buffer_ =
   std::make_unique<decltype(quad_verts_buffer_)::element_type>();
  quad_verts_buffer_->init(std::array<vec2f, 4>{
   vec2f{-1, 1}, vec2f{-1, -1}, vec2f{1, 1}, vec2f{1, -1}});
}

void gl_renderer::render(const scene& scene,
                        const gl_renderer::camera& camera) noexcept
{
  using mat3f = typename scene::mat3f;
  using mat4f = typename scene::mat4f;

  const auto mv_matrix = scene.model_matrix() * camera.view_matrix();
  const auto norm_matrix = mat3f{mat4f{mv_matrix}.inverse().transpose()};
  const auto proj_matrix = camera.projection_matrix();

  glBindFramebuffer(GL_FRAMEBUFFER, color_light_fbo_);
  glViewport(viewport_.x, viewport_.y, viewport_.width, viewport_.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  {
    const auto verts_guard =
     gl_vertex_attribs_guard<shader_attrib_location::vertex,
                          shader_attrib_location::normal,
                          shader_attrib_location::texcoordcolor>{};

    color_light_shader_.use_program();
    color_light_shader_.projection_matrix(proj_matrix);
    color_light_shader_.modelview_matrix(mv_matrix);
    color_light_shader_.normal_matrix(norm_matrix);
    color_light_shader_.light_source(scene.light_source());
    color_light_shader_.fog(scene.fog());
    color_light_shader_.material(scene.material());

    for(auto&& representation_var : scene.representations()) {
      std::visit(
       [this](const auto& representation) {
         render_representation_(representation);
       },
       representation_var);
    }
  }

  glFlush();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(viewport_.x, viewport_.y, viewport_.width, viewport_.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void gl_renderer::render_representation_(
 const spacefill_representation& representation) const
{
  const auto mbuffers = representation.atom_sphere_buffer.get();
  color_light_shader_.color_texture_image(mbuffers->color_texture_image());
  mbuffers->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
}

void gl_renderer::render_representation_(
 const ballstick_representation& representation) const
{
  {
    const auto mbuffers = representation.bond1_cylinder_buffer.get();
    color_light_shader_.color_texture_image(mbuffers->color_texture_image());
    mbuffers->setup_attrib_pointer(
     [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
  }

  {
    const auto mbuffers = representation.bond2_cylinder_buffer.get();
    color_light_shader_.color_texture_image(mbuffers->color_texture_image());
    mbuffers->setup_attrib_pointer(
     [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
  }

  {
    const auto mbuffers = representation.atom_sphere_buffer.get();
    color_light_shader_.color_texture_image(mbuffers->color_texture_image());
    mbuffers->setup_attrib_pointer(
     [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
  }
}

void gl_renderer::change_dimension(std::size_t width,
                                  std::size_t height) noexcept
{
  viewport_.width = width;
  viewport_.height = height;

  glBindTexture(GL_TEXTURE_2D, color_light_color_tex_);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               viewport_.width,
               viewport_.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);

  glBindRenderbuffer(GL_RENDERBUFFER, color_light_depth_rbo_);
  glRenderbufferStorage(
   GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, viewport_.width, viewport_.height);
}

} // namespace molphene

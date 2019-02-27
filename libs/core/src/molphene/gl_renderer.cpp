#include "gl_renderer.hpp"
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

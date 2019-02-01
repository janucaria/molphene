#include "GlRenderer.hpp"
#include "GlVertexAttribsGuard.hpp"
#include "MoleculeRepresentation.hpp"
#include "ShaderAttribLocation.hpp"

namespace molphene {

void GlRenderer::init() noexcept
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
  quad_verts_buffer_->init(std::array<Vec2f, 4>{
   Vec2f{-1, 1}, Vec2f{-1, -1}, Vec2f{1, 1}, Vec2f{1, -1}});
}

void GlRenderer::render(const Scene& scene,
                        const GlRenderer::Camera& camera) noexcept
{
  using Mat3f = typename Scene::Mat3f;
  using Mat4f = typename Scene::Mat4f;

  const auto mv_matrix = scene.model_matrix() * camera.view_matrix();
  const auto norm_matrix = Mat3f{Mat4f{mv_matrix}.inverse().transpose()};
  const auto proj_matrix = camera.projection_matrix();
  const auto viewport = scene.viewport();

  glBindTexture(GL_TEXTURE_2D, color_light_color_tex_);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               viewport.width,
               viewport.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);

  glBindRenderbuffer(GL_RENDERBUFFER, color_light_depth_rbo_);
  glRenderbufferStorage(
   GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, viewport.width, viewport.height);

  glBindFramebuffer(GL_FRAMEBUFFER, color_light_fbo_);
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  {
    const auto verts_guard =
     GlVertexAttribsGuard<ShaderAttribLocation::vertex,
                          ShaderAttribLocation::normal,
                          ShaderAttribLocation::texcoordcolor>{};

    color_light_shader_.use_program();
    color_light_shader_.projection_matrix(proj_matrix);
    color_light_shader_.modelview_matrix(mv_matrix);
    color_light_shader_.normal_matrix(norm_matrix);
    color_light_shader_.light_source(scene.light_source());
    color_light_shader_.fog(scene.fog());
    color_light_shader_.material(scene.material());

    switch(scene.representation) {
    case MoleculeRepresentation::spacefill: {
      const auto mbuffers = scene.mesh_buffers();
      color_light_shader_.color_texture_image(mbuffers->color_texture_image());
      mbuffers->setup_attrib_pointer(
       [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
    } break;
    default: {
      auto mbuffers = scene.cyl_bond1_mesh_buffers();
      color_light_shader_.color_texture_image(mbuffers->color_texture_image());
      mbuffers->setup_attrib_pointer(
       [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

      mbuffers = scene.cyl_bond2_mesh_buffers();
      color_light_shader_.color_texture_image(mbuffers->color_texture_image());
      mbuffers->setup_attrib_pointer(
       [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

      mbuffers = scene.ballnstick_sphere_atom_buffers();
      color_light_shader_.color_texture_image(mbuffers->color_texture_image());
      mbuffers->setup_attrib_pointer(
       [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
    } break;
    }
  }

  glFlush();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  {
    const auto verts_guard =
     GlVertexAttribsGuard<ShaderAttribLocation::vertex>{};

    quad_shader_.use_program();
    quad_shader_.color_texture_image(color_light_color_tex_);

    quad_verts_buffer_->attrib_pointer();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
  glFlush();
}

} // namespace molphene

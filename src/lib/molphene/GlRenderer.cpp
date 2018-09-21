#include "GlRenderer.hpp"
#include "ShaderAttribLocation.hpp"

namespace molphene {

void
GlRenderer::init() noexcept
{
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);

  color_light_shader_.init_program();
}

void
GlRenderer::render(const Scene& scene,
                   const GlRenderer::Camera& camera) noexcept
{
  using Mat3f = typename Scene::Mat3f;
  using Mat4f = typename Scene::Mat4f;

  const auto* mbuffers = scene.mesh_buffers();

  const auto mv_matrix = scene.model_matrix() * camera.view_matrix;
  const auto norm_matrix = Mat3f{Mat4f{mv_matrix}.inverse().transpose()};
  const auto proj_matrix = camera.projection_matrix();

  glViewport(0, 0, camera.width, camera.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  color_light_shader_.use_program();
  color_light_shader_.projection_matrix(proj_matrix);
  color_light_shader_.modelview_matrix(mv_matrix);
  color_light_shader_.normal_matrix(norm_matrix);
  color_light_shader_.color_texture_image(mbuffers->color_texture_image());
  color_light_shader_.light_source(scene.light_source());
  color_light_shader_.fog(scene.fog());
  color_light_shader_.material(scene.material());

  glEnableVertexAttribArray(static_cast<GLuint>(ShaderAttribLocation::vertex));
  glEnableVertexAttribArray(static_cast<GLuint>(ShaderAttribLocation::normal));
  glEnableVertexAttribArray(
   static_cast<GLuint>(ShaderAttribLocation::texcoordcolor));

  mbuffers->setup_attrib_pointer(
   [](auto count) { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

  glEnableVertexAttribArray(static_cast<GLuint>(ShaderAttribLocation::vertex));
  glEnableVertexAttribArray(static_cast<GLuint>(ShaderAttribLocation::normal));
  glEnableVertexAttribArray(
   static_cast<GLuint>(ShaderAttribLocation::texcoordcolor));

  glFlush();
}

} // namespace molphene

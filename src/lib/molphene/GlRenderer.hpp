#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "ColorLightShader.hpp"
#include "m3d.hpp"

namespace molphene {

class GlRenderer {
public:
  void
  init() noexcept;

  template<typename TScene, typename TCamera>
  void
  render(const TScene& scene, TCamera&& camera) noexcept
  {
    using Mat3f = typename TScene::Mat3f;
    using Mat4f = typename TScene::Mat4f;

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

    // TODO(janucaria): fix mesh buffers rendering
    auto&& size_ = mbuffers->size_;
    auto&& remain_instances_ = mbuffers->remain_instances_;
    auto&& instances_per_block_ = mbuffers->instances_per_block_;
    auto&& vert_buffers_ = mbuffers->vert_buffers_;
    auto&& normal_buffers_ = mbuffers->normal_buffers_;
    auto&& texcoord_buffers_ = mbuffers->texcoord_buffers_;
    auto&& verts_per_instance_ = mbuffers->verts_per_instance_;

    glEnableVertexAttribArray(ColorLightShader::AttribLocation::vertex);
    glEnableVertexAttribArray(ColorLightShader::AttribLocation::normal);
    glEnableVertexAttribArray(ColorLightShader::AttribLocation::texcoord0);
    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto verts_count =
       GLsizei{i == (size_ - 1) ? remain_instances_ : instances_per_block_};

      glBindBuffer(GL_ARRAY_BUFFER, vert_buffers_[i]);
      glVertexAttribPointer(ColorLightShader::AttribLocation::vertex,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            nullptr);

      glBindBuffer(GL_ARRAY_BUFFER, normal_buffers_[i]);
      glVertexAttribPointer(ColorLightShader::AttribLocation::normal,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            nullptr);

      glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffers_[i]);
      glVertexAttribPointer(ColorLightShader::AttribLocation::texcoord0,
                            2,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            nullptr);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, verts_count * verts_per_instance_);
    }
    glEnableVertexAttribArray(ColorLightShader::AttribLocation::vertex);
    glEnableVertexAttribArray(ColorLightShader::AttribLocation::normal);
    glEnableVertexAttribArray(ColorLightShader::AttribLocation::texcoord0);

    glFlush();
  }

private:
  ColorLightShader color_light_shader_;
};

} // namespace molphene

#endif
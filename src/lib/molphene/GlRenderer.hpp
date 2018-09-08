#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "ColorLightShader.hpp"

namespace molphene {

template<typename = void>
class GlRenderer {
public:
  template<typename TScene, typename TCamera>
  void
  render(const TScene& scene, TCamera&& camera)
  {
    using Mat3f = typename TScene::Mat3f;
    using Mat4f = typename TScene::Mat4f;

    auto& model_matrix_ = scene.model_matrix_;
    auto& color_light_shader_ = scene.color_light_shader_;
    auto& atom_color_tex_ = scene.atom_color_tex_;
    auto& sphere_buff_atoms_ = scene.sphere_buff_atoms_;

    const auto mv_matrix = model_matrix_ * camera.view_matrix;
    const auto norm_matrix = Mat3f{Mat4f{mv_matrix}.inverse().transpose()};
    const auto proj_matrix = camera.projection_matrix();
    glViewport(0, 0, camera.width, camera.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    color_light_shader_.use_program();
    color_light_shader_.projection_matrix(proj_matrix);
    color_light_shader_.modelview_matrix(mv_matrix);
    color_light_shader_.normal_matrix(norm_matrix);
    color_light_shader_.color_texture_image(atom_color_tex_);

    auto&& size_ = sphere_buff_atoms_->size_;
    auto&& remain_instances_ = sphere_buff_atoms_->remain_instances_;
    auto&& instances_per_block_ = sphere_buff_atoms_->instances_per_block_;
    auto&& vert_buffers_ = sphere_buff_atoms_->vert_buffers_;
    auto&& normal_buffers_ = sphere_buff_atoms_->normal_buffers_;
    auto&& texcoord_buffers_ = sphere_buff_atoms_->texcoord_buffers_;
    auto&& verts_per_instance_ = sphere_buff_atoms_->verts_per_instance_;

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
};

} // namespace molphene

#endif
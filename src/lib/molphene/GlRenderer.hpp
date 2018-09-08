#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

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
    sphere_buff_atoms_->draw();
    glFlush();
  }

private:
};

} // namespace

#endif
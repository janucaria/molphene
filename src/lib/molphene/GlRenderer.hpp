#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "ColorLightShader.hpp"
#include "QuadShader.hpp"
#include "m3d.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "VertexAttribsBuffer.hpp"

namespace molphene {

class GlRenderer {
public:
  using Camera = typename Scene::Camera;

  using Vec2f = Vec2<GLfloat>;

  using VertexAttribsBuffer = VertexAttribsBuffer<Vec2f, ShaderAttribLocation::vertex>;

  void
  init() noexcept;

  void
  render(const Scene& scene, const Camera& camera) noexcept;

private:
  GLuint color_light_fbo_;  

  GLuint color_light_depth_rbo_;

  GLuint color_light_color_tex_;

  std::unique_ptr<VertexAttribsBuffer> quad_verts_buffer_;

  ColorLightShader color_light_shader_;
  
  QuadShader quad_shader_;
};

} // namespace molphene

#endif
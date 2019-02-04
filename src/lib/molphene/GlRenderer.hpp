#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "BallStickRepresentation.hpp"
#include "Camera.hpp"
#include "ColorLightShader.hpp"
#include "QuadShader.hpp"
#include "Scene.hpp"
#include "SpacefillRepresentation.hpp"
#include "VertexAttribsBuffer.hpp"
#include "m3d.hpp"

namespace molphene {

class GlRenderer {
public:
  using Camera = typename Scene::Camera;

  using Vec2f = Vec2<GLfloat>;

  using VertexAttribsBuffer =
   VertexAttribsBuffer<Vec2f, ShaderAttribLocation::vertex>;

  void init() noexcept;

  void render(const Scene& scene, const Camera& camera) noexcept;

private:
  GLuint color_light_fbo_{0};

  GLuint color_light_depth_rbo_{0};

  GLuint color_light_color_tex_{0};

  std::unique_ptr<VertexAttribsBuffer> quad_verts_buffer_;

  ColorLightShader color_light_shader_;

  QuadShader quad_shader_;

  void
  render_representation_(const SpacefillRepresentation& representation) const;

  void
  render_representation_(const BallStickRepresentation& representation) const;
};

} // namespace molphene

#endif
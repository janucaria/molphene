#ifndef MOLPHENE_GL_RENDERER_HPP
#define MOLPHENE_GL_RENDERER_HPP

#include "stdafx.hpp"

#include "ColorLightShader.hpp"
#include "m3d.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

namespace molphene {

class GlRenderer {
public:
  using Camera = typename Scene::Camera;

  void
  init() noexcept;

  void
  render(const Scene& scene, const Camera& camera) noexcept;

private:
  ColorLightShader color_light_shader_;
};

} // namespace molphene

#endif
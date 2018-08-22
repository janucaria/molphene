#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "stdafx.hpp"

#include "SphereMeshBuilder.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

class ColorLightBuffer {
public:
  ColorLightBuffer(GLsizei verts_per_instance, GLsizeiptr total_instances);

  ~ColorLightBuffer();

  ColorLightBuffer(const ColorLightBuffer&) = delete;

  ColorLightBuffer(ColorLightBuffer&&) = delete;

  ColorLightBuffer&
  operator=(const ColorLightBuffer&) = delete;

  ColorLightBuffer&
  operator=(ColorLightBuffer&&) = delete;

  void
  set_data(GLintptr offset,
           GLsizeiptr size,
           gsl::span<const Vec3f> verts,
           gsl::span<const Vec3f> norms,
           gsl::span<const Vec2f> texcoords);

  void
  draw();

private:
  GLsizei verts_per_instance_{0};
  GLsizei instances_per_block_{0};
  GLsizei remain_instances_{0};

  GLsizei size_;

  std::vector<GLuint> vert_buffers_;
  std::vector<GLuint> normal_buffers_;
  std::vector<GLuint> texcoord_buffers_;
};
} // namespace molphene

#endif

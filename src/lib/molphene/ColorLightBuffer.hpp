#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "stdafx.hpp"

#include "ShaderAttribLocation.hpp"
#include "SphereMeshBuilder.hpp"
#include "VertexAttribsBuffer.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

class GlRenderer;

class ColorLightBuffer {
public:
  using Vec2f = Vec2<GLfloat>;
  using Vec3f = Vec3<GLfloat>;

  using PositionAttribsBuffers =
   std::vector<VertexAttribsBuffer<Vec3f, ShaderAttribLocation::vertex>>;
  using NormalAttribsBuffers =
   std::vector<VertexAttribsBuffer<Vec3f, ShaderAttribLocation::normal>>;
  using ColorAttribsBuffers =
   std::vector<VertexAttribsBuffer<Vec2f, ShaderAttribLocation::texcoordcolor>>;

  friend GlRenderer;

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
  color_texture_image_data(const GLvoid* data) const noexcept;

  GLsizei
  color_texture_size() const noexcept;

  GLuint
  color_texture_image() const noexcept;

private:
  GLsizei verts_per_instance_{0};
  GLsizei instances_per_block_{0};
  GLsizei remain_instances_{0};

  GLsizei size_;

  GLuint color_tex_{0};
  GLsizei color_tex_size_{0};

  PositionAttribsBuffers vert_buffers_;
  NormalAttribsBuffers normal_buffers_;
  ColorAttribsBuffers texcoord_buffers_;
};
} // namespace molphene

#endif

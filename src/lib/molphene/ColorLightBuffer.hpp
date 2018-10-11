#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "stdafx.hpp"

#include "ShaderAttribLocation.hpp"
#include "SphereMeshBuilder.hpp"
#include "VertexAttribsBuffer.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

class ColorLightBuffer {
public:
  using Vec2f = Vec2<GLfloat>;
  using Vec3f = Vec3<GLfloat>;

  using PositionAttribsBuffers =
   std::unique_ptr<VertexAttribsBuffer<Vec3f, ShaderAttribLocation::vertex>[]>;
  using NormalAttribsBuffers =
   std::unique_ptr<VertexAttribsBuffer<Vec3f, ShaderAttribLocation::normal>[]>;
  using ColorAttribsBuffers =
   std::unique_ptr<VertexAttribsBuffer<Vec2f, ShaderAttribLocation::texcoordcolor>[]>;

  ColorLightBuffer(GLsizei verts_per_instance, GLsizeiptr total_instances) noexcept;

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
           gsl::span<const Vec2f> texcoords) const noexcept;

  void
  color_texture_image_data(const GLvoid* data) const noexcept;

  GLsizei
  color_texture_size() const noexcept;

  GLuint
  color_texture_image() const noexcept;

  template<typename TCallback>
  void
  setup_attrib_pointer(TCallback fn) const
   noexcept(std::is_nothrow_invocable_v<decltype(fn), GLsizei>)
  {
    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto verts_count =
       GLsizei{i == (size_ - 1) ? remain_instances_ : instances_per_block_};

      vert_buffers_[i].attrib_pointer();
      normal_buffers_[i].attrib_pointer();
      texcoord_buffers_[i].attrib_pointer();

      fn(verts_count * verts_per_instance_);
    }
  }

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

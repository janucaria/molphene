#include "ColorLightBuffer.hpp"
#include "ColorLightShader.hpp"
#include "opengl.hpp"

namespace molphene {

ColorLightBuffer::ColorLightBuffer(GLsizei verts_per_instance,
                                   GLsizeiptr total_instances)
: verts_per_instance_{verts_per_instance}
{
  const auto bytes_per_vert = GLsizeiptr{sizeof(Vec3f) * 2 + sizeof(Vec2f)};
  const auto bytes_per_mesh = GLsizeiptr{verts_per_instance_ * bytes_per_vert};
  const auto max_bytes_per_chunk = GLsizeiptr{1024 * 1024 * 512};

  instances_per_block_ = GLsizei(max_bytes_per_chunk / bytes_per_mesh);
  size_ = GLsizei(total_instances / instances_per_block_);
  remain_instances_ = total_instances % instances_per_block_;

  if(remain_instances_ == 0) {
    remain_instances_ = instances_per_block_;
  } else {
    ++size_;
  }

  vert_buffers_.reserve(size_);
  glGenBuffers(size_, vert_buffers_.data());

  normal_buffers_.reserve(size_);
  glGenBuffers(size_, normal_buffers_.data());

  texcoord_buffers_.reserve(size_);
  glGenBuffers(size_, texcoord_buffers_.data());

  for(auto i = GLsizei{0}; i < size_; ++i) {
    const GLsizeiptr meshes =
     i == (size_ - 1) ? remain_instances_ : instances_per_block_;
    const GLsizeiptr verts = meshes * verts_per_instance_;

    glBindBuffer(GL_ARRAY_BUFFER, vert_buffers_[i]);
    glBufferData(
     GL_ARRAY_BUFFER, verts * sizeof(Vec3f), nullptr, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffers_[i]);
    glBufferData(
     GL_ARRAY_BUFFER, verts * sizeof(Vec3f), nullptr, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffers_[i]);
    glBufferData(
     GL_ARRAY_BUFFER, verts * sizeof(Vec2f), nullptr, GL_STATIC_DRAW);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ColorLightBuffer::~ColorLightBuffer()
{
  glDeleteBuffers(size_, vert_buffers_.data());
  glDeleteBuffers(size_, normal_buffers_.data());
  glDeleteBuffers(size_, texcoord_buffers_.data());

  size_ = verts_per_instance_ = remain_instances_ = 0;
}

void
ColorLightBuffer::set_data(GLintptr offset,
                           GLsizeiptr size,
                           gsl::span<const Vec3f> verts,
                           gsl::span<const Vec3f> norms,
                           gsl::span<const Vec2f> texcoords)
{
  auto data_offset = GLsizeiptr{0};
  while(size > 0) {
    const auto chunk = GLsizeiptr{offset / instances_per_block_};
    const auto index = GLsizeiptr{offset % instances_per_block_};

    const auto elems_fill = GLsizeiptr{instances_per_block_ - index};
    const auto fill_size = GLsizeiptr{size < elems_fill ? size : elems_fill};

    glBindBuffer(GL_ARRAY_BUFFER, vert_buffers_[chunk]);
    glBufferSubData(GL_ARRAY_BUFFER,
                    index * verts_per_instance_ *
                     sizeof(std::remove_pointer_t<decltype(verts)::value_type>),
                    fill_size * verts_per_instance_ *
                     sizeof(std::remove_pointer_t<decltype(verts)::value_type>),
                    verts.first(data_offset * verts_per_instance_).data());

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffers_[chunk]);
    glBufferSubData(GL_ARRAY_BUFFER,
                    index * verts_per_instance_ *
                     sizeof(std::remove_pointer_t<decltype(norms)::value_type>),
                    fill_size * verts_per_instance_ *
                     sizeof(std::remove_pointer_t<decltype(norms)::value_type>),
                    norms.first(data_offset * verts_per_instance_).data());

    glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffers_[chunk]);
    glBufferSubData(
     GL_ARRAY_BUFFER,
     index * verts_per_instance_ *
      sizeof(std::remove_pointer_t<decltype(texcoords)::value_type>),
     fill_size * verts_per_instance_ *
      sizeof(std::remove_pointer_t<decltype(texcoords)::value_type>),
     texcoords.first(data_offset * verts_per_instance_).data());

    size -= fill_size;
    offset += fill_size;
    data_offset += fill_size;
  }
}

} // namespace molphene

#include "ColorLightBuffer.hpp"
#include "ColorLightShader.hpp"
#include "opengl.hpp"

namespace molphene {

ColorLightBuffer::ColorLightBuffer(GLsizei verts_per_instance,
                                   GLsizeiptr total_instances)
: verts_per_instance_{verts_per_instance}
, color_tex_size_(static_cast<GLsizei>(std::ceil(std::sqrt(total_instances))))
{
  glGenTextures(1, &color_tex_);
  glBindTexture(GL_TEXTURE_2D, color_tex_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
  normal_buffers_.reserve(size_);
  texcoord_buffers_.reserve(size_);

  for(auto i = GLsizei{0}; i < size_; ++i) {
    const GLsizeiptr meshes =
     i == (size_ - 1) ? remain_instances_ : instances_per_block_;
    const GLsizeiptr verts = meshes * verts_per_instance_;

    vert_buffers_.emplace_back(verts, GL_STATIC_DRAW);
    normal_buffers_.emplace_back(verts, GL_STATIC_DRAW);
    texcoord_buffers_.emplace_back(verts, GL_STATIC_DRAW);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ColorLightBuffer::~ColorLightBuffer()
{
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

    vert_buffers_[chunk].sub_data(
     index * verts_per_instance_,
     fill_size * verts_per_instance_,
     verts.first(data_offset * verts_per_instance_).data());

    normal_buffers_[chunk].sub_data(
     index * verts_per_instance_,
     fill_size * verts_per_instance_,
     norms.first(data_offset * verts_per_instance_).data());

    texcoord_buffers_[chunk].sub_data(
     index * verts_per_instance_,
     fill_size * verts_per_instance_,
     texcoords.first(data_offset * verts_per_instance_).data());

    size -= fill_size;
    offset += fill_size;
    data_offset += fill_size;
  }
}

void
ColorLightBuffer::color_texture_image_data(const GLvoid* data) const noexcept
{
  glBindTexture(GL_TEXTURE_2D, color_tex_);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               color_tex_size_,
               color_tex_size_,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               data);
}

GLuint
ColorLightBuffer::color_texture_image() const noexcept
{
  return color_tex_;
}

GLsizei
ColorLightBuffer::color_texture_size() const noexcept
{
  return color_tex_size_;
}

} // namespace molphene

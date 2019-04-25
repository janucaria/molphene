#ifndef MOLPHENE_IMAGE_TEXTURE_HPP
#define MOLPHENE_IMAGE_TEXTURE_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"
#include "vertex_attribs_buffer.hpp"

namespace molphene {

template<GLenum VTarget>
class image_taxture {
public:
  static constexpr auto target = VTarget;

  explicit image_taxture(GLsizei total_instances) noexcept
  : size_(static_cast<GLsizei>(std::ceil(std::sqrt(total_instances))))
  {
    glGenTextures(1, &texture_);
    glBindTexture(target, texture_);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  void image_data(const GLvoid* data) const noexcept
  {
    glBindTexture(target, texture_);
    glTexImage2D(
     target, 0, GL_RGBA, size_, size_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }

  auto texture_image() const noexcept -> GLuint
  {
    return texture_;
  }

  auto size() const noexcept -> GLsizei
  {
    return size_;
  }

private:
  GLuint texture_{0};
  GLsizei size_{0};
};

using color_image_texture = image_taxture<GL_TEXTURE_2D>;

} // namespace molphene

#endif

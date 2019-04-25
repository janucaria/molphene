#ifndef MOLPHENE_IMAGE_TEXTURE_HPP
#define MOLPHENE_IMAGE_TEXTURE_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"
#include "vertex_attribs_buffer.hpp"

namespace molphene {

template<GLenum VFormat>
class image_taxture {
public:
  static constexpr auto format = VFormat;
  static constexpr auto type = GL_UNSIGNED_BYTE;
  static constexpr auto target = GL_TEXTURE_2D;

  image_taxture() noexcept
  {
    glGenTextures(1, &texture_);
    glBindTexture(target, texture_);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  image_taxture(const image_taxture&) noexcept = delete;

  auto operator=(const image_taxture&) noexcept -> image_taxture& = delete;

  ~image_taxture() noexcept
  {
    glDeleteTextures(1, &texture_);
  }

  template<typename TView>
  void data(TView&& view) const noexcept
  {
    const auto sqrt = std::sqrt(view.size());
    assert(sqrt == std::floor(sqrt));

    const auto size = static_cast<GLsizei>(sqrt);
    glBindTexture(target, texture_);
    glTexImage2D(target, 0, format, size, size, 0, format, type, view.data());
  }

  auto texture() const noexcept -> GLuint
  {
    return texture_;
  }

private:
  GLuint texture_{0};
};

using color_image_texture = image_taxture<GL_RGBA>;

} // namespace molphene

#endif

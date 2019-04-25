#ifndef MOLPHENE_GL_TEXTURE_IMAGE_2D_HPP
#define MOLPHENE_GL_TEXTURE_IMAGE_2D_HPP

#include "../stdafx.hpp"

#include "../opengl.hpp"

namespace molphene::gl {

template<GLenum VFormat>
class texture_image_2d {
public:
  static constexpr auto format = VFormat;
  static constexpr auto type = GL_UNSIGNED_BYTE;
  static constexpr auto target = GL_TEXTURE_2D;

  texture_image_2d() noexcept
  {
    glGenTextures(1, &texture_);
    glBindTexture(target, texture_);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  texture_image_2d(const texture_image_2d&) noexcept = delete;

  auto operator=(const texture_image_2d&) noexcept
   -> texture_image_2d& = delete;

  ~texture_image_2d() noexcept
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

} // namespace molphene::gl

#endif

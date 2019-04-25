#ifndef MOLPHENE_GL_BUFFER_HPP
#define MOLPHENE_GL_BUFFER_HPP

#include "../opengl.hpp"
#include "../stdafx.hpp"

namespace molphene::gl {

template<typename TData,
         GLenum VTarget = GL_ARRAY_BUFFER,
         GLenum VUsage = GL_STATIC_DRAW>
class buffer {
public:
  using data_type = TData;

  static constexpr auto target = VTarget;
  static constexpr auto usage = VUsage;

  buffer() noexcept
  {
    glGenBuffers(1, &buffer_);
  }

  buffer(const buffer&) = delete;

  auto operator=(const buffer&) -> buffer& = delete;

  ~buffer() noexcept
  {
    glDeleteBuffers(1, &buffer_);
  }

  void bind() const noexcept
  {
    glBindBuffer(target, buffer_);
  }

  void data(gsl::span<const data_type> cont) noexcept
  {
    size_ = cont.size();
    bind();
    glBufferData(target, size_bytes(), cont.data(), usage);
  }

  void reserved(GLsizeiptr size) noexcept
  {
    size_ = size;
    bind();
    glBufferData(target, size_bytes(), nullptr, usage);
  }

  auto size() const noexcept -> GLsizeiptr
  {
    return size_;
  }

  auto size_bytes() const noexcept -> GLsizeiptr
  {
    return size() * sizeof(data_type);
  }

  void subdata(GLintptr offset, gsl::span<const data_type> cont) const noexcept
  {
    bind();
    glBufferSubData(target,
                    offset * sizeof(data_type),
                    cont.size() * sizeof(data_type),
                    cont.data());
  }

private:
  GLuint buffer_{0};
  GLsizeiptr size_{0};
};

} // namespace molphene::gl

#endif

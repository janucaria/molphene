#ifndef MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP
#define MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP

#include "shader_attrib_location.hpp"
#include "opengl.hpp"
#include "stdafx.hpp"

namespace molphene {

template<typename TDataType,
         shader_attrib_location attrib_index,
         GLboolean normalized = GL_FALSE,
         GLenum usage = GL_STATIC_DRAW>
class vertex_attribs_buffer {
public:
  using data_type = TDataType;

  vertex_attribs_buffer() noexcept
  {
    glGenBuffers(1, &buffer_);
  }

  vertex_attribs_buffer(const vertex_attribs_buffer& rsh) = delete;

  vertex_attribs_buffer(vertex_attribs_buffer&& rsh) = delete;

  ~vertex_attribs_buffer() noexcept
  {
    glDeleteBuffers(1, &buffer_);
  }

  auto operator=(const vertex_attribs_buffer& rsh)
   -> vertex_attribs_buffer& = delete;

  auto operator=(vertex_attribs_buffer&& rsh) -> vertex_attribs_buffer& = delete;

  template<
   typename TContainer,
   typename = std::void_t<
    std::enable_if_t<
     std::is_same_v<data_type*, decltype(std::declval<TContainer>().data())>>,
    decltype(std::declval<TContainer>().size())>>
  void init(TContainer&& arr) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferData(
     GL_ARRAY_BUFFER, arr.size() * sizeof(data_type), arr.data(), usage);
  }

  void size(GLsizeiptr size) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(data_type), nullptr, usage);
  }

  void data(GLintptr offset, GLsizeiptr size, const GLvoid* data) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferSubData(
     GL_ARRAY_BUFFER, offset * sizeof(data_type), size * sizeof(data_type), data);
  }

  void attrib_pointer() const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glVertexAttribPointer(static_cast<GLuint>(attrib_index),
                          gl_vertex_attrib<data_type>::size,
                          gl_vertex_attrib<data_type>::type,
                          normalized,
                          0,
                          nullptr);
  }

private:
  GLuint buffer_{0};
};

} // namespace molphene

#endif

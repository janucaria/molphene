#ifndef MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP
#define MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP

#include "ShaderAttribLocation.hpp"
#include "opengl.hpp"
#include "stdafx.hpp"

namespace molphene {

template<class TDataType,
         ShaderAttribLocation attrib_index,
         GLboolean normalized = GL_FALSE,
         GLenum usage = GL_STATIC_DRAW>
class VertexAttribsBuffer {
public:
  using DataType = TDataType;

  VertexAttribsBuffer() noexcept
  {
    glGenBuffers(1, &buffer_);
  }

  VertexAttribsBuffer(const VertexAttribsBuffer& rsh) = delete;

  VertexAttribsBuffer(VertexAttribsBuffer&& rsh) = delete;

  ~VertexAttribsBuffer() noexcept
  {
    glDeleteBuffers(1, &buffer_);
  }

  VertexAttribsBuffer&
  operator=(const VertexAttribsBuffer& rsh) = delete;

  VertexAttribsBuffer&
  operator=(VertexAttribsBuffer&& rsh) = delete;

  template<typename TContainer>
  std::void_t<
   std::enable_if_t<
    std::is_same_v<DataType*, decltype(std::declval<TContainer>().data())>>,
   decltype(std::declval<TContainer>().size())>
  init(TContainer&& arr) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferData(
     GL_ARRAY_BUFFER, arr.size() * sizeof(DataType), arr.data(), usage);
  }

  void
  size(GLsizeiptr size) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(DataType), nullptr, usage);
  }

  void
  data(GLintptr offset, GLsizeiptr size, const GLvoid* data) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glBufferSubData(
     GL_ARRAY_BUFFER, offset * sizeof(DataType), size * sizeof(DataType), data);
  }

  void
  attrib_pointer() const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_);
    glVertexAttribPointer(static_cast<GLuint>(attrib_index),
                          gl_vertex_attrib<DataType>::size,
                          gl_vertex_attrib<DataType>::type,
                          normalized,
                          0,
                          nullptr);
  }

private:
  GLuint buffer_{0};
};

} // namespace molphene

#endif

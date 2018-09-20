#ifndef MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP
#define MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP

#include "ShaderAttribLocation.hpp"
#include "opengl.hpp"
#include "stdafx.hpp"

namespace molphene {

template<class DataType, ShaderAttribLocation AttribLocation>
class VertexAttribsBuffer {
public:
  VertexAttribsBuffer(GLsizeiptr size, GLenum usage) noexcept
  : size_{size}
  , buffer_{new GLuint}
  {
    glGenBuffers(1, buffer_);

    glBindBuffer(GL_ARRAY_BUFFER, *buffer_);
    glBufferData(GL_ARRAY_BUFFER, size_ * sizeof(DataType), nullptr, usage);
  }

  VertexAttribsBuffer(const VertexAttribsBuffer& rsh) = delete;

  VertexAttribsBuffer(VertexAttribsBuffer&& rsh) noexcept
  : size_{rsh.size_}
  , buffer_{rsh.buffer_}
  {
    rsh.buffer_ = nullptr;
  }

  ~VertexAttribsBuffer()
  {
    if(buffer_ != nullptr) {
      glDeleteBuffers(1, buffer_);
      delete buffer_;
    }
  }

  VertexAttribsBuffer&
  operator=(const VertexAttribsBuffer& rsh) = delete;

  VertexAttribsBuffer&
  operator=(VertexAttribsBuffer&& rsh) = delete;

  void
  sub_data(GLintptr offset, GLsizeiptr size, const GLvoid* data) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, *buffer_);
    glBufferSubData(
     GL_ARRAY_BUFFER, offset * sizeof(DataType), size * sizeof(DataType), data);
  }

  void
  attrib_pointer(GLint size, GLenum type, GLboolean normalized) const noexcept
  {
    glBindBuffer(GL_ARRAY_BUFFER, *buffer_);
    glVertexAttribPointer(
     static_cast<GLuint>(AttribLocation), size, type, normalized, 0, nullptr);
  }

private:
  GLsizeiptr size_;
  GLuint* buffer_{nullptr};
};

} // namespace molphene

#endif

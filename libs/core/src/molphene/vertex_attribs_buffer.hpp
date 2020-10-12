#ifndef MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP
#define MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP

#include "gl/buffer.hpp"
#include "gl/draw_instanced_arrays.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"
#include "stdafx.hpp"

namespace molphene {

template<typename TDataType,
         shader_attrib_location attrib_index,
         GLuint VInstanceDivisor = 0,
         GLboolean normalized = GL_FALSE,
         GLenum usage = GL_STATIC_DRAW>
class VertexAttribsBuffer {
public:
  using gl_array_buffer =
   gl::buffer<TDataType, GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
  using data_type = typename gl_array_buffer::data_type;

  static constexpr auto instance_divisor = VInstanceDivisor;

  VertexAttribsBuffer() noexcept = default;

  VertexAttribsBuffer(const VertexAttribsBuffer& rsh) = delete;

  VertexAttribsBuffer(VertexAttribsBuffer&&) = delete;

  auto operator=(const VertexAttribsBuffer& rsh)
   -> VertexAttribsBuffer& = delete;

  auto operator=(VertexAttribsBuffer&& rsh) -> VertexAttribsBuffer& = delete;

  ~VertexAttribsBuffer() noexcept = default;

  void init(gsl::span<const data_type> arr) noexcept
  {
    buffer_.data(arr);
  }

  void size(GLsizeiptr size) noexcept
  {
    buffer_.reserved(size);
  }

  void data(GLintptr offset, GLsizeiptr size, const GLvoid* data) const noexcept
  {
    using SpanData = gsl::span<const data_type>;

    buffer_.subdata(offset,
                    SpanData{static_cast<const data_type*>(data),
                             static_cast<typename SpanData::size_type>(size)});
  }

  void attrib_pointer() const noexcept
  {
    buffer_.bind();

    if constexpr(gl_vertex_attrib<data_type>::is_matrix) {
      using scalar_t = typename boost::qvm::mat_traits<data_type>::scalar_type;
      for(auto index = 0, size = 4; index < size; ++index) {
        const auto location = static_cast<GLuint>(attrib_index) + index;
        glVertexAttribPointer(location,
                              gl_vertex_attrib<data_type>::size,
                              gl_vertex_attrib<data_type>::type,
                              normalized,
                              sizeof(data_type),
                              static_cast<scalar_t*>(nullptr) + size * index);
        gl::vertex_attrib_divisor(location, instance_divisor);
      }
    } else {
      const auto location = static_cast<GLuint>(attrib_index);
      glVertexAttribPointer(location,
                            gl_vertex_attrib<data_type>::size,
                            gl_vertex_attrib<data_type>::type,
                            normalized,
                            0,
                            nullptr);
      gl::vertex_attrib_divisor(location, instance_divisor);
    }
  }

private:
  gl::buffer<TDataType> buffer_{};
};

} // namespace molphene

#endif

#ifndef MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP
#define MOLPHENE_VERTEX_ATTRIBS_BUFFER_HPP

#include "gl/draw_instanced_arrays.hpp"
#include "gl/buffer.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"
#include "stdafx.hpp"

namespace molphene {

template<typename TDataType,
         shader_attrib_location attrib_index,
         GLuint VInstanceDivisor = 0,
         GLboolean normalized = GL_FALSE,
         GLenum usage = GL_STATIC_DRAW>
class vertex_attribs_buffer {
public:
  using gl_array_buffer =
   gl::buffer<TDataType, GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
  using data_type = typename gl_array_buffer::data_type;

  static constexpr auto instance_divisor = VInstanceDivisor;

  vertex_attribs_buffer() noexcept = default;

  vertex_attribs_buffer(const vertex_attribs_buffer& rsh) = delete;

  vertex_attribs_buffer(vertex_attribs_buffer&&) = delete;

  auto operator=(const vertex_attribs_buffer& rsh)
   -> vertex_attribs_buffer& = delete;

  auto operator=(vertex_attribs_buffer&& rsh)
   -> vertex_attribs_buffer& = delete;

  ~vertex_attribs_buffer() noexcept = default;

  template<
   typename TContainer,
   typename = std::void_t<
    std::enable_if_t<
     std::is_same_v<data_type*, decltype(std::declval<TContainer>().data())>>,
    decltype(std::declval<TContainer>().size())>>
  void init(TContainer&& arr) noexcept
  {
    buffer_.data(std::forward<TContainer>(arr));
  }

  void size(GLsizeiptr size) noexcept
  {
    buffer_.reserved(size);
  }

  void data(GLintptr offset, GLsizeiptr size, const GLvoid* data) const noexcept
  {
    buffer_.subdata(
     offset,
     gsl::span<const data_type>{static_cast<const data_type*>(data), size});
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

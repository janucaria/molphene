#ifndef MOLPHENE_GL_VERTEX_ATTRIBS_GUARD_HPP
#define MOLPHENE_GL_VERTEX_ATTRIBS_GUARD_HPP

#include "opengl.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {

template<shader_attrib_location... locations>
class gl_vertex_attribs_guard {
public:
  gl_vertex_attribs_guard() noexcept
  {
    (glEnableVertexAttribArray(static_cast<GLuint>(locations)), ...);
  }

  ~gl_vertex_attribs_guard() noexcept
  {
    (glDisableVertexAttribArray(static_cast<GLuint>(locations)), ...);
  }
};

} // namespace molphene
#endif

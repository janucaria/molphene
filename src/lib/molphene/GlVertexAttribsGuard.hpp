#ifndef MOLPHENE_GL_VERTEX_ATTRIBS_GUARD_HPP
#define MOLPHENE_GL_VERTEX_ATTRIBS_GUARD_HPP

#include "ShaderAttribLocation.hpp"
#include "opengl.hpp"

namespace molphene {

template<ShaderAttribLocation... locations>
class GlVertexAttribsGuard {
public:
  GlVertexAttribsGuard() noexcept
  {
    (glEnableVertexAttribArray(static_cast<GLuint>(locations)), ...);
  }

  ~GlVertexAttribsGuard() noexcept
  {
    (glDisableVertexAttribArray(static_cast<GLuint>(locations)), ...);
  }
};

} // namespace molphene
#endif

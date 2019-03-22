#ifndef MOLPHENE_GL_DRAW_INSTANCED_ARRAYS_HPP
#define MOLPHENE_GL_DRAW_INSTANCED_ARRAYS_HPP

#include "../opengl.hpp"

namespace molphene::gl {

inline void vertex_attrib_divisor(GLuint index, GLuint divisor) noexcept
{
#if GL_ANGLE_instanced_arrays
  glVertexAttribDivisorANGLE(index, divisor);
#else
  glVertexAttribDivisor(index, divisor);
#endif
}

inline void draw_arrays_instanced(GLenum mode,
                                  GLint first,
                                  GLsizei count,
                                  GLsizei primcount) noexcept
{
#if GL_ANGLE_instanced_arrays
  glDrawArraysInstancedANGLE(mode, first, count, primcount);
#else
  glDrawArraysInstanced(mode, first, count, primcount);
#endif
}

inline void draw_elements_instanced(GLenum mode,
                                    GLsizei count,
                                    GLenum type,
                                    const GLvoid* indices,
                                    GLsizei primcount) noexcept
{
#if GL_ANGLE_instanced_arrays
  glDrawElementsInstancedANGLE(mode, count, type, indices, primcount);
#else
  glDrawElementsInstanced(mode, count, type, indices, primcount);
#endif
}

} // namespace molphene::gl

#endif

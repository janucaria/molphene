#ifndef __molphene__Renderer__
#define __molphene__Renderer__

#include "color_light_buffer.h"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {
class Renderer {
public:
  Renderer();

  bool
  setupGL();

  void
  useGLProgram() const;

protected:
  GLuint gProgram;

  GLuint gVertexShader;
  GLuint gFragmentShader;

  GLuint
  createShader(GLenum shaderType, const char* pSource);
  GLuint
  createProgram(const GLuint vertexShader, const GLuint fragmentShader);

  virtual void
  setupGLProgram();

  virtual void
  setupGLUniformsLocation() = 0;

  virtual const char* vert_shader_source() = 0;
  virtual const char* frag_shader_source() = 0;
};
} // namespace molphene

#endif

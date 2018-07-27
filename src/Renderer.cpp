#include "Renderer.h"
#include <memory>

namespace molphene {

Renderer::Renderer()
: gProgram(0)
, gVertexShader(0)
, gFragmentShader(0)
{
}

bool
Renderer::setupGL()
{
  setupGLProgram();

  setupGLUniformsLocation();
  return true;
}

void
Renderer::setupGLProgram()
{
  gVertexShader = createShader(GL_VERTEX_SHADER, vert_shader_source());
  gFragmentShader = createShader(GL_FRAGMENT_SHADER, frag_shader_source());
  gProgram = createProgram(gVertexShader, gFragmentShader);
}

GLuint
Renderer::createShader(GLenum shaderType, const char* pSource)
{
  GLuint shader = glCreateShader(shaderType);
  if(shader) {
    glShaderSource(shader, 1, &pSource, NULL);
    glCompileShader(shader);
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
      GLint infoLen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
      if(infoLen) {
        auto buf = std::make_unique<char>(infoLen);
        glGetShaderInfoLog(shader, infoLen, NULL, buf.get());
        // LOG_E("Could not compile shader %d:\n%s\n", shaderType, buf);
      }
      glDeleteShader(shader);
      shader = 0;
    }
  }
  return shader;
}

GLuint
Renderer::createProgram(const GLuint vertexShader, const GLuint fragmentShader)
{
  if(!vertexShader || !fragmentShader) {
    return 0;
  }

  GLuint program = glCreateProgram();
  if(program) {
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE) {
      GLint bufLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
      if(bufLength) {
        auto buf = std::make_unique<char>(bufLength);
        glGetProgramInfoLog(program, bufLength, NULL, buf.get());
      }
      glDeleteProgram(program);
      program = 0;
    }
  }
  return program;
}

void
Renderer::useGLProgram() const
{
  glUseProgram(gProgram);
}

} // namespace molphene

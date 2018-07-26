#ifndef __Molphene__ColorLightRenderer__
#define __Molphene__ColorLightRenderer__

#include "Renderer.h"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {
class ColorLightRenderer : public Renderer {
public:
  ColorLightRenderer();

  void
  setNormalMatrix(const mat3f& m);

protected:
  const static char* vertexShaderSource;
  const static char* fragmentShaderSource;

  GLint gUniformNormalMatrixLocation;

  void
  setupGLProgram() override;

  void
  setupGLUniformsLocation() override;
};
} // namespace molphene

#endif

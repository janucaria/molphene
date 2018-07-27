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
  setModelViewMatrix(const mat4f& m4);

  void
  setNormalMatrix(const mat3f& m);

  void
  setProjectionMatrix(const mat4f& m4);

  void
  setLightSourceAmbient(const float& r,
                        const float& g,
                        const float& b,
                        const float& a);

  void
  setLightSourceDiffuse(const float& r,
                        const float& g,
                        const float& b,
                        const float& a);

  void
  setLightSourceSpecular(const float& r,
                         const float& g,
                         const float& b,
                         const float& a);

  void
  setLightSourcePosition(const float& x, const float& y, const float& z);

  void
  setMaterialAmbient(const float& r,
                     const float& g,
                     const float& b,
                     const float& a);

  void
  setMaterialDiffuse(const float& r,
                     const float& g,
                     const float& b,
                     const float& a);

  void
  setMaterialSpecular(const float& r,
                      const float& g,
                      const float& b,
                      const float& a);

  void
  setMaterialShininess(const float& v);

  void
  render(color_light_buffer& buff);

protected:
  GLuint gVertexPositionLocation;
  GLuint gVertexNormalLocation;
  GLuint gVertexColorLocation;

  GLint gUniformModelViewMatrixLocation;
  GLint gUniformNormalMatrixLocation;
  GLint gUniformProjectionMatrixLocation;

  GLint gUniformLightSourceAmbientLocation;
  GLint gUniformLightSourceDiffuseLocation;
  GLint gUniformLightSourceSpecularLocation;
  GLint gUniformLightSourcePositionLocation;

  GLint gUniformMaterialAmbientLocation;
  GLint gUniformMaterialDiffuseLocation;
  GLint gUniformMaterialSpecularLocation;
  GLint gUniformMaterialShininessLocation;

  const char*
  vert_shader_source() override;
  const char*
  frag_shader_source() override;

  void
  setupGLProgram() override;

  void
  setupGLUniformsLocation() override;
};
} // namespace molphene
#endif

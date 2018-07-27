#ifndef __Molphene__ColorLightRenderer__
#define __Molphene__ColorLightRenderer__

#include <type_traits>

#include "Directional_light.hpp"
#include "Material.hpp"
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

  template<typename T>
  std::enable_if_t<std::is_same_v<Directional_light<Rgba8, Vec3f>, T>>
  light_source(const T& light) const
  {
    light_source_ambient(light.ambient);
    light_source_diffuse(light.diffuse);
    light_source_specular(light.specular);
    light_source_position(light.direction);
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  light_source_ambient(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_light_source_ambient, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  light_source_diffuse(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_light_source_diffuse, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  light_source_specular(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_light_source_specular, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Vec3f{std::declval<Ts>()...})>
  light_source_position(Ts&&... args) const
  {
    const auto v = Vec3f{std::forward<Ts>(args)...};
    glUniform3f(g_uloc_light_source_position, v.x, v.y, v.z);
  }

  template<typename T>
  std::enable_if_t<std::is_same_v<Material<Rgba8, unsigned int>, T>>
  material(const T& mater) const
  {
    material_ambient(mater.ambient);
    material_diffuse(mater.diffuse);
    material_specular(mater.specular);
    material_shininess(mater.shininess);
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_ambient(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_ambient, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_diffuse(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_diffuse, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_specular(Ts&&... args) const
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_specular, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::void_t<decltype(GLfloat(std::declval<T>()))>
  material_shininess(T&& v) const
  {
    glUniform1f(g_uloc_material_shininess, v);
  }

  void
  render(color_light_buffer& buff);

protected:
  GLuint gVertexPositionLocation;
  GLuint gVertexNormalLocation;
  GLuint gVertexColorLocation;

  GLint gUniformModelViewMatrixLocation;
  GLint gUniformNormalMatrixLocation;
  GLint gUniformProjectionMatrixLocation;

  GLint g_uloc_light_source_ambient{-1};
  GLint g_uloc_light_source_diffuse{-1};
  GLint g_uloc_light_source_specular{-1};
  GLint g_uloc_light_source_position{-1};

  GLint g_uloc_material_ambient{-1};
  GLint g_uloc_material_diffuse{-1};
  GLint g_uloc_material_specular{-1};
  GLint g_uloc_material_shininess{-1};

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

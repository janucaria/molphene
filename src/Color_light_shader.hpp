#ifndef __Molphene__ColorLightRenderer__
#define __Molphene__ColorLightRenderer__

#include <array>
#include <type_traits>
#include <utility>

#include "Directional_light.hpp"
#include "Material.hpp"
#include "Basic_shader.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {
class Color_light_shader : public Basic_shader<Color_light_shader> {
  friend Basic_shader<Color_light_shader>;

public:
  using Basic_shader<Color_light_shader>::Attribs_location_name_type;

  enum Attrib_location : GLuint { vertex, normal, color };

  Color_light_shader();

  void
  modelview_matrix(const Mat4f& m4) const noexcept;

  void
  normal_matrix(const Mat3f& m) const noexcept;

  void
  projection_matrix(const Mat4f& m4) const noexcept;

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

protected:
  GLuint gVertexPositionLocation;
  GLuint gVertexNormalLocation;
  GLuint gVertexColorLocation;

  GLint g_uloc_modelview_matrix{-1};
  GLint g_uloc_normal_matrix{-1};
  GLint g_uloc_projection_matrix{-1};

  GLint g_uloc_light_source_ambient{-1};
  GLint g_uloc_light_source_diffuse{-1};
  GLint g_uloc_light_source_specular{-1};
  GLint g_uloc_light_source_position{-1};

  GLint g_uloc_material_ambient{-1};
  GLint g_uloc_material_diffuse{-1};
  GLint g_uloc_material_specular{-1};
  GLint g_uloc_material_shininess{-1};

  const char*
  vert_shader_source() const noexcept;

  const char*
  frag_shader_source() const noexcept;

  Attribs_location_name_type
  get_attribs_location() const noexcept;

  void
  setup_gl_attribs_val() const noexcept;

  void
  setup_gl_uniforms_loc() noexcept;

  void
  setup_gl_uniforms_val() const noexcept;
};
} // namespace molphene
#endif

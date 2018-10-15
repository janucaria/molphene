#ifndef MOLPHENE_COLOR_LIGHT_SHADER_HPP
#define MOLPHENE_COLOR_LIGHT_SHADER_HPP

#include "stdafx.hpp"

#include "BasicShader.hpp"
#include "DirectionalLight.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include "ShaderAttribLocation.hpp"

namespace molphene {
class ColorLightShader : public BasicShader<ColorLightShader> {
public:
  using Mat4f = Mat4<float>;
  using Mat3f = Mat3<float>;
  using Vec3f = Vec3<float>;
  using AttribsLocationName =
   std::array<std::pair<ShaderAttribLocation, const GLchar*>, 3>;

  ColorLightShader() noexcept;

  void
  modelview_matrix(const Mat4f& m4) const noexcept;

  template<typename U>
  std::enable_if_t<std::is_constructible_v<Mat4f, U>>
  modelview_matrix(const U& m) const noexcept
  {
    modelview_matrix(Mat4f(m));
  }

  void
  normal_matrix(const Mat3f& m) const noexcept;

  template<typename U>
  std::enable_if_t<std::is_constructible_v<Mat3f, U>>
  normal_matrix(const U& m) const noexcept
  {
    normal_matrix(Mat3f(m));
  }

  void
  projection_matrix(const Mat4f& m4) const noexcept;

  template<typename U>
  std::enable_if_t<std::is_constructible_v<Mat4f, U>>
  projection_matrix(const U& m) const noexcept
  {
    projection_matrix(Mat4f(m));
  }

  template<typename TColor, typename TConfig>
  std::void_t<decltype(
   Rgba32f{std::declval<TColor>()},
   Vec3f{std::declval<typename DirectionalLight<TColor, TConfig>::Vec3f>()})>
  light_source(const DirectionalLight<TColor, TConfig>& light) const noexcept
  {
    light_source_ambient_intensity(light.ambient_intensity);
    light_source_color(light.color);
    light_source_direction(light.direction);
    light_source_intensity(light.intensity);
    light_source_radius(-1);
  }

  template<typename TColor, typename TConfig>
  std::void_t<
   decltype(Rgba32f{std::declval<TColor>()},
            Vec3f{std::declval<typename PointLight<TColor, TConfig>::Vec3f>()})>
  light_source(const PointLight<TColor, TConfig>& light) const noexcept
  {
    light_source_ambient_intensity(light.ambient_intensity);
    light_source_attenuation(light.attenuation);
    light_source_color(light.color);
    light_source_direction(.0f, .0f, .0f);
    light_source_position(light.location);
    light_source_intensity(light.intensity);
    light_source_radius(light.radius);
  }

  template<typename TColor, typename TConfig>
  std::void_t<
   decltype(Rgba32f{std::declval<TColor>()},
            Vec3f{std::declval<typename SpotLight<TColor, TConfig>::Vec3f>()})>
  light_source(const SpotLight<TColor, TConfig>& light) const noexcept
  {
    light_source_ambient_intensity(light.ambient_intensity);
    light_source_attenuation(light.attenuation);
    light_source_beam_width(light.beam_width);
    light_source_color(light.color);
    light_source_cut_off_angle(light.cut_off_angle);
    light_source_direction(light.direction);
    light_source_position(light.location);
    light_source_intensity(light.intensity);
    light_source_radius(light.radius);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_ambient_intensity(T&& val) const noexcept
  {
    glUniform1f(g_uloc_light_source_ambient_intensity, val);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_beam_width(T&& val) const noexcept
  {
    glUniform1f(g_uloc_light_source_beam_width, val);
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  light_source_color(Ts&&... args) const noexcept
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_light_source_color, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_cut_off_angle(T&& val) const noexcept
  {
    glUniform1f(g_uloc_light_source_cut_off_angle, val);
  }

  template<typename... Ts>
  std::void_t<decltype(Vec3f{std::declval<Ts>()...})>
  light_source_direction(Ts&&... args) const noexcept
  {
    const auto v = Vec3f{std::forward<Ts>(args)...};
    glUniform3f(g_uloc_light_source_direction, v.x, v.y, v.z);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_intensity(T&& val) const noexcept
  {
    glUniform1f(g_uloc_light_source_intensity, val);
  }

  template<typename... Ts>
  std::void_t<decltype(Vec3f{std::declval<Ts>()...})>
  light_source_attenuation(Ts&&... args) const noexcept
  {
    const auto v = Vec3f{std::forward<Ts>(args)...};
    glUniform3f(g_uloc_light_source_attenuation, v.x, v.y, v.z);
  }

  template<typename... Ts>
  std::void_t<decltype(Vec3f{std::declval<Ts>()...})>
  light_source_position(Ts&&... args) const noexcept
  {
    const auto v = Vec3f{std::forward<Ts>(args)...};
    glUniform3f(g_uloc_light_source_position, v.x, v.y, v.z);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_radius(T&& val) const noexcept
  {
    glUniform1f(g_uloc_light_source_radius, val);
  }

  template<typename TColor, typename TScalar>
  std::void_t<decltype(Rgba32f{std::declval<TColor>()},
                       std::is_constructible_v<TScalar, GLfloat>)>
  material(const Material<TColor, TScalar>& mater) const noexcept
  {
    material_ambient_intensity(mater.ambient_intensity);
    material_emissive_color(mater.emissive_color);
    material_diffuse_color(mater.diffuse_color);
    material_specular_color(mater.specular_color);
    material_shininess(mater.shininess);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  material_ambient_intensity(T&& val) const noexcept
  {
    glUniform1f(g_uloc_material_ambient_intensity, val);
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_emissive_color(Ts&&... args) const noexcept
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_emissive_color, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_diffuse_color(Ts&&... args) const noexcept
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_diffuse_color, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  material_specular_color(Ts&&... args) const noexcept
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     g_uloc_material_specular_color, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  material_shininess(T&& v) const noexcept
  {
    glUniform1f(g_uloc_material_shininess, v);
  }

  template<typename TColor, typename TScalar>
  std::void_t<decltype(Rgba32f{std::declval<TColor>()},
                       std::is_convertible_v<TScalar, GLfloat>)>
  fog(const Fog<TColor, TScalar>& fog) const noexcept
  {
    fog_color(fog.color);
    fog_fog_type(fog.fog_type == std::decay_t<decltype(fog)>::Type::linear);
    fog_visibility_range(fog.visibility_range);
  }

  template<typename... Ts>
  std::void_t<decltype(Rgba32f{std::declval<Ts>()...})>
  fog_color(Ts&&... args) const noexcept
  {
    const auto col = Rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(g_uloc_fog_color, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLint>>
  fog_fog_type(T&& val) const noexcept
  {
    glUniform1i(g_uloc_fog_fog_type, val);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  fog_visibility_range(T&& val) const noexcept
  {
    glUniform1f(g_uloc_fog_visibility_range, val);
  }

  void
  color_texture_image(GLuint texture) const noexcept;

protected:
  GLint g_uloc_modelview_matrix{-1};
  GLint g_uloc_normal_matrix{-1};
  GLint g_uloc_projection_matrix{-1};

  GLint g_uloc_light_source_ambient_intensity{-1};
  GLint g_uloc_light_source_attenuation{-1};
  GLint g_uloc_light_source_beam_width{-1};
  GLint g_uloc_light_source_intensity{-1};
  GLint g_uloc_light_source_color{-1};
  GLint g_uloc_light_source_cut_off_angle{-1};
  GLint g_uloc_light_source_direction{-1};
  GLint g_uloc_light_source_position{-1};
  GLint g_uloc_light_source_radius{-1};

  GLint g_uloc_material_ambient_intensity{-1};
  GLint g_uloc_material_emissive_color{-1};
  GLint g_uloc_material_diffuse_color{-1};
  GLint g_uloc_material_specular_color{-1};
  GLint g_uloc_material_shininess{-1};

  GLint g_uloc_fog_color{-1};
  GLint g_uloc_fog_fog_type{-1};
  GLint g_uloc_fog_visibility_range{-1};

  const char*
  vert_shader_source() const noexcept;

  const char*
  frag_shader_source() const noexcept;

  AttribsLocationName
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

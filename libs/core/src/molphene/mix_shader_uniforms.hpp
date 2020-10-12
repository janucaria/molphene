#ifndef MOLPHENE_MIX_SHADER_UNIFORMS_HPP
#define MOLPHENE_MIX_SHADER_UNIFORMS_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "opengl.hpp"

#include "directional_light.hpp"
#include "point_light.hpp"
#include "spot_light.hpp"

#include "fog.hpp"
#include "material.hpp"

namespace molphene {

template<typename TShader>
class model_view_matrix_uniform {
  struct accessor : TShader {
    static auto call_gprogram(const TShader* shader) noexcept -> GLuint
    {
      return std::invoke(&accessor::gprogram, shader);
    }
  };

public:
  using mat4f = mat4<GLfloat>;

  void init_uniform_location(GLuint gprogram) noexcept
  {
    auto program = accessor::call_gprogram(static_cast<const TShader*>(this));
    modelview_matrix_location_ =
     glGetUniformLocation(program, "u_ModelViewMatrix");
  }

  void modelview_matrix(const mat4f& m4) const noexcept
  {
    glUniformMatrix4fv(
     modelview_matrix_location_, 1, GL_FALSE, static_cast<const float*>(m4.m));
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<mat4f, U>>>
  void modelview_matrix(const U& m) const noexcept
  {
    modelview_matrix(mat4f(m));
  }

private:
  GLint modelview_matrix_location_{-1};
};

template<typename TShader>
class projection_matrix_uniform {
public:
  using mat4f = mat4<GLfloat>;

  void init_uniform_location(GLuint gprogram) noexcept
  {
    projection_matrix_location_ =
     glGetUniformLocation(gprogram, "u_ProjectionMatrix");
  }

  void projection_matrix(const mat4f& m4) const noexcept
  {
    glUniformMatrix4fv(
     projection_matrix_location_, 1, GL_FALSE, static_cast<const float*>(m4.m));
  }

  template<typename U>
  std::enable_if_t<std::is_constructible_v<mat4f, U>>
  projection_matrix(const U& m) const noexcept
  {
    projection_matrix(mat4f(m));
  }

private:
  GLint projection_matrix_location_{-1};
};

template<typename TShader>
class normal_matrix_uniform {
public:
  using mat3f = mat3<GLfloat>;

  static inline const char* varname = "u_NormalMatrix";

  void init_uniform_location(GLuint gprogram) noexcept
  {
    normal_matrix_location_ = glGetUniformLocation(gprogram, varname);
  }

  void normal_matrix(const mat3f& m) const noexcept
  {
    glUniformMatrix3fv(
     normal_matrix_location_, 1, GL_FALSE, static_cast<const float*>(m.m));
  }

  template<typename U>
  std::enable_if_t<std::is_constructible_v<mat3f, U>>
  normal_matrix(const U& m) const noexcept
  {
    normal_matrix(mat3f(m));
  }

private:
  GLint normal_matrix_location_{-1};
};

template<typename TShader>
class material_uniform {
public:
  using mat4f = mat4<float>;
  using mat3f = mat3<float>;
  using vec3f = vec3<float>;

  void init_uniform_location(GLuint gprogram) noexcept
  {
    material_ambient_intensity_location_ =
     glGetUniformLocation(gprogram, "u_Material_ambientIntensity");
    material_emissive_color_location_ =
     glGetUniformLocation(gprogram, "u_Material_emissiveColor");
    material_diffuse_color_location_ =
     glGetUniformLocation(gprogram, "u_Material_diffuseColor");
    material_shininess_location_ =
     glGetUniformLocation(gprogram, "u_Material_shininess");
    material_specular_color_location_ =
     glGetUniformLocation(gprogram, "u_Material_specularColor");
  }

  template<typename TColor, typename TScalar>
  std::void_t<decltype(rgba32f{std::declval<TColor>()},
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
    glUniform1f(material_ambient_intensity_location_, val);
  }

  template<typename... Ts>
  std::void_t<decltype(rgba32f{std::declval<Ts>()...})>
  material_emissive_color(Ts&&... args) const noexcept
  {
    const auto col = rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(material_emissive_color_location_,
                 1,
                 reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(rgba32f{std::declval<Ts>()...})>
  material_diffuse_color(Ts&&... args) const noexcept
  {
    const auto col = rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(material_diffuse_color_location_,
                 1,
                 reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename... Ts>
  std::void_t<decltype(rgba32f{std::declval<Ts>()...})>
  material_specular_color(Ts&&... args) const noexcept
  {
    const auto col = rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(material_specular_color_location_,
                 1,
                 reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  material_shininess(T&& v) const noexcept
  {
    glUniform1f(material_shininess_location_, v);
  }

private:
  GLint material_ambient_intensity_location_{-1};
  GLint material_emissive_color_location_{-1};
  GLint material_diffuse_color_location_{-1};
  GLint material_specular_color_location_{-1};
  GLint material_shininess_location_{-1};
};

template<typename TShader>
class fog_uniform {
public:
  using mat4f = mat4<GLfloat>;

  void init_uniform_location(GLuint gprogram) noexcept
  {
    fog_color_location_ = glGetUniformLocation(gprogram, "u_Fog_color");
    fog_fog_type_location_ =
     glGetUniformLocation(gprogram, "u_Fog_fogTypeLinear");
    fog_visibility_range_location_ =
     glGetUniformLocation(gprogram, "u_Fog_visibilityRange");
  }

  template<typename TColor, typename TScalar>
  std::void_t<decltype(rgba32f{std::declval<TColor>()},
                       std::is_convertible_v<TScalar, GLfloat>)>
  fog(const Fog<TColor, TScalar>& fog) const noexcept
  {
    fog_color(fog.color);
    fog_fog_type(fog.fog_type == std::decay_t<decltype(fog)>::type::linear);
    fog_visibility_range(fog.visibility_range);
  }

  template<typename... Ts>
  std::void_t<decltype(rgba32f{std::declval<Ts>()...})>
  fog_color(Ts&&... args) const noexcept
  {
    const auto col = rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     fog_color_location_, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLint>> fog_fog_type(T&& val) const
   noexcept
  {
    glUniform1i(fog_fog_type_location_, val);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  fog_visibility_range(T&& val) const noexcept
  {
    glUniform1f(fog_visibility_range_location_, val);
  }

private:
  GLint fog_color_location_{-1};
  GLint fog_fog_type_location_{-1};
  GLint fog_visibility_range_location_{-1};
};

template<typename TShader>
class light_source_uniform {
public:
  using mat4f = mat4<GLfloat>;
  using mat3f = mat3<GLfloat>;
  using vec3f = vec3<GLfloat>;

  void init_uniform_location(GLuint gprogram) noexcept
  {
    light_source_ambient_intensity_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_ambientIntensity");
    light_source_attenuation_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_attenuation");
    light_source_color_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_color");
    light_source_direction_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_direction");
    light_source_intensity_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_intensity");
    light_source_position_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_position");
    light_source_radius_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_radius");
    light_source_beam_width_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_beamWidth");
    light_source_cut_off_angle_location_ =
     glGetUniformLocation(gprogram, "u_LightSource_cutOffAngle");
  }

  template<typename TColor, typename TConfig>
  std::void_t<decltype(
   rgba32f{std::declval<TColor>()},
   vec3f{std::declval<typename DirectionalLight<TColor, TConfig>::vec3f>()})>
  light_source(const DirectionalLight<TColor, TConfig>& light) const noexcept
  {
    light_source_ambient_intensity(light.ambient_intensity);
    light_source_color(light.color);
    light_source_direction(light.direction);
    light_source_intensity(light.intensity);
    light_source_radius(-1);
  }

  template<typename TColor, typename TConfig>
  std::void_t<decltype(
   rgba32f{std::declval<TColor>()},
   vec3f{std::declval<typename PointLight<TColor, TConfig>::vec3f>()})>
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
   decltype(rgba32f{std::declval<TColor>()},
            vec3f{std::declval<typename SpotLight<TColor, TConfig>::vec3f>()})>
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
    glUniform1f(light_source_ambient_intensity_location_, val);
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_beam_width(T&& val) const noexcept
  {
    glUniform1f(light_source_beam_width_location_, val);
  }

  template<typename... Ts>
  std::void_t<decltype(rgba32f{std::declval<Ts>()...})>
  light_source_color(Ts&&... args) const noexcept
  {
    const auto col = rgba32f{std::forward<Ts>(args)...};
    glUniform4fv(
     light_source_color_location_, 1, reinterpret_cast<const GLfloat*>(&col));
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_cut_off_angle(T&& val) const noexcept
  {
    glUniform1f(light_source_cut_off_angle_location_, val);
  }

  template<typename... Ts>
  std::void_t<decltype(vec3f{std::declval<Ts>()...})>
  light_source_direction(Ts&&... args) const noexcept
  {
    const auto v = vec3f{std::forward<Ts>(args)...};
    glUniform3f(light_source_direction_location_, v.x(), v.y(), v.z());
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_intensity(T&& val) const noexcept
  {
    glUniform1f(light_source_intensity_location_, val);
  }

  template<typename... Ts>
  std::void_t<decltype(vec3f{std::declval<Ts>()...})>
  light_source_attenuation(Ts&&... args) const noexcept
  {
    const auto v = vec3f{std::forward<Ts>(args)...};
    glUniform3f(light_source_attenuation_location_, v.x(), v.y(), v.z());
  }

  template<typename... Ts>
  std::void_t<decltype(vec3f{std::declval<Ts>()...})>
  light_source_position(Ts&&... args) const noexcept
  {
    const auto v = vec3f{std::forward<Ts>(args)...};
    glUniform3f(light_source_position_location_, v.x(), v.y(), v.z());
  }

  template<typename T>
  std::enable_if_t<std::is_convertible_v<T, GLfloat>>
  light_source_radius(T&& val) const noexcept
  {
    glUniform1f(light_source_radius_location_, val);
  }

private:
  GLint light_source_ambient_intensity_location_{-1};
  GLint light_source_attenuation_location_{-1};
  GLint light_source_beam_width_location_{-1};
  GLint light_source_intensity_location_{-1};
  GLint light_source_color_location_{-1};
  GLint light_source_cut_off_angle_location_{-1};
  GLint light_source_direction_location_{-1};
  GLint light_source_position_location_{-1};
  GLint light_source_radius_location_{-1};
};

template<typename TShader>
class color2d_sampler_uniform {
public:
  void init_uniform_location(GLuint gprogram) noexcept
  {
    color_2d_sampler_uniform_location_ =
     glGetUniformLocation(gprogram, "u_TexColorImage");
  }

  void color_texture_image(GLuint texture) const noexcept
  {
    glUniform1i(color_2d_sampler_uniform_location_, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture);
  }

private:
  GLint color_2d_sampler_uniform_location_{-1};
};

template<typename TShader, template<typename> class... TShaderUniform>
class mix_shader_uniforms : public TShaderUniform<TShader>... {
public:
  void init_uniform_location(GLuint gprogram) noexcept
  {
    (TShaderUniform<TShader>::init_uniform_location(gprogram), ...);
  }
};

} // namespace molphene

#endif

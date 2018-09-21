#ifndef MOLPHENE_OPENGL_HPP
#define MOLPHENE_OPENGL_HPP

#ifdef __EMSCRIPTEN__

#include <GLES2/gl2.h>

#else

#include <OpenGL/gl.h>

#endif

#include "m3d.hpp"

namespace molphene {
namespace detail {

template<typename T>
struct is_gl_vertex_attrib
: std::bool_constant<std::is_same_v<T, GLbyte> || std::is_same_v<T, GLubyte> ||
                     std::is_same_v<T, GLshort> ||
                     std::is_same_v<T, GLushort> ||
                     std::is_same_v<T, GLfloat>> {
};

template<typename T>
inline constexpr auto is_gl_vertex_attrib_v = is_gl_vertex_attrib<T>::value;

template<typename T>
struct gl_value_type;

template<>
struct gl_value_type<GLbyte> {
  static constexpr GLenum value = GL_BYTE;
};
template<>
struct gl_value_type<GLubyte> {
  static constexpr GLenum value = GL_UNSIGNED_BYTE;
};
template<>
struct gl_value_type<GLshort> {
  static constexpr GLenum value = GL_SHORT;
};
template<>
struct gl_value_type<GLushort> {
  static constexpr GLenum value = GL_UNSIGNED_SHORT;
};
template<>
struct gl_value_type<GLfloat> {
  static constexpr GLenum value = GL_FLOAT;
};

} // namespace detail

template<typename T>
inline constexpr auto gl_value_type_v = detail::gl_value_type<T>::value;

template<typename T, typename = void>
struct gl_attrib_pointer_type;

template<typename T>
struct gl_attrib_pointer_type<
 T,
 std::enable_if_t<detail::is_gl_vertex_attrib_v<T>>> {
  static constexpr GLint type = gl_value_type_v<T>;
};

template<typename T>
struct gl_vertex_attrib : gl_attrib_pointer_type<T> {
  static constexpr GLint size = 1;
};

template<typename T>
struct gl_vertex_attrib<Vec2<T>> : gl_attrib_pointer_type<T> {
  static constexpr GLint size = 2;
};

template<typename T>
struct gl_vertex_attrib<Vec3<T>> : gl_attrib_pointer_type<T> {
  static constexpr GLint size = 3;
};

} // namespace molphene

#endif

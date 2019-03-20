#ifndef MOLPHENE_SHADER_ATTRIB_LOCATION_HPP
#define MOLPHENE_SHADER_ATTRIB_LOCATION_HPP

#include "opengl.hpp"

namespace molphene {

enum class shader_attrib_location : GLuint {
  vertex,
  normal,
  color,
  texcoordcolor,
  transformation,
  transformation_1,
  transformation_2,
  transformation_3
};

template<shader_attrib_location...>
struct shader_attrib_list {
};

template<auto>
struct traits;

template<>
struct traits<shader_attrib_location::vertex> {
  static inline const GLchar* name = "a_Vertex";
};

template<>
struct traits<shader_attrib_location::normal> {
  static inline const GLchar* name = "a_Normal";
};

template<>
struct traits<shader_attrib_location::color> {
  static inline const GLchar* name = "a_Color";
};

template<>
struct traits<shader_attrib_location::texcoordcolor> {
  static inline const GLchar* name = "a_TexCoord0";
};

template<>
struct traits<shader_attrib_location::transformation> {
  static inline const GLchar* name = "a_Transformation";
};

template<>
struct traits<shader_attrib_location::transformation_1> {
  static inline const GLchar* name = "a_Transformation1";
};

template<>
struct traits<shader_attrib_location::transformation_2> {
  static inline const GLchar* name = "a_Transformation2";
};

template<>
struct traits<shader_attrib_location::transformation_3> {
  static inline const GLchar* name = "a_Transformation3";
};

} // namespace molphene

#endif

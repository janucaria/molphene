#ifndef MOLPHENE_SHADER_ATTRIB_LOCATION_HPP
#define MOLPHENE_SHADER_ATTRIB_LOCATION_HPP

#include "opengl.hpp"

namespace molphene {

enum class ShaderAttribLocation : GLuint {
  vertex,
  normal,
  color,
  texcoordcolor
};

template<ShaderAttribLocation...>
struct ShaderAttribList {
};

template<auto>
struct traits;

template<>
struct traits<ShaderAttribLocation::vertex> {
  static inline const GLchar* name = "a_Vertex";
};

template<>
struct traits<ShaderAttribLocation::normal> {
  static inline const GLchar* name = "a_Normal";
};

template<>
struct traits<ShaderAttribLocation::color> {
  static inline const GLchar* name = "a_Color";
};

template<>
struct traits<ShaderAttribLocation::texcoordcolor> {
  static inline const GLchar* name = "a_TexCoord0";
};

} // namespace molphene

#endif

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

}

#endif
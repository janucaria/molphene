#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "ColorLightBuffer.hpp"


namespace molphene {

class SpacefillRepresentation {
public:
  std::unique_ptr<ColorLightBuffer> atom_sphere_buffer;
};

}

#endif

#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_image_texture.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "m3d.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

template<typename TSPhereBuffers>
class basic_spacefill_representation {
public:
  using sphere_buffers_type = TSPhereBuffers;

  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};

  double radius_size{1};

  color_manager color_manager;

  sphere_buffers_type atom_sphere_buffers;

  template<typename TAtomElement>
  auto atom_radius(TAtomElement element) const noexcept -> double
  {
    switch(radius_type) {
    case atom_radius_kind::van_der_waals:
      return element.rvdw;
    case atom_radius_kind::covalent:
      return element.rcov;
    default:
      return radius_size;
    }
  }

  auto atom_color(const atom& atom) const noexcept -> rgba8
  {
    return color_manager.get_element_color(atom.element().symbol);
  }

  void render(const color_light_shader& shader) const noexcept
  {
    atom_sphere_buffers.draw(shader);
  }
};

} // namespace molphene

#endif

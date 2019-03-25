#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "cylinder_vertex_buffers_batch.hpp"
#include "image_texture.hpp"
#include "m3d.hpp"
#include "sphere_vertex_buffers_batch.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

template<typename TSphereBuffers, typename TCylinderBuffers>
class basic_ballstick_representation {
public:
  using sphere_buffers_type = TSphereBuffers;

  using cylinder_buffers_type = TCylinderBuffers;

  atom_radius_kind atom_radius_type{atom_radius_kind::van_der_waals};

  double atom_radius_size{1};

  double radius_size{0.275};

  color_manager color_manager;

  sphere_buffers_type atom_sphere_buffers;

  cylinder_buffers_type bond1_cylinder_buffers;

  cylinder_buffers_type bond2_cylinder_buffers;

  template<typename TAtomElement>
  auto atom_radius(TAtomElement element) const noexcept -> double
  {
    switch(atom_radius_type) {
    case atom_radius_kind::van_der_waals:
      return element.rvdw * radius_size;
    case atom_radius_kind::covalent:
      return element.rcov * radius_size;
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
    bond1_cylinder_buffers.draw(shader);
    bond2_cylinder_buffers.draw(shader);
    atom_sphere_buffers.draw(shader);
  }
};

} // namespace molphene

#endif

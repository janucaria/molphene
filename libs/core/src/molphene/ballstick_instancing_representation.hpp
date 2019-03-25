#ifndef MOLPHENE_BALLSTICK_INSTANCING_REPRESENTATION_HPP
#define MOLPHENE_BALLSTICK_INSTANCING_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "cylinder_vertex_buffers_instanced.hpp"
#include "image_texture.hpp"
#include "m3d.hpp"
#include "sphere_vertex_buffers_instanced.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class ballstick_instancing_representation {
public:
  atom_radius_kind atom_radius_type{atom_radius_kind::van_der_waals};

  double atom_radius_size{1};

  double radius_size{0.275};

  color_manager color_manager;

  sphere_vertex_buffers_instanced atom_sphere_buffers;

  cylinder_vertex_buffers_instanced bond1_cylinder_buffers;

  cylinder_vertex_buffers_instanced bond2_cylinder_buffers;

  auto atom_radius(typename atom::atom_element element) const noexcept
   -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void render(const color_light_shader& shader) const noexcept;
};

} // namespace molphene

#endif

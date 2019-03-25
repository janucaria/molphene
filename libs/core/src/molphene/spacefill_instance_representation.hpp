#ifndef MOLPHENE_SPACEFILL_INSTANCE_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_INSTANCE_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "image_texture.hpp"
#include "m3d.hpp"
#include "sphere_vertex_instance_buffers.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class spacefill_instance_representation {
public:
  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};

  double radius_size{1};

  color_manager color_manager;

  sphere_vertex_instance_buffers atom_sphere_buffers;

  auto atom_radius(typename atom::atom_element element) const noexcept
   -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void render(const color_light_shader& shader) const noexcept;
};

} // namespace molphene

#endif

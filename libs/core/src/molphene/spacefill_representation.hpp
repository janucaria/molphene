#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "image_texture.hpp"
#include "m3d.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class spacefill_representation {
public:
  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};

  double radius_size{1};

  color_manager color_manager;

  std::unique_ptr<color_image_texture> atom_sphere_color_texture;

  std::unique_ptr<positions_buffer_array> atom_sphere_buffer_positions;

  std::unique_ptr<normals_buffer_array> atom_sphere_buffer_normals;

  std::unique_ptr<texcoords_buffer_array> atom_sphere_buffer_texcoords;

  auto atom_radius(typename atom::atom_element element) const noexcept
   -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void render(const color_light_shader& shader) const noexcept;
};

} // namespace molphene

#endif

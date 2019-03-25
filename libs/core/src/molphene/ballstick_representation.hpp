#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "image_texture.hpp"
#include "m3d.hpp"
#include "sphere_vertex_buffers_batch.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class ballstick_representation {
public:
  atom_radius_kind atom_radius_type{atom_radius_kind::van_der_waals};

  double atom_radius_size{1};

  double radius_size{0.275};

  color_manager color_manager;

  sphere_vertex_buffers_batch atom_sphere_buffers;

  std::unique_ptr<color_image_texture> bond1_cylinder_color_texture;

  std::unique_ptr<positions_buffer_array> bond1_cylinder_buffer_positions;

  std::unique_ptr<normals_buffer_array> bond1_cylinder_buffer_normals;

  std::unique_ptr<texcoords_buffer_array> bond1_cylinder_buffer_texcoords;

  std::unique_ptr<color_image_texture> bond2_cylinder_color_texture;

  std::unique_ptr<positions_buffer_array> bond2_cylinder_buffer_positions;

  std::unique_ptr<normals_buffer_array> bond2_cylinder_buffer_normals;

  std::unique_ptr<texcoords_buffer_array> bond2_cylinder_buffer_texcoords;

  auto atom_radius(typename atom::atom_element element) const noexcept
   -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void render(const color_light_shader& shader) const noexcept;
};

} // namespace molphene

#endif

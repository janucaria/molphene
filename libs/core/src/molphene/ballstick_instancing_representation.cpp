#include "ballstick_instancing_representation.hpp"

#include "gl/draw_instanced_arrays.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {

auto ballstick_instancing_representation::atom_radius(
 typename atom::atom_element element) const noexcept -> double
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

auto ballstick_instancing_representation::atom_color(const atom& atom) const
 noexcept -> rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void ballstick_instancing_representation::render(
 const color_light_shader& shader) const noexcept
{
  bond1_cylinder_buffers.draw(shader);
  bond2_cylinder_buffers.draw(shader);
  atom_sphere_buffers.draw(shader);
}

} // namespace molphene

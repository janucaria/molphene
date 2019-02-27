#include "ballstick_representation.hpp"

namespace molphene {

auto ballstick_representation::atom_radius(
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

auto ballstick_representation::atom_color(const atom& atom) const noexcept
 -> rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void ballstick_representation::clear_buffers() noexcept
{
  atom_sphere_buffer.reset(nullptr);

  bond1_cylinder_buffer.reset(nullptr);

  bond2_cylinder_buffer.reset(nullptr);
}

void ballstick_representation::render(const color_light_shader& shader) const
 noexcept
{
  shader.color_texture_image(bond1_cylinder_buffer->color_texture_image());
  bond1_cylinder_buffer->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

  shader.color_texture_image(bond2_cylinder_buffer->color_texture_image());
  bond2_cylinder_buffer->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

  shader.color_texture_image(atom_sphere_buffer->color_texture_image());
  atom_sphere_buffer->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });
}

} // namespace molphene
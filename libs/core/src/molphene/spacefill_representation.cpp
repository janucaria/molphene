#include "spacefill_representation.hpp"

#include "gl_vertex_attribs_guard.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {

auto spacefill_representation::atom_radius(
 typename atom::atom_element element) const noexcept -> double
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

auto spacefill_representation::atom_color(const atom& atom) const noexcept
 -> rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void spacefill_representation::render(const color_light_shader& shader) const
 noexcept
{
  const auto verts_guard =
   gl_vertex_attribs_guard<shader_attrib_location::vertex,
                           shader_attrib_location::normal,
                           shader_attrib_location::texcoordcolor>{};

  assert(all_has_same_props(*atom_sphere_buffer_positions,
                            *atom_sphere_buffer_normals,
                            *atom_sphere_buffer_texcoords));

  shader.color_texture_image(atom_sphere_color_texture->texture_image());

  const auto size = atom_sphere_buffer_positions->size();
  const auto remain_instances =
   atom_sphere_buffer_positions->remain_instances();
  const auto instances_per_block =
   atom_sphere_buffer_positions->instances_per_block();
  const auto verts_per_instance =
   atom_sphere_buffer_positions->verts_per_instance();

  for(auto i = GLsizei{0}; i < size; ++i) {
    const auto verts_count =
     GLsizei{i == (size - 1) ? remain_instances : instances_per_block};
    const auto count = verts_count * verts_per_instance;

    atom_sphere_buffer_positions->bind_attrib_pointer_index(i);
    atom_sphere_buffer_normals->bind_attrib_pointer_index(i);
    atom_sphere_buffer_texcoords->bind_attrib_pointer_index(i);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
  }
}

} // namespace molphene
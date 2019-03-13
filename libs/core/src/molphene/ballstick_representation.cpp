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

void ballstick_representation::render(const color_light_shader& shader) const
 noexcept
{
  shader.color_texture_image(bond1_cylinder_buffer->color_texture_image());
  bond1_cylinder_buffer->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

  shader.color_texture_image(bond2_cylinder_buffer->color_texture_image());
  bond2_cylinder_buffer->setup_attrib_pointer(
   [](auto count) noexcept { glDrawArrays(GL_TRIANGLE_STRIP, 0, count); });

  {
    assert(atom_sphere_buffer_positions->size_ ==
           atom_sphere_buffer_normals->size_);
    assert(atom_sphere_buffer_positions->size_ ==
           atom_sphere_buffer_texcoords->size_);

    assert(atom_sphere_buffer_positions->remain_instances_ ==
           atom_sphere_buffer_normals->remain_instances_);
    assert(atom_sphere_buffer_positions->remain_instances_ ==
           atom_sphere_buffer_texcoords->remain_instances_);

    assert(atom_sphere_buffer_positions->instances_per_block_ ==
           atom_sphere_buffer_normals->instances_per_block_);
    assert(atom_sphere_buffer_positions->instances_per_block_ ==
           atom_sphere_buffer_texcoords->instances_per_block_);

    assert(atom_sphere_buffer_positions->verts_per_instance_ ==
           atom_sphere_buffer_normals->verts_per_instance_);
    assert(atom_sphere_buffer_positions->verts_per_instance_ ==
           atom_sphere_buffer_texcoords->verts_per_instance_);

    shader.color_texture_image(atom_sphere_color_texture->texture_image());

    const auto size_ = atom_sphere_buffer_positions->size_;
    const auto remain_instances_ =
     atom_sphere_buffer_positions->remain_instances_;
    const auto instances_per_block_ =
     atom_sphere_buffer_positions->instances_per_block_;
    const auto verts_per_instance_ =
     atom_sphere_buffer_positions->verts_per_instance_;

    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto verts_count =
       GLsizei{i == (size_ - 1) ? remain_instances_ : instances_per_block_};

      std::get<0>(atom_sphere_buffer_positions->attrib_buffers_)[i]
       .attrib_pointer();
      std::get<0>(atom_sphere_buffer_normals->attrib_buffers_)[i]
       .attrib_pointer();
      std::get<0>(atom_sphere_buffer_texcoords->attrib_buffers_)[i]
       .attrib_pointer();

      const auto count = verts_count * verts_per_instance_;
      glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
    }
  }
}

} // namespace molphene

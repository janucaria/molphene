#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "color_image_texture.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "cylinder_mesh_attribute.hpp"
#include "cylinder_vertex_buffers_batch.hpp"
#include "m3d.hpp"
#include "molecule_to_shape.hpp"
#include "sphere_mesh_attribute.hpp"
#include "sphere_vertex_buffers_batch.hpp"
#include "utility.hpp"

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

  template<typename TSizedRangeAtoms, typename TSizedRangeBonds>
  void build_vertex_buffers(TSizedRangeAtoms&& atoms_in_bond,
                            TSizedRangeBonds&& bond_atoms)
  {
    {
      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(
        atoms_in_bond.size());

      atoms_to_sphere_attrs(std::forward<TSizedRangeAtoms>(atoms_in_bond),
                            std::back_inserter(sphere_mesh_attrs),
                            {atom_radius_type, atom_radius_size, 0.5});

      atom_sphere_buffers.build_buffers(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs =
     detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

    bonds_to_cylinder_attrs(std::forward<TSizedRangeBonds>(bond_atoms),
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {true, radius_size});

    bond1_cylinder_buffers.build_buffers(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    bonds_to_cylinder_attrs(std::forward<TSizedRangeBonds>(bond_atoms),
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {false, radius_size});

    bond2_cylinder_buffers.build_buffers(cylinder_mesh_attrs);
  }

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

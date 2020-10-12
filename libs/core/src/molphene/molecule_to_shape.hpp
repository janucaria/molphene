#ifndef MOLPHENE_MOLECULE_TO_SHAPE_HPP
#define MOLPHENE_MOLECULE_TO_SHAPE_HPP

#include <molecule/atom_radius_kind.hpp>

#include "color_manager.hpp"
#include "cylinder_mesh_attribute.hpp"
#include "sphere_mesh_attribute.hpp"

namespace molphene {

struct atom_to_sphere_attrs_options {
  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};
  double radius_size{1};
  double radius_scale{1};
};

struct bond_to_cylinder_attrs_options {
  bool is_first{true};
  double radius_size{1};
};

template<typename TSizedRange, typename TOutIter>
void atoms_to_sphere_attrs(const TSizedRange& atoms,
                           TOutIter output,
                           atom_to_sphere_attrs_options options)
{
  using float_type = double;
  using vec2f = vec2<float_type>;

  const auto col_manager = ColorManager{};

  const auto tex_size =
   static_cast<std::size_t>(std::ceil(std::sqrt(atoms.size())));
  auto aindex = std::size_t{0};
  for(auto atomptr : atoms) {
    const auto& atom = *atomptr;
    const auto element = atom.element();
    const auto apos = atom.position();
    const auto arad = [&]() noexcept->float_type
    {
      auto radius = 0.0;
      switch(options.radius_type) {
      case atom_radius_kind::van_der_waals:
        radius = element.rvdw * options.radius_scale;
        break;
      case atom_radius_kind::covalent:
        radius = element.rcov;
        break;
      default:
        radius = options.radius_size;
        break;
      }

      return radius * options.radius_scale;
    }
    ();
    const auto acol = col_manager.get_element_color(element.symbol);

    const auto atex = vec2f{float_type(aindex % tex_size),
                            std::floor(float_type(aindex) / tex_size)} /
                      tex_size;

    auto sphere_mesh_attr = sphere_mesh_attribute{};
    sphere_mesh_attr.sphere = {arad, apos};
    sphere_mesh_attr.index = aindex++;
    sphere_mesh_attr.texcoord = atex;
    sphere_mesh_attr.color = acol;

    *output++ = sphere_mesh_attr;
  }
}

template<typename TSizeRange, typename TOutIter>
void bonds_to_cylinder_attrs(const TSizeRange& bond_atoms,
                             TOutIter output,
                             bond_to_cylinder_attrs_options options)
{
  using float_type = double;
  using vec2f = vec2<float_type>;

  const auto col_manager = ColorManager{};

  const auto tex_size =
   static_cast<std::size_t>(std::ceil(std::sqrt(bond_atoms.size())));
  auto aindex = std::size_t{0};
  for(auto&& atom_pair : bond_atoms) {
    const auto& atom1 = *atom_pair.first;
    const auto& atom2 = *atom_pair.second;
    const auto element1 = atom1.element();
    const auto element2 = atom2.element();
    const auto apos1 = atom1.position();
    const auto apos2 = atom2.position();
    const auto acol1 = col_manager.get_element_color(element1.symbol);
    const auto acol2 = col_manager.get_element_color(element2.symbol);

    const auto atex = vec2f{float_type(aindex % tex_size),
                            std::floor(float_type(aindex) / tex_size)} /
                      tex_size;

    const auto rad = options.radius_size;
    const auto midpos = (apos1 + apos2) * 0.5;

    auto cyl = Cylinder<float_type>{rad};
    auto color = rgba8{};
    if(options.is_first) {
      cyl.top = apos1;
      cyl.bottom = midpos;
      color = acol1;
    } else {
      cyl.top = midpos;
      cyl.bottom = apos2;
      color = acol2;
    }

    auto cyl_mesh_attr = cylinder_mesh_attribute{};
    cyl_mesh_attr.cylinder = cyl;
    cyl_mesh_attr.index = aindex++;
    cyl_mesh_attr.texcoord = atex;
    cyl_mesh_attr.color = color;

    *output++ = cyl_mesh_attr;
  }
}

} // namespace molphene

#endif

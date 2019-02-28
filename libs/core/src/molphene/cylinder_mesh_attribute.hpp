#ifndef MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP
#define MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP

#include "m3d.hpp"
#include "shape/cylinder.hpp"
#include "color_manager.hpp"

namespace molphene {

struct cylinder_mesh_attribute {
  rgba8 color;
  std::size_t index;
  vec2<double> texcoord;
  cylinder<double> cylinder;
};

struct bond_to_cylinder_attrs_options {
  bool is_first{true};
  double radius_size{1};
};

template<typename TSizeRange, typename TOutIter>
void transform_to_cylinder_attrs(const TSizeRange& bond_atoms,
                                 TOutIter output,
                                 bond_to_cylinder_attrs_options options)
{
  using float_type = double;
  using vec2f = vec2<float_type>;

  const auto col_manager = color_manager{};

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

    auto cyl = cylinder<float_type>{rad};
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

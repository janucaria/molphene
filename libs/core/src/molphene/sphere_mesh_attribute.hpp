#ifndef MOLPHENE_SPHERE_MESH_ATTRIBUTE_HPP
#define MOLPHENE_SPHERE_MESH_ATTRIBUTE_HPP

#include <molecule/atom_radius_kind.hpp>

#include "m3d.hpp"
#include "shape/sphere.hpp"
#include "color_manager.hpp"

namespace molphene {

struct sphere_mesh_attribute {
  rgba8 color;
  std::size_t index;
  vec2<double> texcoord;
  sphere<double> sphere;
};

struct atom_to_sphere_attrs_options {
  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};
  double radius_size{1};
};

template<typename TSizedRange, typename TOutIter>
void transform_to_sphere_attrs(const TSizedRange& atoms,
                               TOutIter output,
                               atom_to_sphere_attrs_options options)
{
  using float_type = double;
  using vec2f = vec2<float_type>;

  const auto col_manager = color_manager{};

  const auto tex_size =
   static_cast<std::size_t>(std::ceil(std::sqrt(atoms.size())));
  auto aindex = std::size_t{0};
  for(auto atomptr : atoms) {
    const auto& atom = *atomptr;
    const auto element = atom.element();
    const auto apos = atom.position();
    const auto arad = [&]() noexcept -> float_type {
      switch(options.radius_type) {
      case atom_radius_kind::van_der_waals:
        return element.rvdw;
      case atom_radius_kind::covalent:
        return element.rcov;
      default:
        return options.radius_size;
      }
    }();
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

} // namespace molphene
#endif
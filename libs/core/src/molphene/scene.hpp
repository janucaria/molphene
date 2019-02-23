#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include "stdafx.hpp"

#include <molecule/molecule.hpp>

#include "ballstick_representation.hpp"
#include "bounding_sphere.hpp"
#include "camera.hpp"
#include "color_light_buffer.hpp"
#include "cylinder_mesh_builder.hpp"
#include "directional_light.hpp"
#include "fog.hpp"
#include "m3d.hpp"
#include "material.hpp"
#include "molecule_display.hpp"
#include "point_light.hpp"
#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "spacefill_representation.hpp"
#include "sphere_mesh_builder.hpp"
#include "spot_light.hpp"
#include "sphere_mesh_attribute.hpp"
#include "cylinder_mesh_attribute.hpp"

namespace molphene {

class scene {
public:
  struct config_type {
    using float_type = double;
  };

  using float_type = typename type_configs<config_type>::float_type;
  using size_type = typename type_configs<config_type>::size_type;

  using vec3f = vec3<float_type>;
  using vec2f = vec2<float_type>;
  using mat4f = mat4<float_type>;
  using mat3f = mat3<float_type>;

  using bounding_sphere_type = bounding_sphere<float_type>;

  using camera = camera<config_type>;

  using fog_type = fog<rgba8, config_type>;

  using material_type = material<rgba8, config_type>;

  using directional_light = directional_light<rgba8, config_type>;

  using point_light = point_light<rgba8, config_type>;

  using spot_light = spot_light<rgba8, config_type>;

  using sphere_mesh_builder = sphere_mesh_builder<config_type>;

  using cylinder_mesh_builder = cylinder_mesh_builder<config_type>;

  using representation_variant =
   std::variant<spacefill_representation, ballstick_representation>;

  using representations_container = std::list<representation_variant>;

  using light_variant =
   std::variant<directional_light, point_light, spot_light>;

  auto setup_graphics() noexcept -> bool;

  void reset_mesh(const molecule& mol) noexcept;

  void reset_representation(const molecule& mol) noexcept;

  void rotate(vec3f rot) noexcept;

  auto model_matrix() const noexcept -> mat4f;

  auto light_source() const noexcept -> light_variant;

  auto material() const noexcept -> material_type;

  auto fog() const noexcept -> fog_type;

  void representation(molecule_display value, const molecule& mol);

  auto representations() const noexcept -> const representations_container&;

  auto bounding_sphere() const noexcept -> bounding_sphere_type;

  auto spacefill() noexcept -> spacefill_representation&;

  auto ballnstick() noexcept -> ballstick_representation&;

  auto build_sphere_mesh(const std::vector<sphere_mesh_attribute>& atoms)
   -> std::unique_ptr<color_light_buffer>;

  auto
  build_cylinder_mesh(const std::vector<cylinder_mesh_attribute>& cyl_attrs)
   -> std::unique_ptr<color_light_buffer>;

  template<typename Represent, typename InRange, typename OutIter>
  void transform_clylinder_attrs(bool is_first,
                                 const Represent& representation,
                                 const InRange& bond_atoms,
                                 OutIter output)

  {
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
      const auto acol1 = representation.atom_color(atom1);
      const auto acol2 = representation.atom_color(atom2);

      const auto atex = vec2f{float_type(aindex % tex_size),
                              std::floor(float_type(aindex) / tex_size)} /
                        tex_size;

      const auto rad = representation.radius_size;
      const auto midpos = (apos1 + apos2) * 0.5;

      auto cyl = cylinder<float_type>{rad};
      auto color = rgba8{};
      if(is_first) {
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

  template<typename Represent, typename InRange, typename OutIter>
  void transform_sphere_attrs(const Represent& representation,
                              const InRange& atoms,
                              OutIter output)
  {
    const auto tex_size =
     static_cast<std::size_t>(std::ceil(std::sqrt(atoms.size())));
    auto aindex = std::size_t{0};
    for(auto atomptr : atoms) {
      const auto& atom = *atomptr;
      const auto element = atom.element();
      const auto apos = atom.position();
      const auto arad = representation.atom_radius(element);
      const auto acol = representation.atom_color(atom);

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

private:
  molecule_display representation_{molecule_display::spacefill};

  representations_container representations_;

  light_variant light_source_;

  fog_type fog_;

  material_type material_;

  mat4f model_matrix_{1};

  bounding_sphere_type bounding_sphere_;
};

} // namespace molphene

#endif

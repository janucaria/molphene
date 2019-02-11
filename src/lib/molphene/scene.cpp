#include "stdafx.hpp"

#include <molecule/chemdoodle_json_parser.hpp>

#include "algorithm.hpp"
#include "color_manager.hpp"
#include "expand_iterator.hpp"
#include "m3d.hpp"
#include "scene.hpp"
#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "utility.hpp"

namespace molphene {

auto scene::setup_graphics() noexcept -> bool
{
  material_.diffuse_color = {0xFF, 0xFF, 0xFF};

  point_light_source_.location = {0, 0, -23};
  point_light_source_.radius = 5;

  spot_light_source_.location = {0, 0, -20};

  representations_.emplace_back(spacefill_representation{});
  representations_.emplace_back(ballstick_representation{});

  return true;
}

void scene::reset_mesh(const Molecule& mol) noexcept
{
  namespace range = boost::range;

  // calculate bounding sphere
  bounding_sphere_.reset();

  range::transform(
   mol.atoms(), expand_iterator{bounding_sphere_}, [
   ](auto atom) noexcept { return atom.position(); });

  model_matrix_.identity().translate(-bounding_sphere_.center());

  reset_representation(mol);
}

auto scene::build_sphere_mesh(
 const std::vector<sphere_mesh_attribute>& sph_attrs)
 -> std::unique_ptr<color_light_buffer>
{
  const auto total_instances = sph_attrs.size();
  auto mesh_builder = sphere_mesh_builder{10, 20};
  const auto vertices_per_instance = mesh_builder.vertices_size();

  auto sphere_buff_atoms =
   std::make_unique<color_light_buffer>(vertices_per_instance, total_instances);

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  constexpr auto bytes_per_vertex =
   sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
  const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
  const auto max_models =
   bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
  const auto instances_per_chunk = std::min(total_instances, max_models);
  const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

  const auto tex_size = sphere_buff_atoms->color_texture_size();
  auto colors = std::vector<rgba8>{};
  colors.reserve(tex_size * tex_size);

  auto chunk_count = size_t{0};
  for_each_slice(sph_attrs, instances_per_chunk, [&](auto sph_attrs_range) {
    const auto instances_size = boost::distance(sph_attrs_range);

    auto normals = std::vector<vec3<GLfloat>>{};
    auto positions = std::vector<vec3<GLfloat>>{};
    auto texcoords = std::vector<vec2<GLfloat>>{};

    positions.reserve(vertices_per_chunk);
    normals.reserve(vertices_per_chunk);
    texcoords.reserve(vertices_per_chunk);
    for(const auto& sph_attr : sph_attrs_range) {
      const auto acol = sph_attr.color;
      const auto atex = sph_attr.texcoord;
      const auto sph = sph_attr.sphere;

      colors.push_back(acol);

      mesh_builder.build_positions(sph, std::back_inserter(positions));
      mesh_builder.build_normals(std::back_inserter(normals));
      mesh_builder.build_texcoords(atex, std::back_inserter(texcoords));
    }

    sphere_buff_atoms->set_data(chunk_count * instances_per_chunk,
                                instances_size,
                                positions,
                                normals,
                                texcoords);
    ++chunk_count;
  });

  colors.resize(colors.capacity());
  sphere_buff_atoms->color_texture_image_data(colors.data());

  return sphere_buff_atoms;
}

auto scene::build_cylinder_mesh(
 const std::vector<cylinder_mesh_attribute>& cyl_attrs)
 -> std::unique_ptr<color_light_buffer>
{
  const auto total_instances = cyl_attrs.size();
  auto mesh_builder = cylinder_mesh_builder{20};
  const auto vertices_per_instance = mesh_builder.vertices_size();

  auto cyl_buff_bonds =
   std::make_unique<color_light_buffer>(vertices_per_instance, total_instances);

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  constexpr auto bytes_per_vertex =
   sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
  const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
  const auto max_models =
   bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
  const auto instances_per_chunk = std::min(total_instances, max_models);
  const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

  const auto tex_size = cyl_buff_bonds->color_texture_size();
  auto colors = std::vector<rgba8>{};
  colors.reserve(tex_size * tex_size);

  auto chunk_count = size_t{0};
  for_each_slice(cyl_attrs, instances_per_chunk, [&](auto cyl_attrs_range) {
    const auto instances_size = boost::distance(cyl_attrs_range);

    auto normals = std::vector<vec3<GLfloat>>{};
    auto positions = std::vector<vec3<GLfloat>>{};
    auto texcoords = std::vector<vec2<GLfloat>>{};

    positions.reserve(vertices_per_chunk);
    normals.reserve(vertices_per_chunk);
    texcoords.reserve(vertices_per_chunk);

    for(const auto& cyl_attr : cyl_attrs_range) {
      const auto acol = cyl_attr.color;
      const auto atex = cyl_attr.texcoord;
      const auto cyl = cyl_attr.cylinder;

      colors.push_back(acol);

      mesh_builder.build_positions(cyl, std::back_inserter(positions));
      mesh_builder.build_normals(cyl, std::back_inserter(normals));
      mesh_builder.build_texcoords(cyl, atex, std::back_inserter(texcoords));
    }

    cyl_buff_bonds->set_data(chunk_count * instances_per_chunk,
                             instances_size,
                             positions,
                             normals,
                             texcoords);
    ++chunk_count;
  });

  colors.resize(colors.capacity());
  cyl_buff_bonds->color_texture_image_data(colors.data());

  return cyl_buff_bonds;
}

void scene::rotate(scene::vec3f rot) noexcept
{
  model_matrix_.rotate(rot.x(), {1.0f, 0.0f, 0.0f});
  model_matrix_.rotate(rot.y(), {0.0f, 1.0f, 0.0f});
  model_matrix_.rotate(rot.z(), {0.0f, 0.0f, 1.0f});
}

auto scene::model_matrix() const noexcept -> mat4f
{
  return model_matrix_;
}

auto scene::light_source() const noexcept -> directional_light
{
  return light_source_;
}

auto scene::material() const noexcept -> material_type
{
  return material_;
}

auto scene::fog() const noexcept -> fog_type
{
  return fog_;
}

auto scene::bounding_sphere() const noexcept -> bounding_sphere_type
{
  return bounding_sphere_;
}

auto scene::spacefill() noexcept -> spacefill_representation&
{
  return *detail::attain<spacefill_representation>(&representations_.front());
}

auto scene::ballnstick() noexcept -> ballstick_representation&
{
  return *detail::attain<ballstick_representation>(&representations_.back());
}

void scene::representation(molecule_display value, const Molecule& mol)
{
  if(representation_ == value) {
    return;
  }

  representation_ = value;
  reset_representation(mol);
}

void scene::reset_representation(const Molecule& mol) noexcept
{
  namespace range = boost::range;

  representations_.clear();
  switch(representation_) {
  case molecule_display::spacefill: {
    using representation_t = spacefill_representation;

    auto atoms = std::vector<const Atom*>{};
    atoms.reserve(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    auto& rep_var = representations_.emplace_back(representation_t{});
    auto& spacefill = *detail::attain<representation_t>(&rep_var);

    auto sphere_mesh_attrs = std::vector<sphere_mesh_attribute>{};
    sphere_mesh_attrs.reserve(atoms.size());

    transform_sphere_attrs(
     spacefill, atoms, std::back_inserter(sphere_mesh_attrs));

    spacefill.atom_sphere_buffer = build_sphere_mesh(sphere_mesh_attrs);
  } break;
  case molecule_display::ball_and_stick: {
    using representation_t = ballstick_representation;

    auto atoms = std::vector<const Atom*>{};
    auto bonds = std::vector<const Bond*>{};
    using pair_atoms_t = std::pair<const Atom*, const Atom*>;
    auto bond_atoms = std::vector<pair_atoms_t>{};
    auto atoms_in_bond = std::vector<const Atom*>{};

    bonds.reserve(mol.bonds().size());
    range::transform(
     mol.bonds(), std::back_inserter(bonds), [](auto& bond) noexcept {
       return std::addressof(bond);
     });

    bond_atoms.reserve(bonds.size());
    range::transform(
     bonds,
     std::back_inserter(bond_atoms),
     [& atoms = mol.atoms()](auto bond) noexcept {
       return std::make_pair(&atoms.at(bond->atom1()),
                             &atoms.at(bond->atom2()));
     });

    atoms.reserve(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    atoms_in_bond.reserve(atoms.size());
    boost::algorithm::copy_if(
     atoms, std::back_inserter(atoms_in_bond), [&](auto* atom) {
       return boost::find_if(bond_atoms, [&](auto atom_pair) {
                return atom == atom_pair.first || atom == atom_pair.second;
              }) != std::end(bond_atoms);
     });
    atoms_in_bond.shrink_to_fit();

    auto& rep_var = representations_.emplace_back(representation_t{});
    auto& ballnstick = *detail::attain<representation_t>(&rep_var);
    {
      auto sphere_mesh_attrs = std::vector<sphere_mesh_attribute>{};
      sphere_mesh_attrs.reserve(atoms_in_bond.size());

      transform_sphere_attrs(
       ballnstick, atoms_in_bond, std::back_inserter(sphere_mesh_attrs));

      ballnstick.atom_sphere_buffer = build_sphere_mesh(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs = std::vector<cylinder_mesh_attribute>{};
    cylinder_mesh_attrs.reserve(bond_atoms.size());

    transform_clylinder_attrs(true,
                              ballnstick,
                              bond_atoms,
                              std::back_insert_iterator(cylinder_mesh_attrs));
    ballnstick.bond1_cylinder_buffer = build_cylinder_mesh(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    transform_clylinder_attrs(false,
                              ballnstick,
                              bond_atoms,
                              std::back_insert_iterator(cylinder_mesh_attrs));
    ballnstick.bond2_cylinder_buffer = build_cylinder_mesh(cylinder_mesh_attrs);
  } break;
  }
}

auto scene::representations() const noexcept -> const representations_container&
{
  return representations_;
}

} // namespace molphene

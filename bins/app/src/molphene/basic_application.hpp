#ifndef MOLPHENE_APP_APPLICATION_VIEW_HPP
#define MOLPHENE_APP_APPLICATION_VIEW_HPP

#include <sstream>
#include <string>
#include <utility>

#include <molecule/chemdoodle_json_parser.hpp>
#include <molecule/molecule.hpp>

#include <molphene/algorithm.hpp>
#include <molphene/gl_renderer.hpp>
#include <molphene/scene.hpp>

#include <molphene/ballstick_representation.hpp>
#include <molphene/molecule_display.hpp>
#include <molphene/spacefill_representation.hpp>

#include <molphene/io/click_state.hpp>

namespace molphene {

template<typename TApp>
class basic_application {
public:
  using representation_variant =
   std::variant<spacefill_representation, ballstick_representation>;

  using representations_container = std::list<representation_variant>;

  using sphere_mesh_builder = sphere_mesh_builder<void>;

  using cylinder_mesh_builder = cylinder_mesh_builder<void>;

  void setup()
  {
    static_cast<TApp*>(this)->init_context();

    representations_.emplace_back(spacefill_representation{});
    representations_.emplace_back(ballstick_representation{});

    scene.setup_graphics();
    renderer.init();

    const auto [width, height] = static_cast<TApp*>(this)->framebuffer_size();

    renderer.change_dimension(width, height);
    camera.aspect_ratio(width, height);
    camera.update_view_matrix();

    scene.reset_mesh(molecule);
    reset_representation(molecule);
  }

  void open_pdb_data(std::string pdbdata)
  {
    auto pdbstm = std::stringstream{pdbdata};
    molecule = chemdoodle_json_parser{}.parse(pdbstm);

    scene.reset_mesh(molecule);
    reset_representation(molecule);
    camera.top = scene.bounding_sphere().radius() + 2;
    camera.update_view_matrix();
  }

  void render_frame()
  {
    renderer.render(scene, camera, representations_);
  }

  void canvas_size_change_callback(int width, int height)
  {
    renderer.change_dimension(width, height);
    camera.aspect_ratio(width, height);
    camera.update_view_matrix();
  }

  void change_representation(int representation_type)
  {
    switch(representation_type) {
    case static_cast<int>(molecule_display::spacefill): {
      representation(molecule_display::spacefill, molecule);
    } break;
    case static_cast<int>(molecule_display::ball_and_stick): {
      representation(molecule_display::ball_and_stick, molecule);
    } break;
    }
  }

  void representation(molecule_display value, const molecule& mol)
  {
    if(representation_ == value) {
      return;
    }

    representation_ = value;
    reset_representation(mol);
  }

  template<typename TSphMeshSizedRange>
  auto build_sphere_mesh(const TSphMeshSizedRange& sph_attrs)
   -> std::unique_ptr<color_light_buffer>
  {
    const auto total_instances = sph_attrs.size();
    auto mesh_builder = sphere_mesh_builder{10, 20};
    const auto vertices_per_instance = mesh_builder.vertices_size();

    auto sphere_buff_atoms = std::make_unique<color_light_buffer>(
     vertices_per_instance, total_instances);

    constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
    constexpr auto bytes_per_vertex =
     sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
    const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
    const auto max_models =
     bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
    const auto instances_per_chunk = std::min(total_instances, max_models);
    const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

    const auto tex_size = sphere_buff_atoms->color_texture_size();
    auto colors = detail::make_reserved_vector<rgba8>(tex_size * tex_size);

    auto chunk_count = size_t{0};
    for_each_slice(sph_attrs, instances_per_chunk, [&](auto sph_attrs_range) {
      const auto instances_size = boost::distance(sph_attrs_range);

      auto normals =
       detail::make_reserved_vector<vec3<GLfloat>>(vertices_per_chunk);
      auto positions =
       detail::make_reserved_vector<vec3<GLfloat>>(vertices_per_chunk);
      auto texcoords =
       detail::make_reserved_vector<vec2<GLfloat>>(vertices_per_chunk);

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

  template<typename TCylMeshSizedRange>
  auto build_cylinder_mesh(const TCylMeshSizedRange& cyl_attrs)
   -> std::unique_ptr<color_light_buffer>
  {
    const auto total_instances = cyl_attrs.size();
    auto mesh_builder = cylinder_mesh_builder{20};
    const auto vertices_per_instance = mesh_builder.vertices_size();

    auto cyl_buff_bonds = std::make_unique<color_light_buffer>(
     vertices_per_instance, total_instances);

    constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
    constexpr auto bytes_per_vertex =
     sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
    const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
    const auto max_models =
     bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
    const auto instances_per_chunk = std::min(total_instances, max_models);
    const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

    const auto tex_size = cyl_buff_bonds->color_texture_size();
    auto colors = detail::make_reserved_vector<rgba8>(tex_size * tex_size);

    auto chunk_count = size_t{0};
    for_each_slice(cyl_attrs, instances_per_chunk, [&](auto cyl_attrs_range) {
      const auto instances_size = boost::distance(cyl_attrs_range);

      auto normals =
       detail::make_reserved_vector<vec3<GLfloat>>(vertices_per_chunk);
      auto positions =
       detail::make_reserved_vector<vec3<GLfloat>>(vertices_per_chunk);
      auto texcoords =
       detail::make_reserved_vector<vec2<GLfloat>>(vertices_per_chunk);

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

  void reset_representation(const molecule& mol) noexcept
  {
    namespace range = boost::range;

    representations_.clear();
    switch(representation_) {
    case molecule_display::spacefill: {
      using representation_t = spacefill_representation;

      auto atoms =
       detail::make_reserved_vector<const atom*>(mol.atoms().size());
      range::transform(
       mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
         return &atom;
       });

      auto& rep_var = representations_.emplace_back(representation_t{});
      auto& spacefill = *detail::attain<representation_t>(&rep_var);

      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(atoms.size());

      transform_to_sphere_attrs(atoms,
                                std::back_inserter(sphere_mesh_attrs),
                                {spacefill.radius_type, spacefill.radius_size});

      spacefill.atom_sphere_buffer = build_sphere_mesh(sphere_mesh_attrs);
    } break;
    case molecule_display::ball_and_stick: {
      using representation_t = ballstick_representation;

      auto bonds =
       detail::make_reserved_vector<const bond*>(mol.bonds().size());
      range::transform(
       mol.bonds(), std::back_inserter(bonds), [](auto& bond) noexcept {
         return std::addressof(bond);
       });

      using pair_atoms_t = std::pair<const atom*, const atom*>;
      auto bond_atoms =
       detail::make_reserved_vector<pair_atoms_t>(bonds.size());
      range::transform(
       bonds,
       std::back_inserter(bond_atoms),
       [& atoms = mol.atoms()](auto bond) noexcept {
         return std::make_pair(&atoms.at(bond->atom1()),
                               &atoms.at(bond->atom2()));
       });

      auto atoms =
       detail::make_reserved_vector<const atom*>(mol.atoms().size());
      range::transform(
       mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
         return &atom;
       });

      auto atoms_in_bond =
       detail::make_reserved_vector<const atom*>(atoms.size());
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
        auto sphere_mesh_attrs =
         detail::make_reserved_vector<sphere_mesh_attribute>(
          atoms_in_bond.size());

        transform_to_sphere_attrs(
         atoms_in_bond,
         std::back_inserter(sphere_mesh_attrs),
         {ballnstick.atom_radius_type, ballnstick.radius_size});

        ballnstick.atom_sphere_buffer = build_sphere_mesh(sphere_mesh_attrs);
      }

      auto cylinder_mesh_attrs =
       detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

      transform_to_cylinder_attrs(
       bond_atoms,
       std::back_insert_iterator(cylinder_mesh_attrs),
       ballnstick,
       true);
      ballnstick.bond1_cylinder_buffer =
       build_cylinder_mesh(cylinder_mesh_attrs);

      cylinder_mesh_attrs.clear();

      transform_to_cylinder_attrs(
       bond_atoms,
       std::back_insert_iterator(cylinder_mesh_attrs),
       ballnstick,
       false);
      ballnstick.bond2_cylinder_buffer =
       build_cylinder_mesh(cylinder_mesh_attrs);
    } break;
    }
  }

  void key_press_event(unsigned char charcode, int mods)
  {
    switch(charcode) {
    case 27:
      static_cast<TApp*>(this)->close_app();
      break;
    case 80:
    case 112:
      camera.projection_mode(true);
      break;
    case 79:
    case 111:
      camera.projection_mode(false);
      break;
    case 75:
    case 107:
      representation(molecule_display::spacefill, molecule);
      break;
    case 76:
    case 108:
      representation(molecule_display::ball_and_stick, molecule);
      break;
    }
  }

  void mouse_press_event(int button, int mods, int pos_x, int pos_y)
  {
    click_state.is_down = true;
    click_state.last_x = pos_x;
    click_state.last_y = pos_y;
  }

  void mouse_release_event(int button, int mods, int pos_x, int pos_y)
  {
    click_state.is_down = false;
    click_state.last_x = pos_x;
    click_state.last_y = pos_y;
  }

  void mouse_move_event(int pos_x, int pos_y)
  {
    if(click_state.is_down) {
      const auto delta_x = static_cast<double>(click_state.last_x) - pos_x;
      const auto delta_y = static_cast<double>(click_state.last_y) - pos_y;

      click_state.last_x = pos_x;
      click_state.last_y = pos_y;

      scene.rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
    }
  }

  void mouse_scroll_event(int offset_x, int offset_y)
  {
    offset_y > 0 ? camera.zoom_in() : camera.zoom_out();
  }

  void framebuffer_size_change_event(int width, int height)
  {
    renderer.change_dimension(width, height);
    camera.aspect_ratio(width, height);
    camera.update_view_matrix();
  }

protected:
  io::click_state click_state{false, 0, 0};

  scene scene{};

  gl_renderer renderer;

  scene::camera camera;

  molecule molecule;

  representations_container representations_;

  molecule_display representation_{molecule_display::spacefill};
};

} // namespace molphene

#endif

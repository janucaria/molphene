#ifndef MOLPHENE_APP_APPLICATION_VIEW_HPP
#define MOLPHENE_APP_APPLICATION_VIEW_HPP

#include <set>
#include <sstream>
#include <string>
#include <utility>

#include <molecule/chemdoodle_json_parser.hpp>
#include <molecule/molecule.hpp>

#include <molphene/algorithm.hpp>
#include <molphene/gl_renderer.hpp>
#include <molphene/scene.hpp>

#include <molphene/ballstick_representation.hpp>
#include <molphene/buffers_builder.hpp>
#include <molphene/camera.hpp>
#include <molphene/cylinder_mesh_builder.hpp>
#include <molphene/cylinder_vertex_buffers_batch.hpp>
#include <molphene/cylinder_vertex_buffers_instanced.hpp>
#include <molphene/drawable.hpp>
#include <molphene/instance_copy_builder.hpp>
#include <molphene/molecule_display.hpp>
#include <molphene/molecule_to_shape.hpp>
#include <molphene/spacefill_representation.hpp>
#include <molphene/sphere_mesh_builder.hpp>
#include <molphene/sphere_vertex_buffers_batch.hpp>
#include <molphene/sphere_vertex_buffers_instanced.hpp>

#include <molphene/io/click_state.hpp>

namespace molphene {

template<typename TApp>
class basic_application {
public:
  using camera_type = camera<void>;
  using scene_type = scene;

  using spacefill_representation =
   basic_spacefill_representation<sphere_vertex_buffers_batch>;

  using spacefill_representation_instanced =
   basic_spacefill_representation<sphere_vertex_buffers_instanced>;

  using ballstick_representation =
   basic_ballstick_representation<sphere_vertex_buffers_batch,
                                  cylinder_vertex_buffers_batch>;

  using ballstick_representation_instanced =
   basic_ballstick_representation<sphere_vertex_buffers_instanced,
                                  cylinder_vertex_buffers_instanced>;

  using representations_container = std::list<drawable>;

  static constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};

  static constexpr auto cyl_mesh_builder = cylinder_mesh_builder<20>{};

  static constexpr auto copy_builder = instance_copy_builder{};

  void setup()
  {
    static_cast<TApp*>(this)->init_context();

    representations_.emplace_back(spacefill_representation{});
    representations_.emplace_back(ballstick_representation{});
    representations_.emplace_back(spacefill_representation_instanced{});
    representations_.emplace_back(ballstick_representation_instanced{});

    scene_.setup_graphics();
    renderer_.init();

    const auto [width, height] = static_cast<TApp*>(this)->framebuffer_size();

    renderer_.change_dimension(width, height);
    camera_.aspect_ratio(width, height);
    camera_.update_view_matrix();

    scene_.reset_mesh(molecule_);

    // representation_ = molecule_display::ball_and_stick;
    // representation_ = molecule_display::spacefill_instance;
    // representation_ = molecule_display::spacefill;
    representation_ = molecule_display::ball_and_stick_instance;
    reset_representation(molecule_);
  }

  void open_pdb_data(std::string pdbdata)
  {
    auto pdbstm = std::stringstream{pdbdata};
    molecule_ = chemdoodle_json_parser{}.parse(pdbstm);

    scene_.reset_mesh(molecule_);
    reset_representation(molecule_);
    camera_.top(scene_.bounding_sphere().radius() + 2);
    camera_.update_view_matrix();
  }

  void render_frame()
  {
    renderer_.render(scene_, camera_, representations_);
  }

  void canvas_size_change_callback(int width, int height)
  {
    renderer_.change_dimension(width, height);
    camera_.aspect_ratio(width, height);
    camera_.update_view_matrix();
  }

  void change_representation(int representation_type)
  {
    switch(representation_type) {
    case static_cast<int>(molecule_display::spacefill): {
      representation(molecule_display::spacefill, molecule_);
    } break;
    case static_cast<int>(molecule_display::ball_and_stick): {
      representation(molecule_display::ball_and_stick, molecule_);
    } break;
    case static_cast<int>(molecule_display::spacefill_instance): {
      representation(molecule_display::spacefill_instance, molecule_);
    } break;
    case static_cast<int>(molecule_display::ball_and_stick_instance): {
      representation(molecule_display::ball_and_stick_instance, molecule_);
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

  template<typename TSizedRangeAtoms>
  auto build_spacefill_representation(TSizedRangeAtoms&& atoms) const
   -> spacefill_representation
  {
    auto spacefill = spacefill_representation{};

    spacefill.radius_size = 1;
    spacefill.radius_type = atom_radius_kind::van_der_waals;

    auto sphere_mesh_attrs =
     detail::make_reserved_vector<sphere_mesh_attribute>(atoms.size());

    atoms_to_sphere_attrs(std::forward<TSizedRangeAtoms>(atoms),
                          std::back_inserter(sphere_mesh_attrs),
                          {spacefill.radius_type, spacefill.radius_size, 1.});

    spacefill.atom_sphere_buffers.build_buffers(sphere_mesh_attrs);

    return spacefill;
  }

  template<typename TSizedRangeAtoms, typename TSizedRangeBonds>
  auto build_ballstick_representation(TSizedRangeAtoms&& atoms_in_bond,
                                      TSizedRangeBonds&& bond_atoms)
   -> ballstick_representation
  {
    auto ballnstick = ballstick_representation{};
    {
      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(
        atoms_in_bond.size());

      atoms_to_sphere_attrs(
       std::forward<TSizedRangeAtoms>(atoms_in_bond),
       std::back_inserter(sphere_mesh_attrs),
       {ballnstick.atom_radius_type, ballnstick.atom_radius_size, 0.5});

      ballnstick.atom_sphere_buffers.build_buffers(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs =
     detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

    bonds_to_cylinder_attrs(std::forward<TSizedRangeBonds>(bond_atoms),
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {true, ballnstick.radius_size});

    ballnstick.bond1_cylinder_buffers.build_buffers(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {false, ballnstick.radius_size});

    ballnstick.bond2_cylinder_buffers.build_buffers(cylinder_mesh_attrs);

    return ballnstick;
  }

  template<typename TSizedRangeAtoms>
  auto build_spacefill_representation_instanced(TSizedRangeAtoms&& atoms) const
   -> spacefill_representation_instanced
  {
    auto spacefill = spacefill_representation_instanced{};

    auto sphere_mesh_attrs =
     detail::make_reserved_vector<sphere_mesh_attribute>(atoms.size());

    atoms_to_sphere_attrs(std::forward<TSizedRangeAtoms>(atoms),
                          std::back_inserter(sphere_mesh_attrs),
                          {spacefill.radius_type, spacefill.radius_size, 1.});

    spacefill.atom_sphere_buffers.build_buffers(sphere_mesh_attrs);

    return spacefill;
  }

  template<typename TSizedRangeAtoms, typename TSizedRangeBonds>
  auto build_ballstick_instance_representation(TSizedRangeAtoms&& atoms_in_bond,
                                               TSizedRangeBonds&& bond_atoms)
   -> ballstick_representation_instanced
  {
    auto ballnstick = ballstick_representation_instanced{};
    {
      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(
        atoms_in_bond.size());

      atoms_to_sphere_attrs(
       std::forward<TSizedRangeAtoms>(atoms_in_bond),
       std::back_inserter(sphere_mesh_attrs),
       {ballnstick.atom_radius_type, ballnstick.atom_radius_size, 0.5});

      ballnstick.atom_sphere_buffers.build_buffers(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs =
     detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

    bonds_to_cylinder_attrs(std::forward<TSizedRangeBonds>(bond_atoms),
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {true, ballnstick.radius_size});

    ballnstick.bond1_cylinder_buffers.build_buffers(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {false, ballnstick.radius_size});

    ballnstick.bond2_cylinder_buffers.build_buffers(cylinder_mesh_attrs);

    return ballnstick;
  }

  void reset_representation(const molecule& mol) noexcept
  {
    namespace range = boost::range;

    representations_.clear();

    const auto atoms = [&]() {
      auto atoms =
       detail::make_reserved_vector<const atom*>(mol.atoms().size());
      range::transform(
       mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
         return &atom;
       });
      return atoms;
    }();

    const auto bond_atoms = [&]() {
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

      return bond_atoms;
    }();

    const auto atoms_in_bond = [&]() {
      auto atoms_in_bond = std::set<const atom*>{};

      boost::for_each(
       bond_atoms, [&](auto atom_pair) noexcept {
         atoms_in_bond.insert({atom_pair.first, atom_pair.second});
       });

      return atoms_in_bond;
    }();

    switch(representation_) {
    case molecule_display::spacefill: {
      representations_.emplace_back(build_spacefill_representation(atoms));
    } break;
    case molecule_display::ball_and_stick: {
      representations_.emplace_back(
       build_ballstick_representation(atoms_in_bond, bond_atoms));
    } break;
    case molecule_display::spacefill_instance: {
      representations_.emplace_back(
       build_spacefill_representation_instanced(atoms));
    } break;
    case molecule_display::ball_and_stick_instance: {
      representations_.emplace_back(
       build_ballstick_instance_representation(atoms_in_bond, bond_atoms));
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
      camera_.projection_mode(true);
      break;
    case 79:
    case 111:
      camera_.projection_mode(false);
      break;
    case 72:
    case 104:
      representation(molecule_display::ball_and_stick_instance, molecule_);
      break;
    case 74:
    case 106:
      representation(molecule_display::spacefill_instance, molecule_);
      break;
    case 75:
    case 107:
      representation(molecule_display::spacefill, molecule_);
      break;
    case 76:
    case 108:
      representation(molecule_display::ball_and_stick, molecule_);
      break;
    }
  }

  void mouse_press_event(int button, int mods, int pos_x, int pos_y)
  {
    click_state_.is_down = true;
    click_state_.last_x = pos_x;
    click_state_.last_y = pos_y;
  }

  void mouse_release_event(int button, int mods, int pos_x, int pos_y)
  {
    click_state_.is_down = false;
    click_state_.last_x = pos_x;
    click_state_.last_y = pos_y;
  }

  void mouse_move_event(int pos_x, int pos_y)
  {
    if(click_state_.is_down) {
      const auto delta_x = static_cast<double>(click_state_.last_x) - pos_x;
      const auto delta_y = static_cast<double>(click_state_.last_y) - pos_y;

      click_state_.last_x = pos_x;
      click_state_.last_y = pos_y;

      scene_.rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
    }
  }

  void mouse_scroll_event(int offset_x, int offset_y)
  {
    offset_y > 0 ? camera_.zoom_in() : camera_.zoom_out();
  }

  void framebuffer_size_change_event(int width, int height)
  {
    renderer_.change_dimension(width, height);
    camera_.aspect_ratio(width, height);
    camera_.update_view_matrix();
  }

  auto click_state() noexcept -> io::click_state&
  {
    return click_state_;
  }

  auto scene() noexcept -> scene_type&
  {
    return scene_;
  }

private:
  io::click_state click_state_{false, 0, 0};

  scene_type scene_{};

  gl_renderer renderer_;

  camera_type camera_;

  molecule molecule_;

  representations_container representations_;

  molecule_display representation_{molecule_display::spacefill};
};

} // namespace molphene

#endif

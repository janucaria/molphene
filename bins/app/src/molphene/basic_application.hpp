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

  void setup()
  {
    static_cast<TApp*>(this)->init_context();

    representations_.emplace_back(spacefill_representation{});
    representations_.emplace_back(ballstick_representation{});
    representations_.emplace_back(spacefill_representation_instanced{});
    representations_.emplace_back(ballstick_representation_instanced{});

    scene.setup_graphics();
    renderer.init();

    const auto [width, height] = static_cast<TApp*>(this)->framebuffer_size();

    renderer.change_dimension(width, height);
    camera.aspect_ratio(width, height);
    camera.update_view_matrix();

    scene.reset_mesh(molecule);

    // representation_ = molecule_display::ball_and_stick;
    // representation_ = molecule_display::spacefill_instance;
    // representation_ = molecule_display::spacefill;
    representation_ = molecule_display::ball_and_stick_instance;
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
    case static_cast<int>(molecule_display::spacefill_instance): {
      representation(molecule_display::spacefill_instance, molecule);
    } break;
    case static_cast<int>(molecule_display::ball_and_stick_instance): {
      representation(molecule_display::ball_and_stick_instance, molecule);
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

  template<typename TMeshSizedRange>
  auto build_shape_color_texture(TMeshSizedRange&& shape_attrs) const
   -> std::unique_ptr<color_image_texture>
  {
    const auto total_instances =
     std::forward<TMeshSizedRange>(shape_attrs).size();
    auto shape_color_texture =
     std::make_unique<color_image_texture>(total_instances);

    const auto tex_size = shape_color_texture->size();
    auto colors = detail::make_reserved_vector<rgba8>(tex_size * tex_size);

    boost::range::transform(
     std::forward<TMeshSizedRange>(shape_attrs), std::back_inserter(colors), [
     ](auto attr) noexcept { return attr.color; });

    colors.resize(colors.capacity());
    shape_color_texture->image_data(colors.data());

    return shape_color_texture;
  }

  template<typename TOutputVertexBuffer,
           typename TMeshBuilder,
           typename TShapeMeshSizedRange,
           typename TFunction>
  auto build_mesh_vertices(TMeshBuilder mesh_builder,
                           TShapeMeshSizedRange&& shape_attrs,
                           TFunction callable_fn) const
   -> std::unique_ptr<TOutputVertexBuffer>
  {
    using vertex_buffer_array_t = TOutputVertexBuffer;
    using shape_attrs_container_t = TShapeMeshSizedRange;

    constexpr auto vertices_per_instance = mesh_builder.vertices_size();
    constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
    constexpr auto bytes_per_vertex =
     sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
    constexpr auto bytes_per_instance =
     bytes_per_vertex * vertices_per_instance;
    constexpr auto max_instances_per_chunk =
     bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
    const auto total_instances =
     std::forward<shape_attrs_container_t>(shape_attrs).size();
    const auto instances_per_chunk =
     std::min(total_instances, max_instances_per_chunk);
    const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

    auto shape_buff_atoms = std::make_unique<vertex_buffer_array_t>(
     vertices_per_instance, total_instances, max_instances_per_chunk);

    auto chunk_count = size_t{0};
    for_each_slice(
     std::forward<shape_attrs_container_t>(shape_attrs),
     instances_per_chunk,
     [&](auto shape_attrs_range) {
       const auto instances_size = boost::distance(shape_attrs_range);

       using vertex_data_t = typename vertex_buffer_array_t::data_type;
       auto vertices =
        detail::make_reserved_vector<vertex_data_t>(vertices_per_chunk);

       boost::for_each(
        shape_attrs_range, [&](auto shape_attr) noexcept {
          mesh_builder.build(callable_fn(shape_attr),
                             std::back_inserter(vertices));
        });

       shape_buff_atoms->subdata(chunk_count * instances_per_chunk,
                                 instances_size,
                                 gsl::span(vertices.data(), vertices.size()));

       ++chunk_count;
     });

    return shape_buff_atoms;
  }

  template<typename TMeshBuilder, typename TSphMeshSizedRange>
  auto
  build_sphere_mesh_transform_instances(TMeshBuilder mesh_builder,
                                        TSphMeshSizedRange&& sph_attrs) const
   -> std::unique_ptr<transforms_instances_buffer_array>
  {
    return build_mesh_vertices<transforms_instances_buffer_array>(
     mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
     ](auto sph_attr) noexcept {
       auto transform_mat = mat4<float>{1};
       transform_mat.scale(sph_attr.sphere.radius);
       transform_mat.translate(sph_attr.sphere.center);
       return transform_mat;
     });
  }

  template<typename TMeshBuilder, typename TSphMeshSizedRange>
  auto
  build_sphere_mesh_texcoord_instances(TMeshBuilder mesh_builder,
                                       TSphMeshSizedRange&& sph_attrs) const
   -> std::unique_ptr<texcoords_instances_buffer_array>
  {
    return build_mesh_vertices<texcoords_instances_buffer_array>(
     mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
     ](auto sph_attr) noexcept { return sph_attr.texcoord; });
  }

  template<typename TMeshBuilder, typename TSphMeshSizedRange>
  auto build_sphere_mesh_positions(TMeshBuilder mesh_builder,
                                   TSphMeshSizedRange&& sph_attrs) const
   -> std::unique_ptr<positions_buffer_array>
  {
    return build_mesh_vertices<positions_buffer_array>(
     mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
     ](auto sph_attr) noexcept {
       return build_sphere_mesh_position_params{sph_attr.sphere};
     });
  }

  template<typename TMeshBuilder, typename TSphMeshSizedRange>
  auto build_sphere_mesh_normals(TMeshBuilder mesh_builder,
                                 TSphMeshSizedRange&& sph_attrs) const
   -> std::unique_ptr<normals_buffer_array>
  {
    return build_mesh_vertices<normals_buffer_array>(
     mesh_builder, sph_attrs, [](auto) noexcept {
       return build_sphere_mesh_normal_params{};
     });
  }

  template<typename TMeshBuilder, typename TSphMeshSizedRange>
  auto build_sphere_mesh_texcoords(TMeshBuilder mesh_builder,
                                   TSphMeshSizedRange&& sph_attrs) const
   -> std::unique_ptr<texcoords_buffer_array>
  {
    return build_mesh_vertices<texcoords_buffer_array>(
     mesh_builder, sph_attrs, [](auto sph_attr) noexcept {
       return build_sphere_mesh_fill_params{sph_attr.texcoord};
     });
  }

  template<typename TMeshBuilder, typename TCylMeshSizedRange>
  auto build_cylinder_mesh_positions(TMeshBuilder mesh_builder,
                                     TCylMeshSizedRange&& cyl_attrs) const
   -> std::unique_ptr<positions_buffer_array>
  {
    return build_mesh_vertices<positions_buffer_array>(
     mesh_builder, std::forward<TCylMeshSizedRange>(cyl_attrs), [
     ](auto cyl_attr) noexcept {
       return build_cylinder_mesh_position_params{cyl_attr.cylinder};
     });
  }

  template<typename TMeshBuilder, typename TCylMeshSizedRange>
  auto build_cylinder_mesh_normals(TMeshBuilder mesh_builder,
                                   TCylMeshSizedRange&& cyl_attrs) const
   -> std::unique_ptr<normals_buffer_array>
  {
    return build_mesh_vertices<normals_buffer_array>(
     mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
       return build_cylinder_mesh_normal_params{cyl_attr.cylinder};
     });
  }

  template<typename TMeshBuilder, typename TCylMeshSizedRange>
  auto build_cylinder_mesh_texcoords(TMeshBuilder mesh_builder,
                                     TCylMeshSizedRange&& cyl_attrs) const
   -> std::unique_ptr<texcoords_buffer_array>
  {
    return build_mesh_vertices<texcoords_buffer_array>(
     mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
       return build_cylinder_mesh_fill_params{cyl_attr.cylinder,
                                              cyl_attr.texcoord};
     });
  }

  template<typename TMeshBuilder, typename TCylMeshSizedRange>
  auto
  build_cylinder_mesh_transform_instances(TMeshBuilder mesh_builder,
                                          TCylMeshSizedRange&& cyl_attrs) const
   -> std::unique_ptr<transforms_instances_buffer_array>
  {
    return build_mesh_vertices<transforms_instances_buffer_array>(
     mesh_builder, std::forward<TCylMeshSizedRange>(cyl_attrs), [
     ](auto cyl_attr) noexcept {
       using vec3_t =
        typename std::decay_t<decltype(cyl_attr.cylinder)>::vec3_type;

       auto transform_mat = mat4<float>{1};

       const auto top_dir = vec3_t{0, 1, 0};
       const auto cyl_dir =
        (cyl_attr.cylinder.top - cyl_attr.cylinder.bottom) / 2;
       const auto cyl_dir_length = cyl_dir.magnitude();
       const auto rot_axis = cyl_dir.cross(top_dir).to_unit();
       const auto rot_angle = std::acos(cyl_dir.dot(top_dir) / cyl_dir_length);
       const auto cyl_radius = cyl_attr.cylinder.radius;
       const auto cyl_position = cyl_attr.cylinder.bottom + cyl_dir;

       transform_mat.scale(cyl_radius, cyl_dir_length, cyl_radius);
       transform_mat.rotate(rot_angle, rot_axis);
       transform_mat.translate(cyl_position);

       return transform_mat;
     });
  }

  template<typename TMeshBuilder, typename TCylMeshSizedRange>
  auto
  build_cylinder_mesh_texcoord_instances(TMeshBuilder mesh_builder,
                                         TCylMeshSizedRange&& cyl_attrs) const
   -> std::unique_ptr<texcoords_instances_buffer_array>
  {
    return build_mesh_vertices<texcoords_instances_buffer_array>(
     mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
       return cyl_attr.texcoord;
     });
  }

  auto build_spacefill_representation(const molecule& mol) const
   -> spacefill_representation
  {
    namespace range = boost::range;

    auto spacefill = spacefill_representation{};

    constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};

    auto atoms = detail::make_reserved_vector<const atom*>(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    auto sphere_mesh_attrs =
     detail::make_reserved_vector<sphere_mesh_attribute>(atoms.size());

    atoms_to_sphere_attrs(atoms,
                          std::back_inserter(sphere_mesh_attrs),
                          {spacefill.radius_type, spacefill.radius_size, 1.});

    spacefill.atom_sphere_buffers.buffer_positions =
     build_sphere_mesh_positions(sph_mesh_builder, sphere_mesh_attrs);

    spacefill.atom_sphere_buffers.buffer_normals =
     build_sphere_mesh_normals(sph_mesh_builder, sphere_mesh_attrs);

    spacefill.atom_sphere_buffers.buffer_texcoords =
     build_sphere_mesh_texcoords(sph_mesh_builder, sphere_mesh_attrs);

    spacefill.atom_sphere_buffers.color_texture =
     build_shape_color_texture(sphere_mesh_attrs);

    return spacefill;
  }

  auto build_ballstick_representation(const molecule& mol)
   -> ballstick_representation
  {
    namespace range = boost::range;

    auto ballnstick = ballstick_representation{};

    constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};
    constexpr auto cyl_mesh_builder = cylinder_mesh_builder<20>{};

    auto bonds = detail::make_reserved_vector<const bond*>(mol.bonds().size());
    range::transform(
     mol.bonds(), std::back_inserter(bonds), [](auto& bond) noexcept {
       return std::addressof(bond);
     });

    using pair_atoms_t = std::pair<const atom*, const atom*>;
    auto bond_atoms = detail::make_reserved_vector<pair_atoms_t>(bonds.size());
    range::transform(
     bonds,
     std::back_inserter(bond_atoms),
     [& atoms = mol.atoms()](auto bond) noexcept {
       return std::make_pair(&atoms.at(bond->atom1()),
                             &atoms.at(bond->atom2()));
     });

    auto atoms = detail::make_reserved_vector<const atom*>(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    auto atoms_in_bond = std::set<const atom*>{};
    boost::for_each(
     bond_atoms, [&](auto atom_pair) noexcept {
       atoms_in_bond.insert({atom_pair.first, atom_pair.second});
     });

    {
      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(
        atoms_in_bond.size());

      atoms_to_sphere_attrs(
       atoms_in_bond,
       std::back_inserter(sphere_mesh_attrs),
       {ballnstick.atom_radius_type, ballnstick.atom_radius_size, 0.5});

      ballnstick.atom_sphere_buffers.buffer_positions =
       build_sphere_mesh_positions(sph_mesh_builder, sphere_mesh_attrs);

      ballnstick.atom_sphere_buffers.buffer_normals =
       build_sphere_mesh_normals(sph_mesh_builder, sphere_mesh_attrs);

      ballnstick.atom_sphere_buffers.buffer_texcoords =
       build_sphere_mesh_texcoords(sph_mesh_builder, sphere_mesh_attrs);

      ballnstick.atom_sphere_buffers.color_texture =
       build_shape_color_texture(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs =
     detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {true, ballnstick.radius_size});

    ballnstick.bond1_cylinder_buffers.buffer_positions =
     build_cylinder_mesh_positions(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond1_cylinder_buffers.buffer_normals =
     build_cylinder_mesh_normals(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond1_cylinder_buffers.buffer_texcoords =
     build_cylinder_mesh_texcoords(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond1_cylinder_buffers.color_texture =
     build_shape_color_texture(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {false, ballnstick.radius_size});

    ballnstick.bond2_cylinder_buffers.buffer_positions =
     build_cylinder_mesh_positions(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond2_cylinder_buffers.buffer_normals =
     build_cylinder_mesh_normals(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond2_cylinder_buffers.buffer_texcoords =
     build_cylinder_mesh_texcoords(cyl_mesh_builder, cylinder_mesh_attrs);

    ballnstick.bond2_cylinder_buffers.color_texture =
     build_shape_color_texture(cylinder_mesh_attrs);

    return ballnstick;
  }

  auto build_spacefill_representation_instanced(const molecule& mol) const
   -> spacefill_representation_instanced
  {
    namespace range = boost::range;

    auto spacefill = spacefill_representation_instanced{};

    constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};

    constexpr auto copy_builder = instance_copy_builder{};

    auto atoms = detail::make_reserved_vector<const atom*>(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    auto sphere_mesh_attrs =
     detail::make_reserved_vector<sphere_mesh_attribute>(atoms.size());

    atoms_to_sphere_attrs(atoms,
                          std::back_inserter(sphere_mesh_attrs),
                          {spacefill.radius_type, spacefill.radius_size, 1.});

    const auto sphere_attr = std::array<sphere_mesh_attribute, 1>{};

    spacefill.atom_sphere_buffers.buffer_positions =
     build_sphere_mesh_positions(sph_mesh_builder, sphere_attr);

    spacefill.atom_sphere_buffers.buffer_normals =
     build_sphere_mesh_normals(sph_mesh_builder, sphere_attr);

    spacefill.atom_sphere_buffers.buffer_texcoords =
     build_sphere_mesh_texcoord_instances(copy_builder, sphere_mesh_attrs);

    spacefill.atom_sphere_buffers.buffer_transforms =
     build_sphere_mesh_transform_instances(copy_builder, sphere_mesh_attrs);

    spacefill.atom_sphere_buffers.color_texture =
     build_shape_color_texture(sphere_mesh_attrs);

    return spacefill;
  }

  auto build_ballstick_instance_representation(const molecule& mol)
   -> ballstick_representation_instanced
  {
    namespace range = boost::range;

    auto ballnstick = ballstick_representation_instanced{};

    constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};
    constexpr auto cyl_mesh_builder = cylinder_mesh_builder<20>{};
    constexpr auto copy_builder = instance_copy_builder{};

    auto bonds = detail::make_reserved_vector<const bond*>(mol.bonds().size());
    range::transform(
     mol.bonds(), std::back_inserter(bonds), [](auto& bond) noexcept {
       return std::addressof(bond);
     });

    using pair_atoms_t = std::pair<const atom*, const atom*>;
    auto bond_atoms = detail::make_reserved_vector<pair_atoms_t>(bonds.size());
    range::transform(
     bonds,
     std::back_inserter(bond_atoms),
     [& atoms = mol.atoms()](auto bond) noexcept {
       return std::make_pair(&atoms.at(bond->atom1()),
                             &atoms.at(bond->atom2()));
     });

    auto atoms = detail::make_reserved_vector<const atom*>(mol.atoms().size());
    range::transform(
     mol.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
       return &atom;
     });

    auto atoms_in_bond = std::set<const atom*>{};
    boost::for_each(
     bond_atoms, [&](auto atom_pair) noexcept {
       atoms_in_bond.insert({atom_pair.first, atom_pair.second});
     });

    {
      auto sphere_mesh_attrs =
       detail::make_reserved_vector<sphere_mesh_attribute>(
        atoms_in_bond.size());

      atoms_to_sphere_attrs(
       atoms_in_bond,
       std::back_inserter(sphere_mesh_attrs),
       {ballnstick.atom_radius_type, ballnstick.atom_radius_size, 0.5});

      const auto sphere_attr = std::array<sphere_mesh_attribute, 1>{};

      ballnstick.atom_sphere_buffers.buffer_positions =
       build_sphere_mesh_positions(sph_mesh_builder, sphere_attr);

      ballnstick.atom_sphere_buffers.buffer_normals =
       build_sphere_mesh_normals(sph_mesh_builder, sphere_attr);

      ballnstick.atom_sphere_buffers.buffer_texcoords =
       build_sphere_mesh_texcoord_instances(copy_builder, sphere_mesh_attrs);

      ballnstick.atom_sphere_buffers.buffer_transforms =
       build_sphere_mesh_transform_instances(copy_builder, sphere_mesh_attrs);

      ballnstick.atom_sphere_buffers.color_texture =
       build_shape_color_texture(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs =
     detail::make_reserved_vector<cylinder_mesh_attribute>(bond_atoms.size());

    const auto cylinder_attr = std::array<cylinder_mesh_attribute, 1>{};

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {true, ballnstick.radius_size});

    ballnstick.bond1_cylinder_buffers.buffer_positions =
     build_cylinder_mesh_positions(cyl_mesh_builder, cylinder_attr);

    ballnstick.bond1_cylinder_buffers.buffer_normals =
     build_cylinder_mesh_normals(cyl_mesh_builder, cylinder_attr);

    ballnstick.bond1_cylinder_buffers.buffer_texcoords =
     build_cylinder_mesh_texcoord_instances(copy_builder, cylinder_mesh_attrs);

    ballnstick.bond1_cylinder_buffers.buffer_transforms =
     build_cylinder_mesh_transform_instances(copy_builder, cylinder_mesh_attrs);

    ballnstick.bond1_cylinder_buffers.color_texture =
     build_shape_color_texture(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    bonds_to_cylinder_attrs(bond_atoms,
                            std::back_insert_iterator(cylinder_mesh_attrs),
                            {false, ballnstick.radius_size});

    ballnstick.bond2_cylinder_buffers.buffer_positions =
     build_cylinder_mesh_positions(cyl_mesh_builder, cylinder_attr);

    ballnstick.bond2_cylinder_buffers.buffer_normals =
     build_cylinder_mesh_normals(cyl_mesh_builder, cylinder_attr);

    ballnstick.bond2_cylinder_buffers.buffer_texcoords =
     build_cylinder_mesh_texcoord_instances(copy_builder, cylinder_mesh_attrs);

    ballnstick.bond2_cylinder_buffers.buffer_transforms =
     build_cylinder_mesh_transform_instances(copy_builder, cylinder_mesh_attrs);

    ballnstick.bond2_cylinder_buffers.color_texture =
     build_shape_color_texture(cylinder_mesh_attrs);

    return ballnstick;
  }

  void reset_representation(const molecule& mol) noexcept
  {
    representations_.clear();
    switch(representation_) {
    case molecule_display::spacefill: {
      representations_.emplace_back(build_spacefill_representation(mol));
    } break;
    case molecule_display::ball_and_stick: {
      representations_.emplace_back(build_ballstick_representation(mol));
    } break;
    case molecule_display::spacefill_instance: {
      representations_.emplace_back(
       build_spacefill_representation_instanced(mol));
    } break;
    case molecule_display::ball_and_stick_instance: {
      representations_.emplace_back(
       build_ballstick_instance_representation(mol));
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
    case 72:
    case 104:
      representation(molecule_display::ball_and_stick_instance, molecule);
      break;
    case 74:
    case 106:
      representation(molecule_display::spacefill_instance, molecule);
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

  camera_type camera;

  molecule molecule;

  representations_container representations_;

  molecule_display representation_{molecule_display::spacefill};
};

} // namespace molphene

#endif

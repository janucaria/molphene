#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include <fstream>
#include <istream>
#include <memory>

#include "Bounding_sphere.hpp"
#include "Camera.hpp"
#include "Color_light_buffer.hpp"
#include "Color_light_shader.hpp"
#include "Colour_manager.hpp"
#include "Directional_light.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "m3d.hpp"
#include "mol/Atom.hpp"
#include "mol/Bond.hpp"
#include "mol/Model.hpp"
#include "mol/Molecule.hpp"
#include "mol/Pdb_parser.hpp"
#include "Point_light.hpp"
#include "opengl.hpp"

namespace molphene {

class Scene {
public:
  using Camera_type = Camera<float, unsigned int>;

  using Material_type = Material<Rgba8>;

  using Light_source_type = Directional_light<Rgba8, Vec3f>;

  using Point_light_type = Point_light<Rgba8, Vec3f>;

  using Fog_type = Fog<Rgba8>;

  bool
  setup_graphics();

  void
  reset_mesh();

  void
  change_dimension(GLsizei width, GLsizei height);

  void
  render_frame();

  void
  rotate(float x, float y, float z);

  void
  open_stream(std::istream& is);

  void
  calculate_matrices();

  Camera_type&
  get_camera();

private:
  std::unique_ptr<Color_light_buffer> sphere_buff_atoms_;

  Color_light_shader color_light_shader_;

  Light_source_type light_source_;

  Point_light_type point_light_source_;

  Fog_type fog_;

  Material_type material_;

  Mat4f model_matrix_;

  Camera_type camera_;

  std::unique_ptr<Molecule> molecule_;

  Colour_manager colour_manager_;

  GLuint atom_color_tex_{0};
};

} // namespace molphene

#endif

#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include "stdafx.hpp"

#include "BoundingSphere.hpp"
#include "Camera.hpp"
#include "ColorLightBuffer.hpp"
#include "ColorLightShader.hpp"
#include "ColourManager.hpp"
#include "DirectionalLight.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "m3d.hpp"
#include "mol/Atom.hpp"
#include "mol/Bond.hpp"
#include "mol/Model.hpp"
#include "mol/Molecule.hpp"
#include "mol/PdbParser.hpp"
#include "opengl.hpp"

namespace molphene {

class Scene {
public:
  using Camera_type = Camera<float>;

  using Fog_type = Fog<Rgba8>;

  using Light_source_type = DirectionalLight<Rgba8, Vec3f>;

  using Material_type = Material<Rgba8>;

  using PointLight_type = PointLight<Rgba8, Vec3f>;

  using SpotLight_type = SpotLight<Rgba8, Vec3f>;

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
  std::unique_ptr<ColorLightBuffer> sphere_buff_atoms_;

  ColorLightShader color_light_shader_;

  Light_source_type light_source_;

  PointLight_type point_light_source_;

  SpotLight_type spot_light_source_;

  Fog_type fog_;

  Material_type material_;

  Mat4f model_matrix_{1};

  Camera_type camera_;

  std::unique_ptr<Molecule> molecule_;

  ColourManager colour_manager_;

  GLuint atom_color_tex_{0};
};

} // namespace molphene

#endif

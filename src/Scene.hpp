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
  using Camera = Camera<float>;

  using Fog = Fog<Rgba8>;

  using Light_source = DirectionalLight<Rgba8, Vec3f>;

  using Material = Material<Rgba8>;

  using PointLight = PointLight<Rgba8, Vec3f>;

  using SpotLight = SpotLight<Rgba8, Vec3f>;

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

  Camera&
  get_camera();

private:
  std::unique_ptr<ColorLightBuffer> sphere_buff_atoms_;

  ColorLightShader color_light_shader_;

  Light_source light_source_;

  PointLight point_light_source_;

  SpotLight spot_light_source_;

  Fog fog_;

  Material material_;

  Mat4f model_matrix_{1};

  Camera camera_;

  std::unique_ptr<Molecule> molecule_;

  ColourManager colour_manager_;

  GLuint atom_color_tex_{0};
};

} // namespace molphene

#endif

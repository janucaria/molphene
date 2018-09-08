#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include "stdafx.hpp"

#include "BoundingSphere.hpp"
#include "Camera.hpp"
#include "ColorLightBuffer.hpp"
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
#include "GlRenderer.hpp"
#include "SphereMeshBuilder.hpp"

namespace molphene {

class Scene {
public:
  struct ConfigType {
    using float_type = double;
  };

  using float_t = typename type_configs<ConfigType>::float_type;
  using size_t = typename type_configs<ConfigType>::size_type;

  using Vec3f = Vec3<float_t>;
  using Vec2f = Vec2<float_t>;
  using Mat4f = Mat4<float_t>;
  using Mat3f = Mat3<float_t>;

  using Camera = Camera<ConfigType>;

  using Fog = Fog<Rgba8, ConfigType>;

  using Material = Material<Rgba8, ConfigType>;

  using Light_source = DirectionalLight<Rgba8, ConfigType>;

  using PointLight = PointLight<Rgba8, ConfigType>;

  using SpotLight = SpotLight<Rgba8, ConfigType>;

  using SphereMeshBuilder = SphereMeshBuilder<ConfigType>;

  using Renderer = GlRenderer<>;

  friend Renderer;

  bool
  setup_graphics();

  void
  reset_mesh();

  void
  change_dimension(GLsizei width, GLsizei height);

  void
  render_frame();

  void
  rotate(Vec3f rot);

  void
  open_stream(std::istream& is);

  void
  calculate_matrices();

  Camera&
  get_camera();

private:
  std::unique_ptr<ColorLightBuffer> sphere_buff_atoms_;

  Light_source light_source_;

  PointLight point_light_source_;

  SpotLight spot_light_source_;

  Fog fog_;

  Material material_;

  Mat4f model_matrix_{1};

  Camera camera_;

  std::unique_ptr<Molecule> molecule_;

  ColourManager colour_manager_;

  Renderer renderer;
};

} // namespace molphene

#endif

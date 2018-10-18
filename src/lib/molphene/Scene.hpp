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
#include "SphereMeshBuilder.hpp"
#include "SpotLight.hpp"
#include "Viewport.hpp"
#include "m3d.hpp"
#include "mol/Atom.hpp"
#include "mol/Bond.hpp"
#include "mol/Model.hpp"
#include "mol/Molecule.hpp"
#include "mol/PdbParser.hpp"

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

  using BoundingSphere = BoundingSphere<float_t>;

  using Camera = Camera<ConfigType>;

  using Fog = Fog<Rgba8, ConfigType>;

  using Material = Material<Rgba8, ConfigType>;

  using LightSource = DirectionalLight<Rgba8, ConfigType>;

  using PointLight = PointLight<Rgba8, ConfigType>;

  using SpotLight = SpotLight<Rgba8, ConfigType>;

  using SphereMeshBuilder = SphereMeshBuilder<ConfigType>;

  using Viewport = Viewport<size_t, float_t>;

  bool
  setup_graphics() noexcept;

  void
  reset_mesh() noexcept;

  void
  change_dimension(size_t width, size_t height) noexcept;

  void
  rotate(Vec3f rot) noexcept;

  void
  open_stream(std::istream& is);

  Mat4f
  model_matrix() const noexcept;

  LightSource
  light_source() const noexcept;

  Material
  material() const noexcept;

  Fog
  fog() const noexcept;

  Viewport
  viewport() const noexcept;

  const ColorLightBuffer*
  mesh_buffers() const noexcept;

  BoundingSphere
  bounding_sphere() const noexcept;

private:
  std::unique_ptr<ColorLightBuffer> sphere_buff_atoms_;

  LightSource light_source_;

  PointLight point_light_source_;

  SpotLight spot_light_source_;

  Fog fog_;

  Material material_;

  Viewport viewport_;

  Mat4f model_matrix_ {1};

  BoundingSphere bounding_sphere_;

  std::unique_ptr<Molecule> molecule_;

  ColourManager colour_manager_;
};

} // namespace molphene

#endif

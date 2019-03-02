#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include "stdafx.hpp"

#include <molecule/molecule.hpp>

#include "ballstick_representation.hpp"
#include "bounding_sphere.hpp"
#include "camera.hpp"
#include "color_light_buffer.hpp"
#include "cylinder_mesh_attribute.hpp"
#include "cylinder_mesh_builder.hpp"
#include "directional_light.hpp"
#include "fog.hpp"
#include "m3d.hpp"
#include "material.hpp"
#include "point_light.hpp"
#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "spacefill_representation.hpp"
#include "sphere_mesh_attribute.hpp"
#include "spot_light.hpp"
#include "utility.hpp"

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

  using representation_variant =
   std::variant<spacefill_representation, ballstick_representation>;

  using representations_container = std::list<representation_variant>;

  using light_variant =
   std::variant<directional_light, point_light, spot_light>;

  auto setup_graphics() noexcept -> bool;

  void reset_mesh(const molecule& mol) noexcept;

  void rotate(vec3f rot) noexcept;

  auto model_matrix() const noexcept -> mat4f;

  auto light_source() const noexcept -> light_variant;

  auto material() const noexcept -> material_type;

  auto fog() const noexcept -> fog_type;

  auto bounding_sphere() const noexcept -> bounding_sphere_type;

private:
  light_variant light_source_;

  fog_type fog_;

  material_type material_;

  mat4f model_matrix_{1};

  bounding_sphere_type bounding_sphere_;
};

} // namespace molphene

#endif

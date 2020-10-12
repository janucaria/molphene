#ifndef MOLPHENE_SCENE_HPP
#define MOLPHENE_SCENE_HPP

#include "stdafx.hpp"

#include <molecule/chemdoodle_json_parser.hpp>
#include <molecule/molecule.hpp>

#include "algorithm.hpp"
#include "ballstick_representation.hpp"
#include "bounding_sphere.hpp"
#include "cylinder_mesh_attribute.hpp"
#include "directional_light.hpp"
#include "expand_iterator.hpp"
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

template<typename TConfig = void>
class basic_scene {
public:
  using config_type = TConfig;

  using float_type = typename type_configs<config_type>::float_type;
  using size_type = typename type_configs<config_type>::size_type;

  using vec3f = vec3<float_type>;
  using vec2f = vec2<float_type>;
  using mat4f = mat4<float_type>;
  using mat3f = mat3<float_type>;

  using bounding_sphere_type = BoundingSphere<float_type>;

  using fog_type = Fog<rgba8, config_type>;

  using material_type = Material<rgba8, config_type>;

  using directional_light = DirectionalLight<rgba8, config_type>;

  using point_light = PointLight<rgba8, config_type>;

  using spot_light = SpotLight<rgba8, config_type>;

  using light_variant =
   std::variant<directional_light, point_light, spot_light>;

  auto setup_graphics() noexcept -> bool
  {
    material_.diffuse_color = {0xFF, 0xFF, 0xFF};

    light_source_.template emplace<directional_light>();

    return true;
  }

  void reset_mesh(const molecule& mol) noexcept
  {
    namespace range = boost::range;

    // calculate bounding sphere
    bounding_sphere_.reset();
    range::transform(
     mol.atoms(), expand_iterator{bounding_sphere_}, [](auto atom) noexcept {
       return atom.position();
     });

    model_matrix_.identity().translate(-bounding_sphere_.center());
  }

  void rotate(vec3f rot) noexcept
  {
    model_matrix_.rotate({1.0f, 0.0f, 0.0f}, rot.x());
    model_matrix_.rotate({0.0f, 1.0f, 0.0f}, rot.y());
    model_matrix_.rotate({0.0f, 0.0f, 1.0f}, rot.z());
  }

  auto model_matrix() const noexcept -> mat4f
  {
    return model_matrix_;
  }

  auto light_source() const noexcept -> light_variant
  {
    return light_source_;
  }

  auto material() const noexcept -> material_type
  {
    return material_;
  }

  auto fog() const noexcept -> fog_type
  {
    return fog_;
  }

  auto bounding_sphere() const noexcept -> bounding_sphere_type
  {
    return bounding_sphere_;
  }

private:
  light_variant light_source_;

  fog_type fog_;

  material_type material_;

  mat4f model_matrix_{1};

  bounding_sphere_type bounding_sphere_;
};

using Scene = basic_scene<void>;

} // namespace molphene

#endif

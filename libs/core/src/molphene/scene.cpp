#include "stdafx.hpp"

#include <molecule/chemdoodle_json_parser.hpp>

#include "algorithm.hpp"
#include "color_manager.hpp"
#include "expand_iterator.hpp"
#include "m3d.hpp"
#include "scene.hpp"
#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "utility.hpp"

namespace molphene {

auto scene::setup_graphics() noexcept -> bool
{
  material_.diffuse_color = {0xFF, 0xFF, 0xFF};

  light_source_.emplace<directional_light>();

  return true;
}

void scene::reset_mesh(const molecule& mol) noexcept
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

void scene::rotate(scene::vec3f rot) noexcept
{
  model_matrix_.rotate(rot.x(), {1.0f, 0.0f, 0.0f});
  model_matrix_.rotate(rot.y(), {0.0f, 1.0f, 0.0f});
  model_matrix_.rotate(rot.z(), {0.0f, 0.0f, 1.0f});
}

auto scene::model_matrix() const noexcept -> mat4f
{
  return model_matrix_;
}

auto scene::light_source() const noexcept -> light_variant
{
  return light_source_;
}

auto scene::material() const noexcept -> material_type
{
  return material_;
}

auto scene::fog() const noexcept -> fog_type
{
  return fog_;
}

auto scene::bounding_sphere() const noexcept -> bounding_sphere_type
{
  return bounding_sphere_;
}

} // namespace molphene

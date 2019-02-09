#ifndef MOLPHENE_M3D_HPP
#define MOLPHENE_M3D_HPP

#include "stdafx.hpp"
#include <molecule/m3d.hpp>

namespace molphene {

template<typename T>
using mat3 = gm3d::Mat3<T>;

template<typename T>
using mat4 = gm3d::Mat4<T>;

template<typename T>
using vec2 = gm3d::Vec2<T>;

template<typename T>
using vec3 = gm3d::Vec3<T>;

using rgba8 = gm3d::Rgba<std::uint8_t>;

using rgba32f = gm3d::Rgba<float>;

} // namespace molphene

#endif

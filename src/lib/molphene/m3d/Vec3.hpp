#ifndef MOLPHENE_M3D_VEC3_HPP
#define MOLPHENE_M3D_VEC3_HPP

#include "../stdafx.hpp"

namespace molphene {

template<typename T>
struct Vec3 {
  T x, y, z;

  Vec3() noexcept = default;

  explicit Vec3(T s) noexcept
  : Vec3{s, s, s}
  {
  }

  Vec3(T x, T y, T z) noexcept
  : x{x}
  , y{y}
  , z{z}
  {
  }

  Vec3&
  operator+=(const Vec3& rhs) noexcept
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vec3&
  operator+=(T rhs) noexcept
  {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
  }

  Vec3&
  operator-=(const Vec3& rhs) noexcept
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vec3&
  operator-=(T rhs) noexcept
  {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
  }

  Vec3&
  operator*=(const Vec3& rhs) noexcept
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }

  Vec3&
  operator*=(T rhs) noexcept
  {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  Vec3&
  operator/=(const Vec3& rhs) noexcept
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
  }

  Vec3&
  operator/=(T rhs) noexcept
  {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  T
  dot(const Vec3& other) const noexcept
  {
    return x * other.x + y * other.y + z * other.z;
  }

  T
  magnitude() const noexcept
  {
    return std::sqrt(dot(*this));
  }

  T
  magnitude_squared() const noexcept
  {
    return dot(*this);
  }

  Vec3
  to_unit() const noexcept
  {
    return *this / magnitude();
  }

  Vec3
  cross(const Vec3& other) const noexcept
  {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
  }
};

template<typename T>
bool
operator==(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template<typename T>
bool
operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return !(lhs == rhs);
}

template<typename T>
Vec3<T>
operator+(const Vec3<T>& val) noexcept
{
  return val;
}

template<typename T>
Vec3<T>
operator+(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template<typename T>
Vec3<T>
operator+(const Vec3<T>& lhs, std::common_type_t<T> rhs) noexcept
{
  return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

template<typename T>
Vec3<T>
operator-(const Vec3<T>& lhs) noexcept
{
  return {-lhs.x, -lhs.y, -lhs.z};
}

template<typename T>
Vec3<T>
operator-(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T>
Vec3<T>
operator-(const Vec3<T>& lhs, std::common_type_t<T> rhs) noexcept
{
  return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
}

template<typename T>
Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template<typename T>
Vec3<T> operator*(const Vec3<T>& lhs, std::common_type_t<T> rhs) noexcept
{
  return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

template<typename T>
Vec3<T>
operator/(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept
{
  return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template<typename T>
Vec3<T>
operator/(const Vec3<T>& lhs, std::common_type_t<T> rhs) noexcept
{
  return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

} // namespace molphene

#endif

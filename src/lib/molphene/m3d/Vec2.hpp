#ifndef MOLPHENE_M3D_VEC2_HPP
#define MOLPHENE_M3D_VEC2_HPP

#include "../stdafx.hpp"

namespace molphene {

template<typename T>
struct Vec2 {
  T x, y;

  Vec2() noexcept = default;

  explicit Vec2(T s) noexcept
  : Vec2{s, s}
  {
  }

  Vec2(T x, T y) noexcept
  : x{x}
  , y{y}
  {
  }

  Vec2
  operator+(const Vec2& v) const noexcept
  {
    return Vec2{*this} += v;
  }

  Vec2&
  operator+=(const Vec2& v) noexcept
  {
    this->x += v.x;
    this->y += v.y;
    return *this;
  }

  Vec2
  operator-(const Vec2& v) const noexcept
  {
    return Vec2{*this} -= v;
  }

  Vec2&
  operator-=(const Vec2& v) noexcept
  {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
  }

  Vec2 operator*(const Vec2& v) const noexcept
  {
    return Vec2{*this} *= v;
  }

  Vec2&
  operator*=(const Vec2& v) noexcept
  {
    this->x *= v.x;
    this->y *= v.y;
    return *this;
  }

  Vec2
  operator/(const Vec2& v) const noexcept
  {
    return Vec2{*this} /= v;
  }

  Vec2&
  operator/=(const Vec2& v) noexcept
  {
    this->x /= v.x;
    this->y /= v.y;
    return *this;
  }

  Vec2
  operator-() const noexcept
  {
    return {-this->x, -this->y};
  }

  Vec2
  operator+(const T& s) const noexcept
  {
    return Vec2{*this} += s;
  }

  Vec2&
  operator+=(const T& s) noexcept
  {
    this->x += s;
    this->y += s;
    return *this;
  }

  Vec2
  operator-(const T& s) const noexcept
  {
    return Vec2{*this} -= s;
  }

  Vec2&
  operator-=(const T& s) noexcept
  {
    this->x -= s;
    this->y -= s;
    return *this;
  }

  Vec2 operator*(const T& s) const noexcept
  {
    return Vec2{*this} *= s;
  }

  Vec2&
  operator*=(const T& s) noexcept
  {
    this->x *= s;
    this->y *= s;
    return *this;
  }

  Vec2
  operator/(const T& s) const noexcept
  {
    return Vec2{*this} /= s;
  }

  Vec2&
  operator/=(const T& s) noexcept
  {
    this->x /= s;
    this->y /= s;
    return *this;
  }

  T
  magnitude() const noexcept
  {
    return sqrt(x * x + y * y);
  }

  Vec2
  to_unit() noexcept
  {
    return *this / magnitude();
  }
};

} // namespace molphene

#endif

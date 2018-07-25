#ifndef MOLPHENE_M3D_VEC2_HPP
#define MOLPHENE_M3D_VEC2_HPP

#include <cmath>

namespace molphene {

template<typename T>
struct Vec2 {
  T x{0}, y{0};

  Vec2() = default;

  Vec2(T x, T y)
  : x{x}
  , y{y}
  {
  }

  Vec2<T>&
  operator()(const T& x, const T& y)
  {
    this->x = x;
    this->y = y;
    return *this;
  }

  Vec2
  operator+(const Vec2& v) const
  {
    return Vec2{*this} += v;
  }

  Vec2&
  operator+=(const Vec2& v)
  {
    this->x += v.x;
    this->y += v.y;
    return *this;
  }

  Vec2
  operator-(const Vec2& v) const
  {
    return Vec2{*this} -= v;
  }

  Vec2&
  operator-=(const Vec2& v)
  {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
  }

  Vec2 operator*(const Vec2& v) const
  {
    return Vec2{*this} *= v;
  }

  Vec2&
  operator*=(const Vec2& v)
  {
    this->x *= v.x;
    this->y *= v.y;
    return *this;
  }

  Vec2
  operator/(const Vec2& v) const
  {
    return Vec2{*this} /= v;
  }

  Vec2&
  operator/=(const Vec2& v)
  {
    this->x /= v.x;
    this->y /= v.y;
    return *this;
  }

  Vec2
  operator-() const
  {
    return {-this->x, -this->y};
  }

  Vec2
  operator+(const T& s) const
  {
    return Vec2{*this} += s;
  }

  Vec2&
  operator+=(const T& s)
  {
    this->x += s;
    this->y += s;
    return *this;
  }

  Vec2
  operator-(const T& s) const
  {
    return Vec2{*this} -= s;
  }

  Vec2&
  operator-=(const T& s)
  {
    this->x -= s;
    this->y -= s;
    return *this;
  }

  Vec2 operator*(const T& s) const
  {
    return Vec2{*this} *= s;
  }

  Vec2&
  operator*=(const T& s)
  {
    this->x *= s;
    this->y *= s;
    return *this;
  }

  Vec2
  operator/(const T& s) const
  {
    return Vec2{*this} /= s;
  }

  Vec2&
  operator/=(const T& s)
  {
    this->x /= s;
    this->y /= s;
    return *this;
  }

  T
  magnitude() const
  {
    return sqrt(x * x + y * y);
  }

  Vec2
  to_unit()
  {
    return *this / magnitude();
  }
};

} // namespace molphene

#endif

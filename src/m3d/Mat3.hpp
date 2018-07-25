#ifndef MOLPHENE_M3D_MAT3_HPP
#define MOLPHENE_M3D_MAT3_HPP

#include "Mat4.hpp"

namespace molphene {
template<typename T>
struct Mat3 {
  T m[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};

  Mat3() noexcept = default;

  Mat3(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33) noexcept
  : m{m11, m12, m13, m21, m22, m23, m31, m32, m33}
  {
  }

  explicit Mat3(const Mat4<T>& m4) noexcept
  : Mat3(m4.m[0],
         m4.m[1],
         m4.m[2],
         m4.m[4],
         m4.m[5],
         m4.m[6],
         m4.m[8],
         m4.m[9],
         m4.m[10])
  {
  }

  Mat3&
  operator()(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33) noexcept
  {
    m[0] = m11;
    m[1] = m12;
    m[2] = m13;

    m[3] = m21;
    m[4] = m22;
    m[5] = m23;

    m[6] = m31;
    m[7] = m32;
    m[8] = m33;

    return *this;
  }

  Mat3&
  zero() noexcept
  {
    return (*this)(0, 0, 0, 0, 0, 0, 0, 0, 0);
  }
};

} // namespace molphene

#endif

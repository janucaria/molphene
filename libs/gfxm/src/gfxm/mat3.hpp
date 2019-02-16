#ifndef MOLPHENE_M3D_MAT3_HPP
#define MOLPHENE_M3D_MAT3_HPP

#include <boost/qvm/all.hpp>

#include "mat4.hpp"

namespace molphene {
template<typename T>
struct mat3 {
  T m[9];

  mat3() noexcept = default;

  explicit mat3(T s) noexcept
  : mat3{s, 0, 0, 0, s, 0, 0, 0, s}
  {
  }

  mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
  : m{m00, m01, m02, m10, m11, m12, m20, m21, m22}
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit mat3(const mat4<U>& m4) noexcept
  : mat3(m4.m[0],
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

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  mat3(const mat4<U>& m4) noexcept
  : mat3(m4.m[0],
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

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit mat3(const mat3<U>& m3) noexcept
  : mat3(m3.m[0],
         m3.m[1],
         m3.m[2],
         m3.m[3],
         m3.m[4],
         m3.m[5],
         m3.m[6],
         m3.m[7],
         m3.m[8])
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  mat3(const mat3<U>& m3) noexcept
  : mat3(m3.m[0],
         m3.m[1],
         m3.m[2],
         m3.m[3],
         m3.m[4],
         m3.m[5],
         m3.m[6],
         m3.m[7],
         m3.m[8])
  {
  }

  void m00(T val) noexcept
  {
    m[0] = val;
  }

  void m01(T val) noexcept
  {
    m[1] = val;
  }

  void m02(T val) noexcept
  {
    m[2] = val;
  }

  void m10(T val) noexcept
  {
    m[3] = val;
  }

  void m11(T val) noexcept
  {
    m[4] = val;
  }

  void m12(T val) noexcept
  {
    m[5] = val;
  }

  void m20(T val) noexcept
  {
    m[6] = val;
  }

  void m21(T val) noexcept
  {
    m[7] = val;
  }

  void m22(T val) noexcept
  {
    m[8] = val;
  }

  auto m00() const noexcept -> T
  {
    return m[0];
  }

  auto m01() const noexcept -> T
  {
    return m[1];
  }

  auto m02() const noexcept -> T
  {
    return m[2];
  }

  auto m10() const noexcept -> T
  {
    return m[3];
  }

  auto m11() const noexcept -> T
  {
    return m[4];
  }

  auto m12() const noexcept -> T
  {
    return m[5];
  }

  auto m20() const noexcept -> T
  {
    return m[6];
  }

  auto m21() const noexcept -> T
  {
    return m[7];
  }

  auto m22() const noexcept -> T
  {
    return m[8];
  }
};

} // namespace molphene

namespace boost::qvm {

template<class T>
struct mat_traits<molphene::mat3<T>> {
  using scalar_type = T;
  static int const rows = 3;
  static int const cols = 3;

  template<int Row, int Col>
  static scalar_type read_element(molphene::mat3<T> const& x)
  {
    return x.m[Row * 3 + Col];
  }

  template<int Row, int Col>
  static scalar_type& write_element(molphene::mat3<T>& x)
  {
    return x.m[Row * 3 + Col];
  }

  static scalar_type
  read_element_idx(int row, int col, molphene::mat3<T> const& x)
  {
    return x.m[row * 3 + col];
  }

  static scalar_type& write_element_idx(int row, int col, molphene::mat3<T>& x)
  {
    return x.m[row * 3 + col];
  }
};
} // namespace boost::qvm

#endif

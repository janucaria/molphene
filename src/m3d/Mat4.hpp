#ifndef MOLPHENE_M3D_MAT4_HPP
#define MOLPHENE_M3D_MAT4_HPP

#include "stdafx.hpp"

#include "Vec2.hpp"
#include "Vec3.hpp"

namespace molphene {

template<typename T>
struct Mat4 {
  T m[16];

  Mat4() noexcept = default;

  explicit Mat4(T s) noexcept
  : Mat4{s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, s}
  {
  }

  Mat4(T m11,
       T m12,
       T m13,
       T m14,
       T m21,
       T m22,
       T m23,
       T m24,
       T m31,
       T m32,
       T m33,
       T m34,
       T m41,
       T m42,
       T m43,
       T m44) noexcept
  : m{m11,
      m12,
      m13,
      m14,
      m21,
      m22,
      m23,
      m24,
      m31,
      m32,
      m33,
      m34,
      m41,
      m42,
      m43,
      m44}
  {
  }

  Mat4&
  operator()(T m11,
             T m12,
             T m13,
             T m14,
             T m21,
             T m22,
             T m23,
             T m24,
             T m31,
             T m32,
             T m33,
             T m34,
             T m41,
             T m42,
             T m43,
             T m44) noexcept
  {
    m[0] = m11;
    m[1] = m12;
    m[2] = m13;
    m[3] = m14;

    m[4] = m21;
    m[5] = m22;
    m[6] = m23;
    m[7] = m24;

    m[8] = m31;
    m[9] = m32;
    m[10] = m33;
    m[11] = m34;

    m[12] = m41;
    m[13] = m42;
    m[14] = m43;
    m[15] = m44;
    return *this;
  }

  Mat4&
  operator*=(const Mat4& m4) noexcept
  {
    const auto m11 = m[0], m12 = m[1], m13 = m[2], m14 = m[3], m21 = m[4],
               m22 = m[5], m23 = m[6], m24 = m[7], m31 = m[8], m32 = m[9],
               m33 = m[10], m34 = m[11], m41 = m[12], m42 = m[13], m43 = m[14],
               m44 = m[15];

    const auto n11 = m4.m[0], n12 = m4.m[1], n13 = m4.m[2], n14 = m4.m[3],
               n21 = m4.m[4], n22 = m4.m[5], n23 = m4.m[6], n24 = m4.m[7],
               n31 = m4.m[8], n32 = m4.m[9], n33 = m4.m[10], n34 = m4.m[11],
               n41 = m4.m[12], n42 = m4.m[13], n43 = m4.m[14], n44 = m4.m[15];

    return (*this)(m11 * n11 + m12 * n21 + m13 * n31 + m14 * n41,
                   m11 * n12 + m12 * n22 + m13 * n32 + m14 * n42,
                   m11 * n13 + m12 * n23 + m13 * n33 + m14 * n43,
                   m11 * n14 + m12 * n24 + m13 * n34 + m14 * n44,

                   m21 * n11 + m22 * n21 + m23 * n31 + m24 * n41,
                   m21 * n12 + m22 * n22 + m23 * n32 + m24 * n42,
                   m21 * n13 + m22 * n23 + m23 * n33 + m24 * n43,
                   m21 * n14 + m22 * n24 + m23 * n34 + m24 * n44,

                   m31 * n11 + m32 * n21 + m33 * n31 + m34 * n41,
                   m31 * n12 + m32 * n22 + m33 * n32 + m34 * n42,
                   m31 * n13 + m32 * n23 + m33 * n33 + m34 * n43,
                   m31 * n14 + m32 * n24 + m33 * n34 + m34 * n44,

                   m41 * n11 + m42 * n21 + m43 * n31 + m44 * n41,
                   m41 * n12 + m42 * n22 + m43 * n32 + m44 * n42,
                   m41 * n13 + m42 * n23 + m43 * n33 + m44 * n43,
                   m41 * n14 + m42 * n24 + m43 * n34 + m44 * n44);
  }

  Mat4 operator*(const Mat4& m4) const noexcept
  {
    return Mat4(*this) *= m4;
  }

  Mat4&
  operator/=(const T& s) noexcept
  {
    m[0] /= s;
    m[1] /= s;
    m[2] /= s;
    m[3] /= s;
    m[4] /= s;
    m[5] /= s;
    m[6] /= s;
    m[7] /= s;
    m[8] /= s;
    m[9] /= s;
    m[10] /= s;
    m[11] /= s;
    m[12] /= s;
    m[13] /= s;
    m[14] /= s;
    m[15] /= s;

    return *this;
  }

  Mat4
  operator/(const T& s) const noexcept
  {
    return Mat4(*this) /= s;
  }

  Mat4&
  scale(const T& s) noexcept
  {
    return scale(s, s, s);
  }

  Mat4&
  scale(const T& x, const T& y, const T& z) noexcept
  {
    m[0] *= x;
    m[5] *= y;
    m[10] *= z;
    return *this;
  }

  Mat4&
  identity() noexcept
  {
    return (*this)(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  }

  Mat4&
  scale(const Vec3<T>& v) noexcept
  {
    return scale(v.x, v.y, v.z);
  }

  Mat4&
  rotate(T x, T y, T z, T a) noexcept
  {
    // zero rotation is nothing
    if(!a) {
      return *this;
    }

    const auto l = sqrt(x * x + y * y + z * z);

    if(l == 0) {
      x = 0;
      y = 0;
      z = 1;
    } else if(l != 1) {
      x /= l;
      y /= l;
      z /= l;
    }

    const auto m11 = m[0], m12 = m[1], m13 = m[2], m14 = m[3], m21 = m[4],
               m22 = m[5], m23 = m[6], m24 = m[7], m31 = m[8], m32 = m[9],
               m33 = m[10], m34 = m[11], m41 = m[12], m42 = m[13], m43 = m[14],
               m44 = m[15];

    const auto s = sinf(a);
    const auto c = cosf(a);
    const auto t = T{1} - c;
    const auto xx = x * x;
    const auto xy = x * y;
    const auto yy = y * y;
    const auto yz = y * z;
    const auto zz = z * z;
    const auto zx = z * x;

    const auto n11 = c + t * xx;
    const auto n12 = t * xy + s * z;
    const auto n13 = t * zx - s * y;

    const auto n21 = t * xy - s * z;
    const auto n22 = c + t * yy;
    const auto n23 = t * yz + s * x;

    const auto n31 = t * zx + s * y;
    const auto n32 = t * yz - s * x;
    const auto n33 = c + t * zz;

    return (*this)(m11 * n11 + m12 * n21 + m13 * n31,
                   m11 * n12 + m12 * n22 + m13 * n32,
                   m11 * n13 + m12 * n23 + m13 * n33,
                   m14,

                   m21 * n11 + m22 * n21 + m23 * n31,
                   m21 * n12 + m22 * n22 + m23 * n32,
                   m21 * n13 + m22 * n23 + m23 * n33,
                   m24,

                   m31 * n11 + m32 * n21 + m33 * n31,
                   m31 * n12 + m32 * n22 + m33 * n32,
                   m31 * n13 + m32 * n23 + m33 * n33,
                   m34,

                   m41 * n11 + m42 * n21 + m43 * n31,
                   m41 * n12 + m42 * n22 + m43 * n32,
                   m41 * n13 + m42 * n23 + m43 * n33,
                   m44);
  }

  Mat4&
  translate(T x, T y, T z) noexcept
  {
    const auto m14 = m[3];
    const auto m24 = m[7];
    const auto m34 = m[11];
    const auto m44 = m[15];

    m[0] += m14 * x;
    m[4] += m24 * x;
    m[8] += m34 * x;
    m[12] += m44 * x;

    m[1] += m14 * y;
    m[5] += m24 * y;
    m[9] += m34 * y;
    m[13] += m44 * y;

    m[2] += m14 * z;
    m[6] += m24 * z;
    m[10] += m34 * z;
    m[14] += m44 * z;

    return *this;
  }

  Mat4&
  translate(const Vec3<T>& v) noexcept
  {
    return translate(v.x, v.y, v.z);
  }

  Mat4&
  set_translate(T x, T y, T z) noexcept
  {
    m[12] = x;
    m[13] = y;
    m[14] = z;

    return *this;
  }

  Mat4&
  set_translate(Vec3<T> v) noexcept
  {
    return set_translate(v.x, v.y, v.z);
  }

  Mat4&
  frustum(T l, T r, T b, T t, T n, T f) noexcept
  {
    m[0] = 2 * n / (r - l);
    m[5] = 2 * n / (t - b);
    m[8] = (r + l) / (r - l);
    m[9] = (t + b) / (t - b);
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[12] = m[13] = m[15] = 0;
    m[11] = -1;

    if(std::isfinite(f)) {
      m[10] = -(f + n) / (f - n);
      m[14] = -(2 * f * n) / (f - n);
    } else {
      m[10] = -1;
      m[14] = -2 * n;
    }

    return *this;
  }

  Mat4&
  orthogonal(T l, T r, T b, T t, T n, T f) noexcept
  {
    m[0] = 2 / (r - l);
    m[5] = 2 / (t - b);
    m[10] = -2 / (f - n);
    m[11] = 0;
    m[12] = -(l + r) / (r - l);
    m[13] = -(t + b) / (t - b);
    m[14] = -(f + n) / (f - n);
    m[15] = 1;
    m[6] = m[7] = m[8] = m[9] = m[1] = m[2] = m[3] = m[4] = 0;

    return *this;
  }

  Mat4&
  lookat(T ex, T ey, T ez, T lx, T ly, T lz, T ux, T uy, T uz) noexcept
  {
    auto fx = ex - lx;
    auto fy = ey - ly;
    auto fz = ez - lz;
    const auto fl = sqrt(fx * fx + fy * fy + fz * fz);
    fx /= fl;
    fy /= fl;
    fz /= fl;

    const auto ul = sqrt(ux * ux + uy * uy + uz * uz);
    ux /= ul;
    uy /= ul;
    uz /= ul;

    const auto rx = uy * fz - uz * fy;
    const auto ry = uz * fx - ux * fz;
    const auto rz = ux * fy - uy * fx;

    ux = fy * rz - fz * ry;
    uy = fz * rx - fx * rz;
    uz = fx * ry - fy * rx;

    m[0] = rx;
    m[1] = ux;
    m[2] = fx;
    m[3] = 0;

    m[4] = ry;
    m[5] = uy;
    m[6] = fy;
    m[7] = 0;

    m[8] = rz;
    m[9] = uz;
    m[10] = fz;
    m[11] = 0;

    m[12] = -(rx * ex + ry * ey + rz * ez);
    m[13] = -(ux * ex + uy * ey + uz * ez);
    m[14] = -(fx * ex + fy * ey + fz * ez);
    m[15] = 1;
    return *this;
  }

  Mat4&
  lookat(Vec3<T> e, Vec3<T> l, Vec3<T> u) noexcept
  {
    return lookat(e.x, e.y, e.z, l.x, l.y, l.z, u.x, u.y, u.z);
  }

  Mat4&
  perspective(T fov, T a, T n, T f) noexcept
  {
    const auto t = tan(fov / 2) * n;
    const auto r = a * t;
    frustum(-r, r, -t, t, n, f);
    return *this;
  }

  Mat4&
  adjoint() noexcept
  {
    const auto m11 = m[0], m12 = m[1], m13 = m[2], m14 = m[3], m21 = m[4],
               m22 = m[5], m23 = m[6], m24 = m[7], m31 = m[8], m32 = m[9],
               m33 = m[10], m34 = m[11], m41 = m[12], m42 = m[13], m43 = m[14],
               m44 = m[15];

    return (*this)(m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 -
                    m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
                   m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 +
                    m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
                   m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 -
                    m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
                   m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 +
                    m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,
                   m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 +
                    m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44,
                   m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 -
                    m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44,
                   m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 +
                    m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44,
                   m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 -
                    m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34,
                   m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 -
                    m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44,
                   m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 +
                    m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44,
                   m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 -
                    m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44,
                   m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 +
                    m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34,
                   m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 +
                    m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43,
                   m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 -
                    m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43,
                   m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 +
                    m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43,
                   m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 -
                    m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33);
  }

  Mat4&
  inverse() noexcept
  {
    const auto det = determinant();
    if(det == 0) {
      // TODO(janucaria): handle error
      // throw "NOT_SUPPORTED_ERR";
    }
    adjoint();
    return this->operator/=(det);
  }

  Mat4&
  transpose() noexcept
  {
    return (*this)(m[0],
                   m[4],
                   m[8],
                   m[12],
                   m[1],
                   m[5],
                   m[9],
                   m[13],
                   m[2],
                   m[6],
                   m[10],
                   m[14],
                   m[3],
                   m[7],
                   m[11],
                   m[15]);
  }

  Mat4&
  zero() noexcept
  {
    return (*this)(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  T
  determinant() const noexcept
  {
    const auto m11 = m[0], m12 = m[1], m13 = m[2], m14 = m[3], m21 = m[4],
               m22 = m[5], m23 = m[6], m24 = m[7], m31 = m[8], m32 = m[9],
               m33 = m[10], m34 = m[11], m41 = m[12], m42 = m[13], m43 = m[14],
               m44 = m[15];

    return (
     m41 * m32 * m23 * m14 - m31 * m42 * m23 * m14 - m41 * m22 * m33 * m14 +
     m21 * m42 * m33 * m14 + m31 * m22 * m43 * m14 - m21 * m32 * m43 * m14 -
     m41 * m32 * m13 * m24 + m31 * m42 * m13 * m24 + m41 * m12 * m33 * m24 -
     m11 * m42 * m33 * m24 - m31 * m12 * m43 * m24 + m11 * m32 * m43 * m24 +
     m41 * m22 * m13 * m34 - m21 * m42 * m13 * m34 - m41 * m12 * m23 * m34 +
     m11 * m42 * m23 * m34 + m21 * m12 * m43 * m34 - m11 * m22 * m43 * m34 -
     m31 * m22 * m13 * m44 + m21 * m32 * m13 * m44 + m31 * m12 * m23 * m44 -
     m11 * m32 * m23 * m44 - m21 * m12 * m33 * m44 + m11 * m22 * m33 * m44);
  }
};

} // namespace molphene

#endif

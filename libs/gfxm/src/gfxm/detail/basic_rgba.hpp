#ifndef MOLPHENE_GFXM_DETAIL_BASIC_RGBA_HPP
#define MOLPHENE_GFXM_DETAIL_BASIC_RGBA_HPP

namespace molphene::detail {

template<typename TRgba, typename T>
class basic_rgba {
public:
  using scalar_type = T;

  basic_rgba() noexcept = default;

  explicit basic_rgba(scalar_type s) noexcept
  : basic_rgba{s, s, s, s}
  {
  }

  basic_rgba(scalar_type s, scalar_type a) noexcept
  : basic_rgba{s, s, s, a}
  {
  }

  basic_rgba(scalar_type r, scalar_type g, scalar_type b, scalar_type a) noexcept
  : r_{r}
  , g_{g}
  , b_{b}
  , a_{a}
  {
  }

  void
  r(scalar_type val) noexcept
  {
    r_ = val;
  }

  void
  g(scalar_type val) noexcept
  {
    g_ = val;
  }

  void
  b(scalar_type val) noexcept
  {
    b_ = val;
  }

  void
  a(scalar_type val) noexcept
  {
    a_ = val;
  }

  auto
  r() const noexcept -> scalar_type
  {
    return r_;
  }

  auto
  g() const noexcept -> scalar_type
  {
    return g_;
  }

  auto
  b() const noexcept -> scalar_type
  {
    return b_;
  }

  auto
  a() const noexcept -> scalar_type
  {
    return a_;
  }

  friend auto
  operator==(const basic_rgba& lhs, const basic_rgba& rhs) noexcept -> bool
  {
    return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() &&
           lhs.a() == rhs.a();
  }

  friend auto
  operator!=(const basic_rgba& lhs, const basic_rgba& rhs) noexcept -> bool
  {
    return !(lhs == rhs);
  }

private:
  scalar_type r_, g_, b_, a_;
};

} // namespace molphene::detail

#endif

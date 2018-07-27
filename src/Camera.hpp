#ifndef MOLPHENE_CAMERA_HPP
#define MOLPHENE_CAMERA_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TFloatingP,
         typename TResolution,
         typename TMat4 = Mat4<TFloatingP>>
class Camera {
public:
  using Floatp_t = TFloatingP;
  using Mat4_t = TMat4;
  using Floatp_type = TFloatingP;
  using Mat4_type = TMat4;
  using Resolution_type = TResolution;

  Floatp_type far{0};

  Floatp_type fov{M_PI_4};

  Floatp_type near{0};

  Floatp_type zoom{1};

  Resolution_type height{0};

  Resolution_type width{0};

  Mat4f view_matrix;

  Camera() = default;

  Floatp_t
  aspect_ratio() const noexcept
  {
    return Floatp_t(width) / height;
  }

  const Mat4_t&
  orthogonal_proj_matrix() noexcept
  {
    const auto top = std::tan(fov / 2) * ((far - near) / 2 + near) * zoom;
    const auto right = aspect_ratio() * top;
    return projection_matrix_.orthogonal(-right, right, -top, top, near, far);
  }

  const Mat4_t&
  perspective_proj_matrix() noexcept
  {
    const auto top = std::tan(fov / 2) * near * zoom;
    const auto right = aspect_ratio() * top;
    return projection_matrix_.frustum(-right, right, -top, top, near, far);
  }

  const Mat4_t&
  projection_matrix() noexcept
  {
    return projection_mode_ ? perspective_proj_matrix()
                            : orthogonal_proj_matrix();
  }

  bool
  projection_mode(bool mode) noexcept
  {
    return projection_mode_ = mode;
  }

  void
  set_resolution(Resolution_type size) noexcept
  {
    width = height = size;
  }

  void
  set_resolution(Resolution_type width, Resolution_type height) noexcept
  {
    this->width = width;
    this->height = height;
  }

  void
  reset_zoom() const noexcept
  {
    zoom = 1;
  }

  void
  zoom_in() noexcept
  {
    zoom = std::min(zoom * 1.1, 200 * 1.1);
  }

  void
  zoom_out() noexcept
  {
    zoom = std::max(zoom / 1.1, 1 / 1.1 / 200);
  }

private:
  Mat4_t projection_matrix_;

  bool projection_mode_{false};
};
} // namespace molphene

#endif

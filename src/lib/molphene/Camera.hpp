#ifndef MOLPHENE_CAMERA_HPP
#define MOLPHENE_CAMERA_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TFloatingP,
         typename TResolution = size_t,
         typename TMat4 = Mat4<TFloatingP>>
class Camera {
public:
  using Floatp = TFloatingP;
  using Mat4 = TMat4;
  using Resolution = TResolution;

  Floatp far{0};

  Floatp fov{M_PI_4};

  Floatp near{0};

  Floatp zoom{1};

  Resolution height{0};

  Resolution width{0};

  Mat4f view_matrix{1};

  Camera() noexcept = default;

  Floatp
  aspect_ratio() const noexcept
  {
    return Floatp(width) / height;
  }

  const Mat4&
  orthogonal_proj_matrix() noexcept
  {
    const auto top = std::tan(fov / 2) * ((far - near) / 2 + near) * zoom;
    const auto right = aspect_ratio() * top;
    return projection_matrix_.orthogonal(-right, right, -top, top, near, far);
  }

  const Mat4&
  perspective_proj_matrix() noexcept
  {
    const auto top = std::tan(fov / 2) * near * zoom;
    const auto right = aspect_ratio() * top;
    return projection_matrix_.frustum(-right, right, -top, top, near, far);
  }

  const Mat4&
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
  set_resolution(Resolution size) noexcept
  {
    width = height = size;
  }

  void
  set_resolution(Resolution width, Resolution height) noexcept
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
  Mat4 projection_matrix_{1};

  bool projection_mode_{false};
};
} // namespace molphene

#endif

#ifndef MOLPHENE_CAMERA_HPP
#define MOLPHENE_CAMERA_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TConfig>
class Camera {
public:
  using size_t = typename type_configs<TConfig>::size_type;
  using float_t = typename type_configs<TConfig>::float_type;
  using Mat4f = Mat4<float_t>;

  float_t far{0};

  float_t fov{M_PI_4};

  float_t near{0};

  float_t top{0};

  float_t zoom{1};

  size_t height{0};

  size_t width{0};

  Mat4f view_matrix{1};

  Camera() noexcept = default;

  float_t
  aspect_ratio() const noexcept
  {
    return float_t(width) / height;
  }

  Mat4f
  orthogonal_proj_matrix() const noexcept
  {
    const auto top = std::tan(fov / 2) * ((far - near) / 2 + near) * zoom;
    const auto right = aspect_ratio() * top;
    return Mat4f{1}.orthogonal(-right, right, -top, top, near, far);
  }

  Mat4f
  perspective_proj_matrix() const noexcept
  {
    const auto top = std::tan(fov / 2) * near * zoom;
    const auto right = aspect_ratio() * top;
    return Mat4f{1}.frustum(-right, right, -top, top, near, far);
  }

  Mat4f
  projection_matrix() const noexcept
  {
    return projection_mode_ ? perspective_proj_matrix() : orthogonal_proj_matrix();
  }

  bool
  projection_mode(bool mode) noexcept
  {
    return projection_mode_ = mode;
  }

  void
  set_resolution(size_t size) noexcept
  {
    width = height = size;
  }

  void
  set_resolution(size_t width, size_t height) noexcept
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

  void
  update_view_matrix() noexcept
  {
    const auto aspect = aspect_ratio();
    const auto tan_theta = std::tan(fov / 2);
    const auto focal_len = [=]() noexcept {
      auto focal = top / tan_theta;
      if(aspect < 1) {
        focal /= aspect;
      }
      return focal;
    }();

    near = focal_len - top;
    far = focal_len + top;

    view_matrix.set_translate(0, 0, -focal_len);
  }

private:
  Mat4f projection_matrix_{1};

  bool projection_mode_{false};
};
} // namespace molphene

#endif

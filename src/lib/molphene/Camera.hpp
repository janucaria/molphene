#ifndef MOLPHENE_CAMERA_HPP
#define MOLPHENE_CAMERA_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TConfig>
class Camera {
public:
  using size_t = typename type_configs<TConfig>::size_type;

  using float_t = typename type_configs<TConfig>::float_type;

  using Vec3f = Vec3<float_t>;

  using Mat4f = Mat4<float_t>;

  float_t top{0};

  Camera() noexcept = default;

  auto aspect_ratio() const noexcept -> float_t
  {
    return aspect_ratio_;
  }

  void aspect_ratio(float_t aspect) noexcept
  {
    aspect_ratio_ = aspect;
  }

  void aspect_ratio(size_t width, size_t height) noexcept
  {
    aspect_ratio(float_t(width) / height);
  }

  auto orthogonal_proj_matrix() const noexcept -> Mat4f
  {
    const auto fov = field_of_view();
    const auto near = znear();
    const auto far = zfar();
    const auto zoom = zoom_;
    const auto top = std::tan(fov / 2) * ((far - near) / 2 + near) * zoom;
    const auto right = aspect_ratio() * top;
    return Mat4f{1}.orthogonal(-right, right, -top, top, near, far);
  }

  auto perspective_proj_matrix() const noexcept -> Mat4f
  {
    const auto fov = field_of_view();
    const auto near = znear();
    const auto far = zfar();
    const auto zoom = zoom_;
    const auto top = std::tan(fov / 2) * near * zoom;
    const auto right = aspect_ratio() * top;
    return Mat4f{1}.frustum(-right, right, -top, top, near, far);
  }

  auto projection_matrix() const noexcept -> Mat4f
  {
    return projection_mode_ ? perspective_proj_matrix()
                            : orthogonal_proj_matrix();
  }

  auto projection_mode(bool mode) noexcept -> bool
  {
    return projection_mode_ = mode;
  }

  auto field_of_view() const noexcept -> float_t
  {
    return field_of_view_;
  }

  void reset_zoom() const noexcept
  {
    zoom_ = 1;
  }

  void zoom_in() noexcept
  {
    zoom_ = std::min(zoom_ * 1.1, 200 * 1.1);
  }

  void zoom_out() noexcept
  {
    zoom_ = std::max(zoom_ / 1.1, 1 / 1.1 / 200);
  }

  auto zfar() const noexcept -> float_t
  {
    return zfar_;
  }

  auto znear() const noexcept -> float_t
  {
    return znear_;
  }

  auto view_matrix() const noexcept -> Mat4f
  {
    return Mat4f{1}.translate(position_);
  }

  template<typename... Ts,
           typename = std::enable_if_t<std::is_constructible_v<Vec3f, Ts...>>>
  void position(Ts&&... args) noexcept
  {
    position_ = Vec3f(std::forward<Ts>(args)...);
  }

  auto position() const noexcept -> Vec3f
  {
    return position_;
  }

  void update_view_matrix() noexcept
  {
    const auto aspect = aspect_ratio();
    const auto tan_theta = std::tan(field_of_view() / 2);
    const auto focus_dist = [=]() noexcept
    {
      auto focus = top / tan_theta;
      if(aspect < 1) {
        focus /= aspect;
      }
      return focus;
    }
    ();

    znear_ = focus_dist - top;
    zfar_ = focus_dist + top;

    position(0, 0, -focus_dist);
  }

private:
  float_t field_of_view_{M_PI_4};

  float_t zfar_{0};

  float_t znear_{0};

  float_t zoom_{1};

  float_t aspect_ratio_{1};

  Vec3f position_{0};

  bool projection_mode_{false};
};
} // namespace molphene

#endif

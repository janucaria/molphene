#ifndef MOLPHENE_CAMERA_HPP
#define MOLPHENE_CAMERA_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TConfig>
class camera {
public:
  using size_type = typename type_configs<TConfig>::size_type;

  using float_type = typename type_configs<TConfig>::float_type;

  using vec3f = vec3<float_type>;

  using mat4f = mat4<float_type>;

  constexpr camera() noexcept = default;

  constexpr auto aspect_ratio() const noexcept -> float_type
  {
    return aspect_ratio_;
  }

  constexpr void aspect_ratio(float_type aspect) noexcept
  {
    aspect_ratio_ = aspect;
  }

  constexpr void aspect_ratio(size_type width, size_type height) noexcept
  {
    aspect_ratio(float_type(width) / height);
  }

  constexpr auto orthogonal_proj_matrix() const noexcept -> mat4f
  {
    const auto fov = field_of_view();
    const auto near = znear();
    const auto far = zfar();
    const auto zoom = zoom_;
    const auto top = std::tan(fov / 2) * ((far - near) / 2 + near) * zoom;
    const auto right = aspect_ratio() * top;
    return mat4f{1}.orthogonal(-right, right, -top, top, near, far);
  }

  constexpr auto perspective_proj_matrix() const noexcept -> mat4f
  {
    const auto fov = field_of_view();
    const auto near = znear();
    const auto far = zfar();
    const auto zoom = zoom_;
    const auto top = std::tan(fov / 2) * near * zoom;
    const auto right = aspect_ratio() * top;
    return mat4f{1}.frustum(-right, right, -top, top, near, far);
  }

  constexpr auto projection_matrix() const noexcept -> mat4f
  {
    return projection_mode_ ? perspective_proj_matrix()
                            : orthogonal_proj_matrix();
  }

  constexpr auto projection_mode(bool mode) noexcept -> bool
  {
    return projection_mode_ = mode;
  }

  constexpr auto field_of_view() const noexcept -> float_type
  {
    return field_of_view_;
  }

  constexpr auto top() const noexcept -> float_type
  {
    return top_;
  }

  constexpr auto top(float_type val) noexcept -> float_type&
  {
    return top_ = val;
  }

  constexpr void reset_zoom() const noexcept
  {
    zoom_ = 1;
  }

  constexpr void zoom_in() noexcept
  {
    zoom_ = std::min(zoom_ * 1.1, 200 * 1.1);
  }

  constexpr void zoom_out() noexcept
  {
    zoom_ = std::max(zoom_ / 1.1, 1 / 1.1 / 200);
  }

  constexpr auto zfar() const noexcept -> float_type
  {
    return zfar_;
  }

  constexpr auto znear() const noexcept -> float_type
  {
    return znear_;
  }

  constexpr auto view_matrix() const noexcept -> mat4f
  {
    return mat4f{1}.translate(position_);
  }

  template<typename... Ts,
           typename = std::enable_if_t<std::is_constructible_v<vec3f, Ts...>>>
  constexpr void position(Ts&&... args) noexcept
  {
    position_ = vec3f(std::forward<Ts>(args)...);
  }

  constexpr auto position() const noexcept -> vec3f
  {
    return position_;
  }

  constexpr void update_view_matrix() noexcept
  {
    const auto aspect = aspect_ratio();
    const auto tan_theta = std::tan(field_of_view() / 2);
    const auto top = top_;
    const auto focus_dist = [=]() noexcept
    {
      auto focus = top / tan_theta;
      if(aspect < 1) {
        focus /= aspect;
      }
      return focus;
    }
    ();

    znear_ = focus_dist - top_;
    zfar_ = focus_dist + top_;

    position(0, 0, -focus_dist);
  }

private:
  float_type field_of_view_{M_PI_4};

  float_type top_{0};

  float_type zfar_{0};

  float_type znear_{0};

  float_type zoom_{1};

  float_type aspect_ratio_{1};

  vec3f position_{0};

  bool projection_mode_{false};
};
} // namespace molphene

#endif

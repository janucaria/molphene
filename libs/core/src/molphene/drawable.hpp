#ifndef MOLPHENE_DRAWABLE_HPP
#define MOLPHENE_DRAWABLE_HPP

#include "stdafx.hpp"

#include "color_light_shader.hpp"

namespace molphene {

template<typename>
class basic_drawable {
public:
  template<typename T>
  basic_drawable(T obj)
  : model_ptr_{std::make_shared<model<T>>(std::move(obj))}
  {
  }

  void render(color_light_shader const& shader) const
  {
    model_ptr_->render(shader);
  }

private:
  struct basic_concept {
    basic_concept() noexcept = default;

    basic_concept(const basic_concept&) noexcept = default;

    basic_concept(basic_concept&&) noexcept = default;

    auto operator=(const basic_concept&) noexcept -> basic_concept& = default;

    auto operator=(basic_concept&&) noexcept -> basic_concept& = default;

    virtual ~basic_concept() noexcept = default;

    virtual void render(color_light_shader const& shader) const = 0;
  };

  template<typename T>
  struct model final : basic_concept {
    model(T obj)
    : object_{std::move(obj)}
    {
    }

    void render(color_light_shader const& shader) const override
    {
      object_.render(shader);
    }

  private:
    T object_;
  };

  std::shared_ptr<basic_concept const> model_ptr_;
};

using drawable = basic_drawable<void>;

} // namespace molphene

#endif

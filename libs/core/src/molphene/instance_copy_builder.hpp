#ifndef MOLPHENE_INSTANCE_COPY_BUILDER_HPP
#define MOLPHENE_INSTANCE_COPY_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

class instance_copy_builder {
public:
  using size_type = std::size_t;

  template<typename T, typename OutputIt>
  constexpr void build(T value, OutputIt output) const noexcept
  {
    *output++ = value;
  }

  constexpr inline auto vertices_size() const noexcept -> size_type
  {
    return 1;
  }
};
} // namespace molphene

#endif

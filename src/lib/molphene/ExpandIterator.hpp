#ifndef MOLPHENE_EXPAND_ITERATOR_HPP
#define MOLPHENE_EXPAND_ITERATOR_HPP

#include "stdafx.hpp"

namespace molphene {

namespace detail {

template<typename T, typename = void>
struct is_bounding : std::false_type {
};

template<typename T>
struct is_bounding<T,
                   std::void_t<decltype(std::declval<T>().expand(
                    std::declval<typename T::center_type>()))>>
: std::true_type {
};

template<typename T>
inline constexpr auto is_bounding_v = is_bounding<T>::value;

} // namespace detail

template<typename Bounding>
struct ExpandIterator {
  static_assert(detail::is_bounding_v<Bounding>,
                "Bounding type requirement not satisfied");

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  constexpr explicit ExpandIterator(Bounding& bounding)
  : bounding{bounding}
  {
  }

  constexpr auto operator=(const typename Bounding::center_type& value)
   -> ExpandIterator&
  {
    bounding.expand(value);
    return *this;
  }

  constexpr auto operator=(const typename Bounding::center_type&& value)
   -> ExpandIterator&
  {
    bounding.expand(std::move(value));
    return *this;
  }

  constexpr auto operator*() -> ExpandIterator&
  {
    return *this;
  }

  constexpr auto operator++() -> ExpandIterator&
  {
    return *this;
  }

  constexpr auto operator++(int) -> const ExpandIterator
  {
    return *this;
  }

private:
  Bounding& bounding;
};

} // namespace molphene

#endif

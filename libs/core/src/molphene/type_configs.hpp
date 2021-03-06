#ifndef MOLPHENE_CONFIG_TYPE_HPP
#define MOLPHENE_CONFIG_TYPE_HPP

#include <type_traits>

#include "detail/empty.hpp"

namespace molphene {

template<typename T>
struct type_configs {
private:
  template<typename U, typename V, typename = void>
  struct size_type_imp {
    using type = V;
  };

  template<typename U, typename V>
  struct size_type_imp<U, V, std::void_t<typename U::size_type>> {
    using type = typename U::size_type;
  };

  template<typename U, typename V, typename = void>
  struct float_type_imp {
    using type = V;
  };

  template<typename U, typename V>
  struct float_type_imp<U, V, std::void_t<typename U::float_type>> {
    using type = typename U::float_type;
  };

  template<typename U, typename V, typename = void>
  struct int_type_imp {
    using type = V;
  };

  template<typename U, typename V>
  struct int_type_imp<U, V, std::void_t<typename U::int_type>> {
    using type = typename U::float_type;
  };

  template<typename U, typename V, typename = void>
  struct char_type_imp {
    using type = V;
  };

  template<typename U, typename V>
  struct char_type_imp<U, V, std::void_t<typename U::char_type>> {
    using type = typename U::char_type;
  };

public:
  using size_type = typename size_type_imp<T, std::size_t>::type;
  using float_type = typename float_type_imp<T, double>::type;
  using int_type = typename int_type_imp<T, int>::type;
  using char_type = typename char_type_imp<T, char>::type;
};

template<>
struct type_configs<void> : type_configs<detail::empty> {
  using type_configs<detail::empty>::size_type;
  using type_configs<detail::empty>::float_type;
  using type_configs<detail::empty>::int_type;
  using type_configs<detail::empty>::char_type;
};

} // namespace molphene

#endif
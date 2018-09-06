#ifndef MOLPHENE_CONFIG_TYPE_HPP
#define MOLPHENE_CONFIG_TYPE_HPP

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

public:
  using size_type = typename size_type_imp<T, std::size_t>::type;
  using float_type = typename float_type_imp<T, float>::type;
};

#endif
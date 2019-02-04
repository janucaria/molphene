#ifndef MOLPHENE_UTILITY_HPP
#define MOLPHENE_UTILITY_HPP

#include <type_traits>
#include <variant>

namespace molphene::detail {

template<class T, class... Types>
constexpr std::add_pointer_t<T> attain(std::variant<Types...>* pv) noexcept
{
  auto* ptr = std::get_if<T>(pv);
  assert(ptr != nullptr);
  return ptr;
}

template<class T, class... Types>
constexpr std::add_pointer_t<const T>
attain(const std::variant<Types...>* pv) noexcept
{
  auto* ptr = std::get_if<T>(pv);
  assert(ptr != nullptr);
  return ptr;
}

} // namespace molphene::detail

#endif

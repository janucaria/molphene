#ifndef MOLPHENE_UTILITY_HPP
#define MOLPHENE_UTILITY_HPP

#include <type_traits>
#include <variant>
#include <vector>

namespace molphene::detail {

template<typename T, typename... Types>
constexpr auto attain(std::variant<Types...>* pv) noexcept
 -> std::add_pointer_t<T>
{
  auto* ptr = std::get_if<T>(pv);
  assert(ptr != nullptr);
  return ptr;
}

template<typename T, typename... Types>
constexpr auto attain(const std::variant<Types...>* pv) noexcept
 -> std::add_pointer_t<const T>
{
  auto* ptr = std::get_if<T>(pv);
  assert(ptr != nullptr);
  return ptr;
}

template<typename T, typename Allocator = std::allocator<T>>
constexpr auto
make_reserved_vector(typename std::vector<T, Allocator>::size_type n)
 -> std::vector<T, Allocator>
{
  auto v = std::vector<T, Allocator>{};
  v.reserve(n);
  return v;
}

} // namespace molphene::detail

#endif

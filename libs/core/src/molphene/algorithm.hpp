#ifndef MOLPHENE_ALGORITHM_HPP
#define MOLPHENE_ALGORITHM_HPP

#include "stdafx.hpp"

namespace molphene {

template<typename InputIt, typename Function>
constexpr auto for_each_slice(
 InputIt first,
 InputIt last,
 typename std::iterator_traits<InputIt>::difference_type chunk_length,
 Function func) -> Function
{
  const auto iter_diff = std::distance(first, last);
  const auto chunked_size = std::min(iter_diff, chunk_length);

  if(chunked_size == 0) {
    return func;
  }

  auto chunk_begin = first;
  auto chunk_end = first;

  auto chunks_n = iter_diff / chunked_size;
  if(iter_diff % chunked_size) {
    ++chunks_n;
  }
  while(--chunks_n) {
    std::advance(chunk_end, chunked_size);

    func(boost::make_iterator_range(chunk_begin, chunk_end));

    chunk_begin = chunk_end;
  }

  func(boost::make_iterator_range(chunk_begin, last));

  return func;
}

template<typename InRange, typename Function>
constexpr auto for_each_slice(
 InRange container,
 typename boost::range_difference<InRange>::type chunk_length,
 Function func) -> Function
{
  return for_each_slice(
   std::begin(container), std::end(container), chunk_length, func);
}

} // namespace molphene

#endif
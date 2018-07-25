#ifndef Molphene_primitive_data_h
#define Molphene_primitive_data_h

#include "logger.h"
#include "m3d.hpp"
#include "shape_data.h"
#include <cstddef>

namespace molphene {
template<typename... T>
class primitive_data : public shape_data<T...> {
public:
  primitive_data();

  virtual ~primitive_data();

  void
  clear() override;

  void
  reserve(size_t n) override;

  const vec3f*
  positions();

  const vec3f*
  normals();

  const colour*
  colors();

  virtual unsigned int
  unitlen() const = 0;

protected:
  vec3f* positions_;
  vec3f* normals_;
  colour* colors_;
};

template<typename... T>
primitive_data<T...>::primitive_data()
: shape_data<T...>()
, positions_(nullptr)
, normals_(nullptr)
, colors_(nullptr)
{
}

template<typename... T>
primitive_data<T...>::~primitive_data()
{
  clear();
}

template<typename... T>
void
primitive_data<T...>::clear()
{
  shape_data<T...>::clear();

  delete[] positions_;
  delete[] normals_;
  delete[] colors_;

  positions_ = normals_ = nullptr;
  colors_ = nullptr;
}

template<typename... T>
void
primitive_data<T...>::reserve(size_t n)
{
  shape_data<T...>::reserve(n);

  size_t totalvers = shape_data<T...>::capacity() * unitlen();

  positions_ = new vec3f[totalvers];
  normals_ = new vec3f[totalvers];
  colors_ = new colour[totalvers];
}

template<typename... T>
const vec3f*
primitive_data<T...>::positions()
{
  return positions_;
}

template<typename... T>
const vec3f*
primitive_data<T...>::normals()
{
  return normals_;
}

template<typename... T>
const colour*
primitive_data<T...>::colors()
{
  return colors_;
}
} // namespace molphene

#endif

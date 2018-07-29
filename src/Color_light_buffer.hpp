#ifndef __Molphene__Color_light_buffer__
#define __Molphene__Color_light_buffer__

#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {
class Color_light_buffer {
public:
  Color_light_buffer();

  ~Color_light_buffer();

  virtual void
  setup();

  virtual void
  teardown();

  virtual void
  reserve(GLuint size);

  void
  set_position_data(GLintptr offset, GLsizeiptr size, const vec3f* data);

  void
  set_normal_data(GLintptr offset, GLsizeiptr size, const vec3f* data);

  void
  set_texcoord_data(GLintptr offset, GLsizeiptr size, const Vec2f* data);

  void
  push(GLsizeiptr size,
       const vec3f* posdat,
       const vec3f* normdat,
       const Vec2f* texdat);

  void
  render(GLenum mode);

protected:
  GLintptr size_{0};
  GLuint capacity_{0};

  GLuint position_buffer_{0};
  GLuint normal_buffer_{0};
  GLuint texcoord_buffer_{0};

  void
  enable_vertex_attribs();

  void
  disable_vertex_attribs();
};
} // namespace molphene

#endif

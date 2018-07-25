#include "sphere_buffer.h"

namespace molphene {
sphere_buffer::sphere_buffer()
: color_light_buffer()
, radius_buffer_(0)
{
}

void
sphere_buffer::setup()
{
  glGenBuffers(1, &radius_buffer_);
  color_light_buffer::setup();
}

void
sphere_buffer::teardown()
{
  color_light_buffer::teardown();
  glDeleteBuffers(1, &radius_buffer_);
  radius_buffer_ = 0;
}

void
sphere_buffer::reserve(GLuint n)
{
  color_light_buffer::reserve(n);
  glBindBuffer(GL_ARRAY_BUFFER, radius_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(float) * capacity_, nullptr, GL_STATIC_DRAW);
}

void
sphere_buffer::set_radius_data(GLintptr offset,
                               GLsizeiptr size,
                               const float* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, radius_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(float), size * sizeof(float), data);
}

void
sphere_buffer::push(GLsizeiptr size,
                    const vec3f* posdat,
                    const vec3f* normdat,
                    const colour* coldat,
                    const float* raddat)
{
  if(!size)
    return;
  set_radius_data(size_, size, raddat);
  color_light_buffer::push(size, posdat, normdat, coldat);
}

void
sphere_buffer::enable_vertex_attribs(GLuint posloc,
                                     GLuint normloc,
                                     GLuint colloc,
                                     GLuint radloc)
{
  color_light_buffer::enable_vertex_attribs(posloc, normloc, colloc);
  glEnableVertexAttribArray(radloc);
}

void
sphere_buffer::disable_vertex_attribs(GLuint posloc,
                                      GLuint normloc,
                                      GLuint colloc,
                                      GLuint radloc)
{
  color_light_buffer::disable_vertex_attribs(posloc, normloc, colloc);
  glDisableVertexAttribArray(radloc);
}

void
sphere_buffer::render(
 GLenum mode, GLuint posloc, GLuint normloc, GLuint colloc, GLuint radloc)
{
  enable_vertex_attribs(posloc, normloc, colloc, radloc);

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glVertexAttribPointer(posloc, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glVertexAttribPointer(colloc, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, radius_buffer_);
  glVertexAttribPointer(radloc, 1, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
  glVertexAttribPointer(normloc, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

  glDrawArrays(mode, 0, capacity_);

  disable_vertex_attribs(posloc, normloc, colloc, radloc);
}
} // namespace molphene
#include "color_light_buffer.h"
#include "Color_light_shader.hpp"

namespace molphene {

color_light_buffer::color_light_buffer()
: size_(0)
, capacity_(0)
, position_buffer_(0)
, normal_buffer_(0)
, color_buffer_(0)
{
}

color_light_buffer::~color_light_buffer()
{
  teardown();
}

void
color_light_buffer::setup()
{
  glGenBuffers(1, &position_buffer_);
  glGenBuffers(1, &normal_buffer_);
  glGenBuffers(1, &color_buffer_);
  reserve(0);
}

void
color_light_buffer::teardown()
{
  reserve(0);
  glDeleteBuffers(1, &position_buffer_);
  glDeleteBuffers(1, &normal_buffer_);
  glDeleteBuffers(1, &color_buffer_);
  position_buffer_ = normal_buffer_ = color_buffer_ = 0;
}

void
color_light_buffer::reserve(GLuint n)
{
  capacity_ = n;
  size_ = 0;

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(vec3f) * capacity_, nullptr, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(vec3f) * capacity_, nullptr, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(colour) * capacity_, nullptr, GL_DYNAMIC_DRAW);
}

void
color_light_buffer::push(GLsizeiptr size,
                         const vec3f* posdat,
                         const vec3f* normdat,
                         const colour* coldat)
{
  if(!size)
    return;

  set_position_data(size_, size, posdat);
  set_normal_data(size_, size, normdat);
  set_color_data(size_, size, coldat);

  size_ += size;
}

void
color_light_buffer::set_position_data(GLintptr offset,
                                      GLsizeiptr size,
                                      const vec3f* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(vec3f), size * sizeof(vec3f), data);
}

void
color_light_buffer::set_normal_data(GLintptr offset,
                                    GLsizeiptr size,
                                    const vec3f* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(vec3f), size * sizeof(vec3f), data);
}

void
color_light_buffer::set_color_data(GLintptr offset,
                                   GLsizeiptr size,
                                   const colour* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(colour), size * sizeof(colour), data);
}

void
color_light_buffer::enable_vertex_attribs()
{
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::vertex);
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::normal);
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::color);
}

void
color_light_buffer::disable_vertex_attribs()
{
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::vertex);
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::normal);
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::color);
}

void
color_light_buffer::render(GLenum mode)
{
  enable_vertex_attribs();

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glVertexAttribPointer(Color_light_shader::Attrib_location::vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glVertexAttribPointer(Color_light_shader::Attrib_location::normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
  glVertexAttribPointer(Color_light_shader::Attrib_location::color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

  glDrawArrays(mode, 0, capacity_);

  disable_vertex_attribs();
}

} // namespace molphene
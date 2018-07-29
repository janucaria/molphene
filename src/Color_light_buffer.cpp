#include "Color_light_buffer.hpp"
#include "Color_light_shader.hpp"

namespace molphene {

Color_light_buffer::Color_light_buffer()
{
}

Color_light_buffer::~Color_light_buffer()
{
  teardown();
}

void
Color_light_buffer::setup()
{
  glGenBuffers(1, &position_buffer_);
  glGenBuffers(1, &normal_buffer_);
  glGenBuffers(1, &texcoord_buffer_);
  reserve(0);
}

void
Color_light_buffer::teardown()
{
  reserve(0);
  glDeleteBuffers(1, &position_buffer_);
  glDeleteBuffers(1, &normal_buffer_);
  glDeleteBuffers(1, &texcoord_buffer_);
  position_buffer_ = normal_buffer_ = texcoord_buffer_ = 0;
}

void
Color_light_buffer::reserve(GLuint n)
{
  capacity_ = n;
  size_ = 0;

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(vec3f) * capacity_, nullptr, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(vec3f) * capacity_, nullptr, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_);
  glBufferData(
   GL_ARRAY_BUFFER, sizeof(Vec2f) * capacity_, nullptr, GL_STATIC_DRAW);
}

void
Color_light_buffer::push(GLsizeiptr size,
                         const vec3f* posdat,
                         const vec3f* normdat,
                         const Vec2f* texdat)
{
  if(!size)
    return;

  set_position_data(size_, size, posdat);
  set_normal_data(size_, size, normdat);
  set_texcoord_data(size_, size, texdat);

  size_ += size;
}

void
Color_light_buffer::set_position_data(GLintptr offset,
                                      GLsizeiptr size,
                                      const vec3f* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(vec3f), size * sizeof(vec3f), data);
}

void
Color_light_buffer::set_normal_data(GLintptr offset,
                                    GLsizeiptr size,
                                    const vec3f* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(vec3f), size * sizeof(vec3f), data);
}

void
Color_light_buffer::set_texcoord_data(GLintptr offset,
                                      GLsizeiptr size,
                                      const Vec2f* data)
{
  glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_);
  glBufferSubData(
   GL_ARRAY_BUFFER, offset * sizeof(Vec2f), size * sizeof(Vec2f), data);
}

void
Color_light_buffer::enable_vertex_attribs()
{
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::vertex);
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::normal);
  glEnableVertexAttribArray(Color_light_shader::Attrib_location::texcoord0);
}

void
Color_light_buffer::disable_vertex_attribs()
{
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::vertex);
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::normal);
  glDisableVertexAttribArray(Color_light_shader::Attrib_location::texcoord0);
}

void
Color_light_buffer::render(GLenum mode)
{
  enable_vertex_attribs();

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glVertexAttribPointer(
   Color_light_shader::Attrib_location::vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
  glVertexAttribPointer(
   Color_light_shader::Attrib_location::normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_);
  glVertexAttribPointer(
   Color_light_shader::Attrib_location::texcoord0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(mode, 0, capacity_);

  disable_vertex_attribs();
}

} // namespace molphene
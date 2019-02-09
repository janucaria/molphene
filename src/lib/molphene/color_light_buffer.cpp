#include "color_light_buffer.hpp"

namespace molphene {

color_light_buffer::color_light_buffer(GLsizei verts_per_instance,
                                   GLsizeiptr total_instances) noexcept
: attrib_buffer_array{verts_per_instance, total_instances}
, color_tex_size_(static_cast<GLsizei>(std::ceil(std::sqrt(total_instances))))
{
  glGenTextures(1, &color_tex_);
  glBindTexture(GL_TEXTURE_2D, color_tex_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void color_light_buffer::color_texture_image_data(const GLvoid* data) const
 noexcept
{
  glBindTexture(GL_TEXTURE_2D, color_tex_);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               color_tex_size_,
               color_tex_size_,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               data);
}

auto color_light_buffer::color_texture_image() const noexcept -> GLuint
{
  return color_tex_;
}

auto color_light_buffer::color_texture_size() const noexcept -> GLsizei
{
  return color_tex_size_;
}

} // namespace molphene

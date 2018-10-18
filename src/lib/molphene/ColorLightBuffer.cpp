#include "ColorLightBuffer.hpp"

namespace molphene {

ColorLightBuffer::ColorLightBuffer(GLsizei verts_per_instance,
                                   GLsizeiptr total_instances) noexcept
: AttribsBufferArray {verts_per_instance, total_instances}
, color_tex_size_(static_cast<GLsizei>(std::ceil(std::sqrt(total_instances))))
{
  glGenTextures(1, &color_tex_);
  glBindTexture(GL_TEXTURE_2D, color_tex_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void
ColorLightBuffer::color_texture_image_data(const GLvoid* data) const noexcept
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

GLuint
ColorLightBuffer::color_texture_image() const noexcept
{
  return color_tex_;
}

GLsizei
ColorLightBuffer::color_texture_size() const noexcept
{
  return color_tex_size_;
}

} // namespace molphene

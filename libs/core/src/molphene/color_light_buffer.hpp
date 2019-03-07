#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "stdafx.hpp"

#include "attribs_buffer_array.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include "shader_attrib_location.hpp"
#include "vertex_attribs_buffer.hpp"

namespace molphene {

class color_light_buffer
: public attrib_buffer_array<
   vertex_attribs_buffer<vec3<GLfloat>, shader_attrib_location::vertex>,
   vertex_attribs_buffer<vec3<GLfloat>, shader_attrib_location::normal>,
   vertex_attribs_buffer<vec2<GLfloat>,
                         shader_attrib_location::texcoordcolor>> {
public:
  color_light_buffer(GLsizei verts_per_instance,
                     GLsizeiptr total_instances) noexcept;

  void color_texture_image_data(const GLvoid* data) const noexcept;

  auto color_texture_image() const noexcept -> GLuint;

  auto color_texture_size() const noexcept -> GLsizei;

  template<typename TArg>
  void subdata_positions(GLintptr offset,
                         GLsizeiptr size,
                         gsl::span<TArg> data) const noexcept
  {
    return subdata<0>(offset, size, data);
  }
  
  template<typename TArg>
  void subdata_normals(GLintptr offset,
                       GLsizeiptr size,
                       gsl::span<TArg> data) const noexcept
  {
    return subdata<1>(offset, size, data);
  }

  template<typename TArg>
  void subdata_texcoords(GLintptr offset,
                         GLsizeiptr size,
                         gsl::span<TArg> data) const noexcept
  {
    return subdata<2>(offset, size, data);
  }

private:
  GLuint color_tex_{0};
  GLsizei color_tex_size_{0};
};

} // namespace molphene

#endif

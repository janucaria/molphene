#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "stdafx.hpp"

#include "AttribsBufferArray.hpp"
#include "ShaderAttribLocation.hpp"
#include "VertexAttribsBuffer.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

class ColorLightBuffer
: public AttribsBufferArray<
   VertexAttribsBuffer<Vec3<GLfloat>, ShaderAttribLocation::vertex>,
   VertexAttribsBuffer<Vec3<GLfloat>, ShaderAttribLocation::normal>,
   VertexAttribsBuffer<Vec2<GLfloat>, ShaderAttribLocation::texcoordcolor>> {
public:
  ColorLightBuffer(GLsizei verts_per_instance,
                   GLsizeiptr total_instances) noexcept;

  void
  color_texture_image_data(const GLvoid* data) const noexcept;

  GLuint
  color_texture_image() const noexcept;

  GLsizei
  color_texture_size() const noexcept;

private:
  GLuint color_tex_{0};
  GLsizei color_tex_size_{0};
};

} // namespace molphene

#endif

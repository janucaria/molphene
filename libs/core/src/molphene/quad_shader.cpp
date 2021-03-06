#include "quad_shader.hpp"

namespace molphene {

void quad_shader::setup_gl_attribs_val() const noexcept
{
  glVertexAttrib4f(
   static_cast<GLuint>(shader_attrib_location::vertex), 0, 0, 0, 1);
}

auto quad_shader::vert_shader_source() const noexcept -> const GLchar*
{
  return R"VERTEX_SHADER(
    attribute vec4 a_Vertex;
    
    varying vec2 v_TexCoord;

    void main() {
      gl_Position = a_Vertex;
      v_TexCoord = a_Vertex.xy * 0.5 + 0.5;
    }
  )VERTEX_SHADER";
}

auto quad_shader::frag_shader_source() const noexcept -> const GLchar*
{
  return R"FRAGMENT_SHADER(
#ifdef GL_ES
    precision highp float;
#endif
    uniform sampler2D u_TexColorImage;
    
    varying vec2 v_TexCoord;

    void main() {
      gl_FragColor = texture2D(u_TexColorImage, v_TexCoord);
    }
    
    )FRAGMENT_SHADER";
}

} // namespace molphene
#ifndef __molphene__Renderer__
#define __molphene__Renderer__

#include <memory>
#include <type_traits>

#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

template<typename TDerived>
class Basic_shader {
public:
  enum Attrib_location : GLuint { vertex, normal, color };

  using Attribs_location_name_type =
   std::array<std::pair<Attrib_location, const GLchar*>, 3>;

  Basic_shader() noexcept = default;

  bool
  init_program()
  {
    g_program = create_program();

    if(g_program) {
      as_derived()->setup_gl_uniforms_loc();
      
      auto current_prog = GLint{0};
      glGetIntegerv(GL_CURRENT_PROGRAM, &current_prog);
      glUseProgram(g_program);
      as_const_derived()->setup_gl_uniforms_val();
      glUseProgram(current_prog);

      as_const_derived()->setup_gl_attribs_val();
    }

    return g_program;
  }
  void
  use_program() const
  {
    glUseProgram(g_program);
  }

protected:
  GLuint g_program{0};

  GLuint g_vert_shader{0};

  GLuint g_frag_shader{0};

  GLuint
  create_shader(GLenum shader_type, const char* psource)
  {
    auto shader = glCreateShader(shader_type);
    if(shader) {
      glShaderSource(shader, 1, &psource, nullptr);
      glCompileShader(shader);
      auto compiled = GLint{0};
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if(!compiled) {
        auto infolen = GLint{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolen);
        if(infolen) {
          const auto buff = std::make_unique<char>(infolen);
          glGetShaderInfoLog(shader, infolen, nullptr, buff.get());
          // TODO(janucaria): LOG_E("Could not compile shader %d:\n%s\n",
          // shaderType, buf);
        }
        glDeleteShader(shader);
        shader = 0;
      }
    }
    return shader;
  }

  GLuint
  create_program()
  {
    const auto vert_sh = g_vert_shader =
     create_shader(GL_VERTEX_SHADER, as_const_derived()->vert_shader_source());
    const auto frag_sh = g_frag_shader = create_shader(
     GL_FRAGMENT_SHADER, as_const_derived()->frag_shader_source());

    if(!vert_sh || !frag_sh) {
      return 0;
    }

    auto sh_program = glCreateProgram();
    if(sh_program) {
      glAttachShader(sh_program, vert_sh);
      glAttachShader(sh_program, frag_sh);

      for(auto [index, name] : as_const_derived()->get_attribs_location()) {
        glBindAttribLocation(sh_program, index, name);
      }

      auto link_status = GLint{GL_FALSE};
      glLinkProgram(sh_program);
      glGetProgramiv(sh_program, GL_LINK_STATUS, &link_status);
      if(link_status != GL_TRUE) {
        auto bufflen = GLint{0};
        glGetProgramiv(sh_program, GL_INFO_LOG_LENGTH, &bufflen);
        if(bufflen) {
          const auto buff = std::make_unique<char>(bufflen);
          glGetProgramInfoLog(sh_program, bufflen, nullptr, buff.get());
          // TODO(janucaria): LOG_E("Could not link program:\n%s\n", buf);
        }
        glDeleteProgram(sh_program);
        sh_program = 0;
      }

      glValidateProgram(sh_program);
      auto validate_status = GLint{GL_FALSE};
      glGetProgramiv(sh_program, GL_VALIDATE_STATUS, &validate_status);
      if(validate_status != GL_TRUE) {
        auto bufflen = GLint{0};
        glGetProgramiv(sh_program, GL_INFO_LOG_LENGTH, &bufflen);
        if(bufflen) {
          const auto buff = std::make_unique<char>(bufflen);
          glGetProgramInfoLog(sh_program, bufflen, nullptr, buff.get());
          // TODO(janucaria): LOG_E("Could not link program:\n%s\n", buf);
        }
        glDeleteProgram(sh_program);
        sh_program = 0;
      }
    }

    return sh_program;
  }

private:
  inline auto
  as_const_derived() const noexcept
  {
    return static_cast<const TDerived*>(this);
  }

  inline auto
  as_derived() noexcept
  {
    return static_cast<TDerived*>(this);
  }
};
} // namespace molphene

#endif

#ifndef MOLPHENE_BASIC_SHADER_HPP
#define MOLPHENE_BASIC_SHADER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

template<typename TShader>
class BasicShader {
  struct accessor : TShader {
    static void
    call_setup_gl_attribs_val(const TShader* shader) noexcept
    {
      std::invoke(&accessor::setup_gl_attribs_val, *shader);
    }

    static const char*
    call_vert_shader_source(const TShader* shader) noexcept
    {
      return std::invoke(&accessor::vert_shader_source, *shader);
    }

    static const char*
    call_frag_shader_source(const TShader* shader) noexcept
    {
      return std::invoke(&accessor::frag_shader_source, *shader);
    }

    static typename TShader::AttribsLocationName
    call_get_attribs_location(const TShader* shader) noexcept
    {
      return std::invoke(&accessor::get_attribs_location, *shader);
    }

    static void
    call_setup_gl_uniforms_loc(TShader* shader) noexcept
    {
      std::invoke(&accessor::setup_gl_uniforms_loc, *shader);
    }

    static void
    call_setup_gl_uniforms_val(const TShader* shader) noexcept
    {
      std::invoke(&accessor::setup_gl_uniforms_val, *shader);
    }
  };

public:
  BasicShader() noexcept = default;

  bool
  init_program() noexcept
  {
    g_program = create_program();

    if(!g_program) {
      std::terminate();
    }
    
    accessor::call_setup_gl_uniforms_loc(derived_ptr());

    auto current_prog = GLint{0};
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_prog);
    glUseProgram(g_program);
    accessor::call_setup_gl_uniforms_val(cderived_ptr());
    glUseProgram(current_prog);

    accessor::call_setup_gl_attribs_val(cderived_ptr());

    return g_program;
  }
  void
  use_program() const noexcept
  {
    glUseProgram(g_program);
  }

protected:
  GLuint g_program{0};

  GLuint g_vert_shader{0};

  GLuint g_frag_shader{0};

  GLuint
  create_shader(GLenum shader_type, const char* psource) noexcept
  {
    auto shader = glCreateShader(shader_type);
    if(shader) {
      glShaderSource(shader, 1, &psource, nullptr);
      glCompileShader(shader);
      auto compiled = GLint{0};
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if(!compiled) {
#ifndef NDEBUG
        auto infolen = GLint{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolen);
        if(infolen) {
          const auto buff = std::make_unique<char>(infolen);
          glGetShaderInfoLog(shader, infolen, nullptr, buff.get());
          std::cerr << "Could not compile shader "
                    << std::to_string(shader_type) << '\n'
                    << buff.get() << '\n';
        }
#endif
        glDeleteShader(shader);
        shader = 0;
      }
    }
    return shader;
  }

  GLuint
  create_program() noexcept
  {
    const auto vert_sh = g_vert_shader =
     create_shader(GL_VERTEX_SHADER, accessor::call_vert_shader_source(cderived_ptr()));
    const auto frag_sh = g_frag_shader = create_shader(
     GL_FRAGMENT_SHADER, accessor::call_frag_shader_source(cderived_ptr()));

    if(!vert_sh || !frag_sh) {
      return 0;
    }

    auto sh_program = glCreateProgram();
    if(sh_program) {
      glAttachShader(sh_program, vert_sh);
      glAttachShader(sh_program, frag_sh);

      for(auto [index, name] : accessor::call_get_attribs_location(cderived_ptr())) {
        glBindAttribLocation(sh_program, static_cast<GLuint>(index), name);
      }

      auto link_status = GLint{GL_FALSE};
      glLinkProgram(sh_program);
      glGetProgramiv(sh_program, GL_LINK_STATUS, &link_status);
      if(link_status != GL_TRUE) {
#ifndef NDEBUG
        auto bufflen = GLint{0};
        glGetProgramiv(sh_program, GL_INFO_LOG_LENGTH, &bufflen);
        if(bufflen) {
          const auto buff = std::make_unique<char>(bufflen);
          glGetProgramInfoLog(sh_program, bufflen, nullptr, buff.get());
          std::cerr << "Could not link program\n" << buff.get() << '\n';
        }
#endif
        glDeleteProgram(sh_program);
        sh_program = 0;
      }

      glValidateProgram(sh_program);
      auto validate_status = GLint{GL_FALSE};
      glGetProgramiv(sh_program, GL_VALIDATE_STATUS, &validate_status);
      if(validate_status != GL_TRUE) {
#ifndef NDEBUG
        auto bufflen = GLint{0};
        glGetProgramiv(sh_program, GL_INFO_LOG_LENGTH, &bufflen);
        if(bufflen) {
          const auto buff = std::make_unique<char>(bufflen);
          glGetProgramInfoLog(sh_program, bufflen, nullptr, buff.get());
          std::cerr << "Could not validate program\n" << buff.get() << '\n';
        }
#endif
        glDeleteProgram(sh_program);
        sh_program = 0;
      }
    }

    return sh_program;
  }

private:
  inline auto
  cderived_ptr() const noexcept
  {
    return static_cast<const TShader*>(this);
  }

  inline auto
  derived_ptr() noexcept
  {
    return static_cast<TShader*>(this);
  }
};
} // namespace molphene

#endif

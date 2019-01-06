#ifndef MOLPHENE_BASIC_SHADER_HPP
#define MOLPHENE_BASIC_SHADER_HPP

#include "stdafx.hpp"

#include "MixShaderUniforms.hpp"
#include "ShaderAttribLocation.hpp"
#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

template<typename TShader, typename TMixShaderUniform>
class BasicShader : public TMixShaderUniform {
  struct accessor : TShader {
    static void call_setup_gl_attribs_val(const TShader* shader) noexcept
    {
      std::invoke(&accessor::setup_gl_attribs_val, *shader);
    }

    static auto call_vert_shader_source(const TShader* shader) noexcept -> const
     char*
    {
      return std::invoke(&accessor::vert_shader_source, *shader);
    }

    static auto call_frag_shader_source(const TShader* shader) noexcept -> const
     char*
    {
      return std::invoke(&accessor::frag_shader_source, *shader);
    }
  };

public:
  BasicShader() noexcept = default;

  auto init_program() noexcept -> bool
  {
    g_program = create_program();

    assert(g_program);

    this->init_uniform_location(g_program);

    accessor::call_setup_gl_attribs_val(cderived_ptr());

    return g_program;
  }

  void use_program() const noexcept
  {
    glUseProgram(g_program);
  }

protected:
  auto gprogram() const noexcept -> GLuint
  {
    return g_program;
  }

  auto create_shader(GLenum shader_type, const char* psource) noexcept -> GLuint
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

  auto create_program() noexcept -> GLuint
  {
    const auto vert_sh = g_vert_shader = create_shader(
     GL_VERTEX_SHADER, accessor::call_vert_shader_source(cderived_ptr()));
    const auto frag_sh = g_frag_shader = create_shader(
     GL_FRAGMENT_SHADER, accessor::call_frag_shader_source(cderived_ptr()));

    if(!vert_sh || !frag_sh) {
      return 0;
    }

    auto sh_program = glCreateProgram();
    if(sh_program) {
      glAttachShader(sh_program, vert_sh);
      glAttachShader(sh_program, frag_sh);

      BasicShader::bind_attrib_locations(sh_program);

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
  GLuint g_program{0};

  GLuint g_vert_shader{0};

  GLuint g_frag_shader{0};

  inline auto cderived_ptr() const noexcept
  {
    return static_cast<const TShader*>(this);
  }

  inline auto derived_ptr() noexcept
  {
    return static_cast<TShader*>(this);
  }

  static void bind_attrib_locations(GLuint gprogram)
  {
    bind_attrib_locations(gprogram, typename TShader::AttribLocations());
  }

  template<ShaderAttribLocation... locations>
  static void bind_attrib_locations(GLuint gprogram,
                                    ShaderAttribList<locations...>)
  {
    (glBindAttribLocation(
      gprogram, static_cast<GLuint>(locations), traits<locations>::name),
     ...);
  }
};
} // namespace molphene

#endif

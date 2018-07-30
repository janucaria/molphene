#ifndef MOLPHENE_COLOR_LIGHT_BUFFER_HPP
#define MOLPHENE_COLOR_LIGHT_BUFFER_HPP

#include "Sphere_mesh_builder.hpp"
#include "m3d.hpp"
#include "opengl.hpp"
#include <gsl/gsl>
#include <vector>

namespace molphene {

class Color_light_buffer {
public:
  Color_light_buffer(GLsizei verts_per_instance, GLsizeiptr total_instances);

  ~Color_light_buffer();

  Color_light_buffer(const Color_light_buffer&) = delete;

  Color_light_buffer(Color_light_buffer&&) = delete;

  Color_light_buffer&
  operator=(const Color_light_buffer&) = delete;

  Color_light_buffer&
  operator=(Color_light_buffer&&) = delete;

  void
  set_data(GLintptr offset,
           GLsizeiptr size,
           gsl::span<const Vec3f> verts,
           gsl::span<const Vec3f> norms,
           gsl::span<const Vec2f> texcoords);

  void
  draw();

private:
  GLsizei verts_per_instance_{0};
  GLsizei instances_per_block_{0};
  GLsizei remain_instances_{0};

  GLsizei size_;

  std::vector<GLuint> vert_buffers_;
  std::vector<GLuint> normal_buffers_;
  std::vector<GLuint> texcoord_buffers_;
};
} // namespace molphene

#endif

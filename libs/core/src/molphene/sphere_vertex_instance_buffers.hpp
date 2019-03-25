#ifndef MOLPHENE_SPHERE_VERTEX_INSTANCE_BUFFERS_HPP
#define MOLPHENE_SPHERE_VERTEX_INSTANCE_BUFFERS_HPP

#include "stdafx.hpp"

#include "opengl.hpp"

#include "attribs_buffer_array.hpp"
#include "color_light_shader.hpp"
#include "image_texture.hpp"

#include "gl/draw_instanced_arrays.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "shader_attrib_location.hpp"
#include "utility.hpp"

namespace molphene {

template<typename = void>
class basic_sphere_vertex_instance_buffers {
public:
  std::unique_ptr<color_image_texture> color_texture;

  std::unique_ptr<positions_buffer_array> buffer_positions;

  std::unique_ptr<normals_buffer_array> buffer_normals;

  std::unique_ptr<texcoords_instances_buffer_array> buffer_texcoords;

  std::unique_ptr<transforms_instances_buffer_array> buffer_transforms;

  void draw(const color_light_shader& shader) const noexcept
  {
    assert(all_has_same_props(*buffer_positions,
                              *buffer_normals));
    assert(all_has_same_props(*buffer_transforms,
                              *buffer_texcoords));

    shader.color_texture_image(color_texture->texture_image());

    const auto size = buffer_transforms->size();
    const auto remain_instances =
     buffer_transforms->remain_instances();
    const auto instances_per_block =
     buffer_transforms->instances_per_block();
    const auto verts_per_instance =
     buffer_positions->verts_per_instance();

    buffer_positions->bind_attrib_pointer_index(0);
    buffer_normals->bind_attrib_pointer_index(0);

    for(auto i = GLsizei{0}; i < size; ++i) {
      const auto total_instances =
       GLsizei{i == (size - 1) ? remain_instances : instances_per_block};

      buffer_texcoords->bind_attrib_pointer_index(i);
      buffer_transforms->bind_attrib_pointer_index(i);

      gl::draw_arrays_instanced(
       GL_TRIANGLE_STRIP, 0, verts_per_instance, total_instances);
    }
  }

private:
};

using sphere_vertex_instance_buffers =
 basic_sphere_vertex_instance_buffers<void>;

} // namespace molphene

#endif

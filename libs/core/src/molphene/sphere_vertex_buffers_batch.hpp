#ifndef MOLPHENE_SPHERE_VERTEX_BUFFERS_BATCH_HPP
#define MOLPHENE_SPHERE_VERTEX_BUFFERS_BATCH_HPP

#include "stdafx.hpp"

#include "opengl.hpp"

#include "attribs_buffer_array.hpp"
#include "color_image_texture.hpp"
#include "color_light_shader.hpp"

#include "algorithm.hpp"
#include "buffers_builder.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "shader_attrib_location.hpp"
#include "sphere_mesh_builder.hpp"
#include "utility.hpp"

namespace molphene {

template<typename = void>
class basic_sphere_vertex_buffers_batch {
public:
  static constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};

  std::unique_ptr<color_image_texture> color_texture;

  std::unique_ptr<positions_buffer_array> buffer_positions;

  std::unique_ptr<normals_buffer_array> buffer_normals;

  std::unique_ptr<texcoords_buffer_array> buffer_texcoords;

  template<typename TRangeSphereMeshAttr>
  void build_buffers(TRangeSphereMeshAttr&& sphere_mesh_attrs)
  {
    buffer_positions = build_sphere_mesh_positions(
     sph_mesh_builder, std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));

    buffer_normals = build_sphere_mesh_normals(
     sph_mesh_builder, std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));

    buffer_texcoords = build_sphere_mesh_texcoords(
     sph_mesh_builder, std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));

    color_texture = build_shape_color_texture(
     std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));
  }

  void draw(const color_light_shader& shader) const noexcept
  {
    const auto verts_guard =
     gl_vertex_attribs_guard<shader_attrib_location::vertex,
                             shader_attrib_location::normal,
                             shader_attrib_location::texcoordcolor>{};

    assert(
     all_has_same_props(*buffer_positions, *buffer_normals, *buffer_texcoords));

    shader.color_texture_image(color_texture->texture());

    const auto size = buffer_positions->size();
    const auto remain_instances = buffer_positions->remain_instances();
    const auto instances_per_block = buffer_positions->instances_per_block();
    const auto verts_per_instance = buffer_positions->verts_per_instance();

    for(auto i = GLsizei{0}; i < size; ++i) {
      const auto verts_count =
       GLsizei{i == (size - 1) ? remain_instances : instances_per_block};
      const auto count = verts_count * verts_per_instance;

      buffer_positions->bind_attrib_pointer_index(i);
      buffer_normals->bind_attrib_pointer_index(i);
      buffer_texcoords->bind_attrib_pointer_index(i);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
    }
  }

private:
};

using sphere_vertex_buffers_batch = basic_sphere_vertex_buffers_batch<void>;

} // namespace molphene

#endif

#ifndef MOLPHENE_SPHERE_VERTEX_BUFFERS_INSTANCED_HPP
#define MOLPHENE_SPHERE_VERTEX_BUFFERS_INSTANCED_HPP

#include "stdafx.hpp"

#include "opengl.hpp"

#include "attribs_buffer_array.hpp"
#include "color_image_texture.hpp"
#include "color_light_shader.hpp"

#include "buffers_builder.hpp"
#include "gl/draw_instanced_arrays.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "instance_copy_builder.hpp"
#include "shader_attrib_location.hpp"
#include "sphere_mesh_builder.hpp"
#include "utility.hpp"

namespace molphene {

template<typename = void>
class basic_sphere_vertex_buffers_instanced {
public:
  static constexpr auto sph_mesh_builder = sphere_mesh_builder<10, 20>{};

  static constexpr auto copy_builder = instance_copy_builder{};

  std::unique_ptr<color_image_texture> color_texture;

  std::unique_ptr<positions_buffer_array> buffer_positions;

  std::unique_ptr<normals_buffer_array> buffer_normals;

  std::unique_ptr<texcoords_instances_buffer_array> buffer_texcoords;

  std::unique_ptr<transforms_instances_buffer_array> buffer_transforms;

  template<typename TRangeSphereMeshAttr>
  void build_buffers(TRangeSphereMeshAttr&& sphere_mesh_attrs)
  {
    const auto sphere_attr = std::array<sphere_mesh_attribute, 1>{};

    buffer_positions =
     build_sphere_mesh_positions(sph_mesh_builder, sphere_attr);

    buffer_normals = build_sphere_mesh_normals(sph_mesh_builder, sphere_attr);

    buffer_texcoords = build_sphere_mesh_texcoord_instances(
     copy_builder, std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));

    buffer_transforms = build_sphere_mesh_transform_instances(
     copy_builder, std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));

    color_texture = build_shape_color_texture(
     std::forward<TRangeSphereMeshAttr>(sphere_mesh_attrs));
  }

  void draw(const color_light_shader& shader) const noexcept
  {
    const auto verts_guard =
     gl_vertex_attribs_guard<shader_attrib_location::vertex,
                             shader_attrib_location::normal,
                             shader_attrib_location::texcoordcolor,
                             shader_attrib_location::transformation,
                             shader_attrib_location::transformation_1,
                             shader_attrib_location::transformation_2,
                             shader_attrib_location::transformation_3>{};

    assert(all_has_same_props(*buffer_positions, *buffer_normals));
    assert(all_has_same_props(*buffer_transforms, *buffer_texcoords));

    shader.color_texture_image(color_texture->texture());

    const auto size = buffer_transforms->size();
    const auto remain_instances = buffer_transforms->remain_instances();
    const auto instances_per_block = buffer_transforms->instances_per_block();
    const auto verts_per_instance = buffer_positions->verts_per_instance();

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

using sphere_vertex_buffers_instanced =
 basic_sphere_vertex_buffers_instanced<void>;

} // namespace molphene

#endif

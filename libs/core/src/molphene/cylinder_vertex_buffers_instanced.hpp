#ifndef MOLPHENE_CYLINDER_VERTEX_BUFFERS_INSTANCED_HPP
#define MOLPHENE_CYLINDER_VERTEX_BUFFERS_INSTANCED_HPP

#include "stdafx.hpp"

#include "opengl.hpp"

#include "attribs_buffer_array.hpp"
#include "color_image_texture.hpp"
#include "color_light_shader.hpp"

#include "buffers_builder.hpp"
#include "cylinder_mesh_attribute.hpp"
#include "cylinder_mesh_builder.hpp"
#include "gl_vertex_attribs_guard.hpp"
#include "instance_copy_builder.hpp"
#include "shader_attrib_location.hpp"

namespace molphene {

template<typename = void>
class basic_cylinder_vertex_buffers_instanced {
public:
  static constexpr auto cyl_mesh_builder = cylinder_mesh_builder<20>{};

  static constexpr auto copy_builder = instance_copy_builder{};

  std::unique_ptr<color_image_texture> color_texture;

  std::unique_ptr<positions_buffer_array> buffer_positions;

  std::unique_ptr<normals_buffer_array> buffer_normals;

  std::unique_ptr<texcoords_instances_buffer_array> buffer_texcoords;

  std::unique_ptr<transforms_instances_buffer_array> buffer_transforms;

  template<typename TRangeCylinderMeshAttr>
  void build_buffers(TRangeCylinderMeshAttr&& cylinder_mesh_attrs)
  {
    const auto cylinder_attr = std::array<cylinder_mesh_attribute, 1>{};

    buffer_positions =
     build_cylinder_mesh_positions(cyl_mesh_builder, cylinder_attr);

    buffer_normals =
     build_cylinder_mesh_normals(cyl_mesh_builder, cylinder_attr);

    buffer_texcoords =
     build_cylinder_mesh_texcoord_instances(copy_builder, cylinder_mesh_attrs);

    buffer_transforms =
     build_cylinder_mesh_transform_instances(copy_builder, cylinder_mesh_attrs);

    color_texture = build_shape_color_texture(cylinder_mesh_attrs);
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

    {
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
  }

private:
};

using cylinder_vertex_buffers_instanced =
 basic_cylinder_vertex_buffers_instanced<void>;

} // namespace molphene

#endif

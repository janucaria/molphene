#ifndef MOLPHENE_BUFFER_BUILDER_HPP
#define MOLPHENE_BUFFER_BUILDER_HPP

#include <molphene/stdafx.hpp>

#include <molphene/attribs_buffer_array.hpp>
#include <molphene/cylinder_mesh_builder.hpp>
#include <molphene/image_texture.hpp>
#include <molphene/m3d.hpp>
#include <molphene/sphere_mesh_builder.hpp>
#include <molphene/utility.hpp>

namespace molphene {

template<typename TMeshSizedRange>
auto build_shape_color_texture(TMeshSizedRange&& shape_attrs)
 -> std::unique_ptr<color_image_texture>
{
  auto shape_color_texture = std::make_unique<color_image_texture>();

  const auto total_instances =
   std::forward<TMeshSizedRange>(shape_attrs).size();

  const auto tex_size = std::ceil(std::sqrt(total_instances));
  auto colors = detail::make_reserved_vector<rgba8>(tex_size * tex_size);

  boost::range::transform(
   std::forward<TMeshSizedRange>(shape_attrs), std::back_inserter(colors), [
   ](auto attr) noexcept { return attr.color; });

  colors.resize(colors.capacity());
  shape_color_texture->data(colors);

  return shape_color_texture;
}

template<typename TOutputVertexBuffer,
         typename TMeshBuilder,
         typename TShapeMeshSizedRange,
         typename TFunction>
auto build_mesh_vertices(TMeshBuilder mesh_builder,
                         TShapeMeshSizedRange&& shape_attrs,
                         TFunction callable_fn)
 -> std::unique_ptr<TOutputVertexBuffer>
{
  using vertex_buffer_array_t = TOutputVertexBuffer;
  using shape_attrs_container_t = TShapeMeshSizedRange;

  constexpr auto vertices_per_instance = mesh_builder.vertices_size();
  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  constexpr auto bytes_per_vertex =
   sizeof(vec3<GLfloat>) + sizeof(vec3<GLfloat>) + sizeof(vec2<GLfloat>);
  constexpr auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
  constexpr auto max_instances_per_chunk =
   bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
  const auto total_instances =
   std::forward<shape_attrs_container_t>(shape_attrs).size();
  const auto instances_per_chunk =
   std::min(total_instances, max_instances_per_chunk);
  const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

  auto shape_buff_atoms = std::make_unique<vertex_buffer_array_t>(
   vertices_per_instance, total_instances, max_instances_per_chunk);

  auto chunk_count = size_t{0};
  for_each_slice(
   std::forward<shape_attrs_container_t>(shape_attrs),
   instances_per_chunk,
   [&](auto shape_attrs_range) {
     const auto instances_size = boost::distance(shape_attrs_range);

     using vertex_data_t = typename vertex_buffer_array_t::data_type;
     auto vertices =
      detail::make_reserved_vector<vertex_data_t>(vertices_per_chunk);

     boost::for_each(
      shape_attrs_range, [&](auto shape_attr) noexcept {
        mesh_builder.build(callable_fn(shape_attr),
                           std::back_inserter(vertices));
      });

     shape_buff_atoms->subdata(chunk_count * instances_per_chunk,
                               instances_size,
                               gsl::span(vertices.data(), vertices.size()));

     ++chunk_count;
   });

  return shape_buff_atoms;
}

template<typename TMeshBuilder, typename TSphMeshSizedRange>
auto build_sphere_mesh_transform_instances(TMeshBuilder mesh_builder,
                                           TSphMeshSizedRange&& sph_attrs)
 -> std::unique_ptr<transforms_instances_buffer_array>
{
  return build_mesh_vertices<transforms_instances_buffer_array>(
   mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
   ](auto sph_attr) noexcept {
     auto transform_mat = mat4<float>{1};
     transform_mat.scale(sph_attr.sphere.radius);
     transform_mat.translate(sph_attr.sphere.center);
     return transform_mat;
   });
}

template<typename TMeshBuilder, typename TSphMeshSizedRange>
auto build_sphere_mesh_texcoord_instances(TMeshBuilder mesh_builder,
                                          TSphMeshSizedRange&& sph_attrs)
 -> std::unique_ptr<texcoords_instances_buffer_array>
{
  return build_mesh_vertices<texcoords_instances_buffer_array>(
   mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
   ](auto sph_attr) noexcept { return sph_attr.texcoord; });
}

template<typename TMeshBuilder, typename TSphMeshSizedRange>
auto build_sphere_mesh_positions(TMeshBuilder mesh_builder,
                                 TSphMeshSizedRange&& sph_attrs)
 -> std::unique_ptr<positions_buffer_array>
{
  return build_mesh_vertices<positions_buffer_array>(
   mesh_builder, std::forward<TSphMeshSizedRange>(sph_attrs), [
   ](auto sph_attr) noexcept {
     return build_sphere_mesh_position_params{sph_attr.sphere};
   });
}

template<typename TMeshBuilder, typename TSphMeshSizedRange>
auto build_sphere_mesh_normals(TMeshBuilder mesh_builder,
                               TSphMeshSizedRange&& sph_attrs)
 -> std::unique_ptr<normals_buffer_array>
{
  return build_mesh_vertices<normals_buffer_array>(
   mesh_builder, sph_attrs, [](auto) noexcept {
     return build_sphere_mesh_normal_params{};
   });
}

template<typename TMeshBuilder, typename TSphMeshSizedRange>
auto build_sphere_mesh_texcoords(TMeshBuilder mesh_builder,
                                 TSphMeshSizedRange&& sph_attrs)
 -> std::unique_ptr<texcoords_buffer_array>
{
  return build_mesh_vertices<texcoords_buffer_array>(
   mesh_builder, sph_attrs, [](auto sph_attr) noexcept {
     return build_sphere_mesh_fill_params{sph_attr.texcoord};
   });
}

template<typename TMeshBuilder, typename TCylMeshSizedRange>
auto build_cylinder_mesh_positions(TMeshBuilder mesh_builder,
                                   TCylMeshSizedRange&& cyl_attrs)
 -> std::unique_ptr<positions_buffer_array>
{
  return build_mesh_vertices<positions_buffer_array>(
   mesh_builder, std::forward<TCylMeshSizedRange>(cyl_attrs), [
   ](auto cyl_attr) noexcept {
     return build_cylinder_mesh_position_params{cyl_attr.cylinder};
   });
}

template<typename TMeshBuilder, typename TCylMeshSizedRange>
auto build_cylinder_mesh_normals(TMeshBuilder mesh_builder,
                                 TCylMeshSizedRange&& cyl_attrs)
 -> std::unique_ptr<normals_buffer_array>
{
  return build_mesh_vertices<normals_buffer_array>(
   mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
     return build_cylinder_mesh_normal_params{cyl_attr.cylinder};
   });
}

template<typename TMeshBuilder, typename TCylMeshSizedRange>
auto build_cylinder_mesh_texcoords(TMeshBuilder mesh_builder,
                                   TCylMeshSizedRange&& cyl_attrs)
 -> std::unique_ptr<texcoords_buffer_array>
{
  return build_mesh_vertices<texcoords_buffer_array>(
   mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
     return build_cylinder_mesh_fill_params{cyl_attr.cylinder,
                                            cyl_attr.texcoord};
   });
}

template<typename TMeshBuilder, typename TCylMeshSizedRange>
auto build_cylinder_mesh_transform_instances(TMeshBuilder mesh_builder,
                                             TCylMeshSizedRange&& cyl_attrs)
 -> std::unique_ptr<transforms_instances_buffer_array>
{
  return build_mesh_vertices<transforms_instances_buffer_array>(
   mesh_builder, std::forward<TCylMeshSizedRange>(cyl_attrs), [
   ](auto cyl_attr) noexcept {
     using vec3_t =
      typename std::decay_t<decltype(cyl_attr.cylinder)>::vec3_type;

     auto transform_mat = mat4<float>{1};

     const auto top_dir = vec3_t{0, 1, 0};
     const auto cyl_dir =
      (cyl_attr.cylinder.top - cyl_attr.cylinder.bottom) / 2;
     const auto cyl_dir_length = cyl_dir.magnitude();
     const auto rot_axis = cyl_dir.cross(top_dir).to_unit();
     const auto rot_angle = std::acos(cyl_dir.dot(top_dir) / cyl_dir_length);
     const auto cyl_radius = cyl_attr.cylinder.radius;
     const auto cyl_position = cyl_attr.cylinder.bottom + cyl_dir;

     transform_mat.scale(cyl_radius, cyl_dir_length, cyl_radius);
     transform_mat.rotate(rot_axis, rot_angle);
     transform_mat.translate(cyl_position);

     return transform_mat;
   });
}

template<typename TMeshBuilder, typename TCylMeshSizedRange>
auto build_cylinder_mesh_texcoord_instances(TMeshBuilder mesh_builder,
                                            TCylMeshSizedRange&& cyl_attrs)
 -> std::unique_ptr<texcoords_instances_buffer_array>
{
  return build_mesh_vertices<texcoords_instances_buffer_array>(
   mesh_builder, cyl_attrs, [](auto cyl_attr) noexcept {
     return cyl_attr.texcoord;
   });
}

} // namespace molphene

#endif

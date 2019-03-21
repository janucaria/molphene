#ifndef MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP
#define MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "opengl.hpp"
#include "vertex_attribs_buffer.hpp"

namespace molphene {

template<typename TVertAttribBuffer>
class attrib_buffer_array {
public:
  using data_type = typename TVertAttribBuffer::data_type;

  attrib_buffer_array(GLsizei verts_per_instance,
                      GLsizei total_instances,
                      GLsizei max_instances_per_block) noexcept
  : verts_per_instance_{verts_per_instance}
  {
    instances_per_block_ = std::min(max_instances_per_block, total_instances);
    size_ = instances_per_block_ ? total_instances / instances_per_block_ : 0;
    remain_instances_ =
     instances_per_block_ ? total_instances % instances_per_block_ : 0;

    if(remain_instances_ == 0) {
      remain_instances_ = instances_per_block_;
    } else {
      ++size_;
    }

    using attrib_buff_t =
     typename std::remove_reference_t<decltype(attrib_buffers_)>::element_type;
    attrib_buffers_ = std::make_unique<attrib_buff_t[]>(size_);

    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto meshes =
       i == (size_ - 1) ? remain_instances_ : instances_per_block_;
      const auto verts_count = GLsizeiptr{meshes * verts_per_instance_};

      attrib_buffers_[i].size(verts_count);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  attrib_buffer_array(const attrib_buffer_array&) = delete;

  attrib_buffer_array(attrib_buffer_array&&) = delete;

  ~attrib_buffer_array() noexcept = default;

  auto operator=(const attrib_buffer_array&) -> attrib_buffer_array& = delete;

  auto operator=(attrib_buffer_array &&) -> attrib_buffer_array& = delete;

  template<typename TArg>
  void subdata(GLintptr offset, GLsizeiptr size, gsl::span<TArg> data) const
   noexcept
  {
    auto data_offset = GLsizeiptr{0};
    while(size > 0) {
      const auto chunk = GLsizeiptr{offset / instances_per_block_};
      const auto index = GLsizeiptr{offset % instances_per_block_};

      const auto elems_fill = instances_per_block_ - index;
      const auto fill_size = GLsizeiptr{size < elems_fill ? size : elems_fill};

      attrib_buffers_[chunk].data(
       index * verts_per_instance_,
       fill_size * verts_per_instance_,
       data.first(data_offset * verts_per_instance_).data());

      size -= fill_size;
      offset += fill_size;
      data_offset += fill_size;
    }
  }

  template<typename TCallback>
  void setup_attrib_pointer(TCallback fn) const
   noexcept(std::is_nothrow_invocable_v<decltype(fn), GLsizei>)
  {
    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto verts_count =
       GLsizei{i == (size_ - 1) ? remain_instances_ : instances_per_block_};

      attrib_buffers_[i].attrib_pointer();

      fn(verts_count * verts_per_instance_);
    }
  }

  void bind_attrib_pointer_index(GLsizei index) const noexcept
  {
    attrib_buffers_[index].attrib_pointer();
  }

  auto verts_per_instance() const noexcept -> GLsizei
  {
    return verts_per_instance_;
  }

  auto instances_per_block() const noexcept -> GLsizei
  {
    return instances_per_block_;
  }

  auto remain_instances() const noexcept -> GLsizei
  {
    return remain_instances_;
  }

  auto size() const noexcept -> GLsizei
  {
    return size_;
  }

  template<typename... T1s, typename... T2s>
  friend auto has_same_props(const attrib_buffer_array<T1s...>& buff,
                             const attrib_buffer_array<T2s...>& other) noexcept
   -> bool
  {
    return (buff.size_ == other.size_) &&
           (buff.remain_instances_ == other.remain_instances_) &&
           (buff.instances_per_block_ == other.instances_per_block_) &&
           (buff.verts_per_instance_ == other.verts_per_instance_);
  }

  template<typename TSelf, typename... TOthers>
  friend auto all_has_same_props(TSelf&& buff, TOthers&&... buffs) noexcept
   -> bool
  {
    static_assert(sizeof...(TOthers) > 0);
    return (has_same_props(buff, buffs) && ...);
  }

private:
  GLsizei verts_per_instance_{0};
  GLsizei instances_per_block_{0};
  GLsizei remain_instances_{0};

  GLsizei size_;

  std::unique_ptr<TVertAttribBuffer[]> attrib_buffers_;
};

using positions_buffer_array = attrib_buffer_array<
 vertex_attribs_buffer<vec3<GLfloat>, shader_attrib_location::vertex>>;

using normals_buffer_array = attrib_buffer_array<
 vertex_attribs_buffer<vec3<GLfloat>, shader_attrib_location::normal>>;

using texcoords_buffer_array = attrib_buffer_array<
 vertex_attribs_buffer<vec2<GLfloat>, shader_attrib_location::texcoordcolor>>;

using texcoords_instances_buffer_array = attrib_buffer_array<
 vertex_attribs_buffer<vec2<GLfloat>,
                       shader_attrib_location::texcoordcolor,
                       1>>;

using transforms_instances_buffer_array = attrib_buffer_array<
 vertex_attribs_buffer<mat4<GLfloat>,
                       shader_attrib_location::transformation,
                       1>>;

} // namespace molphene

#endif

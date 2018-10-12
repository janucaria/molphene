#ifndef MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP
#define MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

template<typename... Ts>
class AttribsBufferArray {
public:
  AttribsBufferArray(GLsizei verts_per_instance,
                     GLsizeiptr total_instances) noexcept
  : verts_per_instance_{verts_per_instance}
  {
    constexpr auto max_bytes_per_chunk = std::numeric_limits<GLsizei>::max();
    constexpr auto bytes_per_vert = (sizeof(typename Ts::DataType) + ... + 0);
    const auto bytes_per_instance = bytes_per_vert * verts_per_instance_;

    instances_per_block_ = max_bytes_per_chunk / bytes_per_instance;
    size_ = total_instances / instances_per_block_;
    remain_instances_ = total_instances % instances_per_block_;

    if(remain_instances_ == 0) {
      remain_instances_ = instances_per_block_;
    } else {
      ++size_;
    }

    boost::fusion::for_each(attrib_buffers_, [=](auto& attribbuf) noexcept {
      using AttribBuffer =
       typename std::remove_reference_t<decltype(attribbuf)>::element_type;
      attribbuf = std::make_unique<AttribBuffer[]>(size_);
    });

    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto meshes =
       i == (size_ - 1) ? remain_instances_ : instances_per_block_;
      const auto verts_count = GLsizeiptr{meshes * verts_per_instance_};

      boost::fusion::for_each(
       attrib_buffers_, [=](const auto& attribbuf) noexcept {
         attribbuf[i].size(verts_count);
       });
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  AttribsBufferArray(const AttribsBufferArray&) = delete;

  AttribsBufferArray(AttribsBufferArray&&) = delete;

  AttribsBufferArray&
  operator=(const AttribsBufferArray&) = delete;

  AttribsBufferArray&
  operator=(AttribsBufferArray&&) = delete;

  void
  set_data(GLintptr offset,
           GLsizeiptr size,
           gsl::span<const typename Ts::DataType>... data) const noexcept
  {
    set_data(std::make_index_sequence<sizeof...(Ts)>(),
             offset,
             size,
             std::forward_as_tuple(data...));
  }

  template<typename... Args, std::size_t... idx>
  void
  set_data(std::index_sequence<idx...>,
           GLintptr offset,
           GLsizeiptr size,
           std::tuple<Args...> data) const noexcept
  {
    static_assert(sizeof...(Ts) == sizeof...(idx) &&
                  sizeof...(Ts) == sizeof...(Args));

    auto data_offset = GLsizeiptr{0};
    while(size > 0) {
      const auto chunk = GLsizeiptr{offset / instances_per_block_};
      const auto index = GLsizeiptr{offset % instances_per_block_};

      const auto elems_fill = instances_per_block_ - index;
      const auto fill_size = GLsizeiptr{size < elems_fill ? size : elems_fill};

      (std::get<idx>(attrib_buffers_)[chunk].data(
        index * verts_per_instance_,
        fill_size * verts_per_instance_,
        std::get<idx>(data).first(data_offset * verts_per_instance_).data()),
       ...);

      size -= fill_size;
      offset += fill_size;
      data_offset += fill_size;
    }
  }

  template<typename TCallback>
  void
  setup_attrib_pointer(TCallback fn) const
   noexcept(std::is_nothrow_invocable_v<decltype(fn), GLsizei>)
  {
    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto verts_count =
       GLsizei{i == (size_ - 1) ? remain_instances_ : instances_per_block_};

      boost::fusion::for_each(
       attrib_buffers_, [=](const auto& attribbuf) noexcept {
         attribbuf[i].attrib_pointer();
       });

      fn(verts_count * verts_per_instance_);
    }
  }

private:
  GLsizei verts_per_instance_{0};
  GLsizei instances_per_block_{0};
  GLsizei remain_instances_{0};

  GLsizei size_;

  std::tuple<std::unique_ptr<Ts[]>...> attrib_buffers_;
};

} // namespace molphene

#endif
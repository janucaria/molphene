#ifndef MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP
#define MOLPHENE_ATTRIBS_BUFFER_ARRAY_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "opengl.hpp"

namespace molphene {

template<typename... Ts>
class attrib_buffer_array {
public:
  attrib_buffer_array(GLsizei verts_per_instance,
                      GLsizeiptr total_instances) noexcept
  : verts_per_instance_{verts_per_instance}
  {
    constexpr auto max_bytes_per_chunk = std::numeric_limits<GLsizei>::max();
    constexpr auto bytes_per_vert = (sizeof(typename Ts::data_type) + ... + 0);
    const auto bytes_per_instance = bytes_per_vert * verts_per_instance_;

    instances_per_block_ = max_bytes_per_chunk / bytes_per_instance;
    size_ = total_instances / instances_per_block_;
    remain_instances_ = total_instances % instances_per_block_;

    if(remain_instances_ == 0) {
      remain_instances_ = instances_per_block_;
    } else {
      ++size_;
    }

    boost::mp11::tuple_for_each(
     attrib_buffers_, [=](auto& attribbuf) noexcept {
       using attrib_buff_t =
        typename std::remove_reference_t<decltype(attribbuf)>::element_type;
       attribbuf = std::make_unique<attrib_buff_t[]>(size_);
     });

    for(auto i = GLsizei{0}; i < size_; ++i) {
      const auto meshes =
       i == (size_ - 1) ? remain_instances_ : instances_per_block_;
      const auto verts_count = GLsizeiptr{meshes * verts_per_instance_};

      boost::mp11::tuple_for_each(
       attrib_buffers_, [=](const auto& attribbuf) noexcept {
         attribbuf[i].size(verts_count);
       });
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  attrib_buffer_array(const attrib_buffer_array&) = delete;

  attrib_buffer_array(attrib_buffer_array&&) = delete;

  ~attrib_buffer_array() noexcept = default;

  auto operator=(const attrib_buffer_array&) -> attrib_buffer_array& = delete;

  auto operator=(attrib_buffer_array &&) -> attrib_buffer_array& = delete;

  template<std::size_t VIdx, typename TArg>
  void subdata(GLintptr offset, GLsizeiptr size, gsl::span<TArg> data) const noexcept
  {
    static_assert(VIdx < sizeof...(Ts));

    constexpr auto idx = VIdx;

    auto data_offset = GLsizeiptr{0};
    while(size > 0) {
      const auto chunk = GLsizeiptr{offset / instances_per_block_};
      const auto index = GLsizeiptr{offset % instances_per_block_};

      const auto elems_fill = instances_per_block_ - index;
      const auto fill_size = GLsizeiptr{size < elems_fill ? size : elems_fill};

      std::get<idx>(attrib_buffers_)[chunk].data(
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

      boost::mp11::tuple_for_each(
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

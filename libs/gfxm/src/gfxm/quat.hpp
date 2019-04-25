#ifndef MOLPHENE_GFXM_QUAT_HPP
#define MOLPHENE_GFXM_QUAT_HPP

#include <boost/qvm/quat.hpp>

namespace molphene {

template<typename T>
using quat = boost::qvm::quat<T>;

} // namespace molphene

#endif

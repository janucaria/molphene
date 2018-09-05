#include <cfloat>
#include <type_traits>

#define BOOST_TEST_MODULE "m3d matrix"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <molphene/m3d.hpp>

BOOST_AUTO_TEST_SUITE(float_matrix4_test)

BOOST_AUTO_TEST_CASE(traits)
{
  using Mat4f = molphene::Mat4<float>;

  BOOST_CHECK(std::is_trivial_v<Mat4f>);
  BOOST_CHECK(std::is_standard_layout_v<Mat4f>);
}

BOOST_AUTO_TEST_SUITE_END()

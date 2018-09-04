#include <cfloat>
#include <type_traits>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <molphene/m3d.hpp>

BOOST_AUTO_TEST_SUITE(rgba8_test)

BOOST_AUTO_TEST_CASE(traits)
{
  using Rgba8 = molphene::Rgba8;

  BOOST_CHECK(std::is_trivial_v<Rgba8>);
  BOOST_CHECK(std::is_standard_layout_v<Rgba8>);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rgba32f_test)

BOOST_AUTO_TEST_CASE(traits)
{
  using Rgba32f = molphene::Rgba32f;

  BOOST_CHECK(std::is_trivial_v<Rgba32f>);
  BOOST_CHECK(std::is_standard_layout_v<Rgba32f>);
}

BOOST_AUTO_TEST_SUITE_END()

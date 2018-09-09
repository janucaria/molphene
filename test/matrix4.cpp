#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <molphene/m3d.hpp>

TEST_CASE("float_matrix4_test traits")
{
  using Mat4f = molphene::Mat4<float>;

  REQUIRE(std::is_trivial_v<Mat4f>);
  REQUIRE(std::is_standard_layout_v<Mat4f>);
}

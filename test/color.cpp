#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <molphene/m3d.hpp>

TEST_CASE("rgba8_test traits")
{
  using Rgba8 = molphene::Rgba8;

  REQUIRE(std::is_trivial_v<Rgba8>);
  REQUIRE(std::is_standard_layout_v<Rgba8>);
}

TEST_CASE("rgba32f_test traits")
{
  using Rgba32f = molphene::Rgba32f;

  REQUIRE(std::is_trivial_v<Rgba32f>);
  REQUIRE(std::is_standard_layout_v<Rgba32f>);
}

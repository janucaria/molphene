#include <cstdint>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gfxm/rgba.hpp>

using rgba8 = molphene::rgba<std::uint8_t>;

TEST_CASE("rgba_uint8 traits")
{
  REQUIRE(std::is_trivial_v<rgba8>);
  REQUIRE(std::is_standard_layout_v<rgba8>);
  REQUIRE(sizeof(rgba8) == (sizeof(std::uint8_t) * 4));
}

TEST_CASE("rgba_uint8 initialization")
{
  {
    auto col = rgba8{0};
    REQUIRE(col.r() == 0);
    REQUIRE(col.g() == 0);
    REQUIRE(col.b() == 0);
    REQUIRE(col.a() == 0);
  }
  {
    auto col = rgba8{0xFF, 0x7F};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0xFF);
    REQUIRE(col.b() == 0xFF);
    REQUIRE(col.a() == 0x7F);
  }
  {
    auto col = rgba8{0xFF, 0x7F, 0x50};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0x7F);
    REQUIRE(col.b() == 0x50);
    REQUIRE(col.a() == 255);
  }
  {
    auto col = rgba8{0xFF, 0x7F, 0x50, 21};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0x7F);
    REQUIRE(col.b() == 0x50);
    REQUIRE(col.a() == 21);
  }
}

TEST_CASE("rgba_uint8 equality comparable")
{
  auto cola = rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto colb = rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto colc = rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto cold = rgba8{0, 0, 0, 0};

  REQUIRE(cola == cola);
  REQUIRE(cola == colb);
  REQUIRE(colb == cola);
  REQUIRE(colb == colc);
  REQUIRE(cola == colc);

  REQUIRE(cola != cold);
}
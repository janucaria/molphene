#include <cstdint>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gfxm/rgba.hpp>

using u8 = std::uint8_t;
using rgba8 = molphene::rgba<u8>;
using rgbaf = molphene::rgba<float>;

TEST_CASE("rgba_uint8 traits")
{
  REQUIRE(std::is_trivial_v<rgbaf>);
  REQUIRE(std::is_standard_layout_v<rgbaf>);
  REQUIRE(sizeof(rgbaf) == (sizeof(float) * 4));
}

TEST_CASE("rgba_uint8 initialization")
{
  {
    auto col = rgbaf{0};
    REQUIRE(col.r() == 0.0f);
    REQUIRE(col.g() == 0.0f);
    REQUIRE(col.b() == 0.0f);
    REQUIRE(col.a() == 0.0f);
  }
  {
    auto col = rgbaf{0.4, 0.4};
    REQUIRE(col.r() == Approx(0.4f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(0.4f));
    REQUIRE(col.a() == Approx(0.4f));
  }
  {
    auto col = rgbaf{0.6, 0.4, 1.8};
    REQUIRE(col.r() == Approx(0.6f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(1.8f));
    REQUIRE(col.a() == Approx(1.0f));
  }
  {
    auto col = rgbaf{0.6, 0.4, 1.8, 1.0};
    REQUIRE(col.r() == Approx(0.6f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(1.8f));
    REQUIRE(col.a() == Approx(1.0f));
  }
  {
    auto col = rgbaf{u8{45}, u8{201}, u8{99}, u8{255}};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
  {
    auto col = rgbaf{rgba8{45, 201, 99, 255}};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
  {
    auto cu8 = rgba8{45, 201, 99, 255};
    auto col = rgbaf{cu8};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
}

TEST_CASE("rgba_uint8 equality comparable")
{
  auto cola = rgbaf{0.6, 0.4, 1.8, 1.0};
  auto colb = rgbaf{0.6, 0.4, 1.8, 1.0};
  auto colc = rgbaf{0.6, 0.4, 1.8, 1.0};
  auto cold = rgbaf{0, 0, 0, 0};

  REQUIRE(cola == cola);
  REQUIRE(cola == colb);
  REQUIRE(colb == cola);
  REQUIRE(colb == colc);
  REQUIRE(cola == colc);

  REQUIRE(cola != cold);
}
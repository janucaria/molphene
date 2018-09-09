#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <molphene/m3d.hpp>

TEST_CASE("float_vector3_test traits")
{
  using Vec3f = molphene::Vec3<float>;

  REQUIRE(std::is_trivial_v<Vec3f>);
  REQUIRE(std::is_standard_layout_v<Vec3f>);
}

TEST_CASE("float_vector3_test initialization")
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{0};
    REQUIRE(vt.x == 0.0f);
    REQUIRE(vt.y == 0.0f);
    REQUIRE(vt.z == 0.0f);
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    REQUIRE(vt.x == 1.5f);
    REQUIRE(vt.y == 2.2f);
    REQUIRE(vt.z == 8.9f);

    vt = Vec3f{2.5, 0.3, 7.4};
    REQUIRE(vt.x == 2.5f);
    REQUIRE(vt.y == 0.3f);
    REQUIRE(vt.z == 7.4f);
  }
  {
    auto vt = Vec3f{Vec3f{1.5, 2.3, 6.4}};
    REQUIRE(vt.x == 1.5f);
    REQUIRE(vt.y == 2.3f);
    REQUIRE(vt.z == 6.4f);
  }
}

TEST_CASE("float_vector3_test comparison")
{
  using Vec3f = molphene::Vec3<float>;

  REQUIRE((Vec3f{0} == Vec3f{0, 0, 0}));
  REQUIRE((Vec3f{3.5} == Vec3f{3.5, 3.5, 3.5}));
  REQUIRE((Vec3f{-.5} == Vec3f{-.5, -.5, -.5}));

  REQUIRE((Vec3f{-.5} != Vec3f{-.5, -.1, -.5}));
}

TEST_CASE("float_vector3_test addition")
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{0} + Vec3f{2.5, 0.3, 7.4};
    REQUIRE(vt.x == Approx(2.5f));
    REQUIRE(vt.y == Approx(0.3f));;
    REQUIRE(vt.z == Approx(7.4f));;
  }
  {
    auto vt = Vec3f{-10.4, 0.4, -15.4};
    vt += Vec3f{0};
    REQUIRE(vt.x == Approx(-10.4f));;
    REQUIRE(vt.y == Approx(0.4f));;
    REQUIRE(vt.z == Approx(-15.4f));;
  }
  {
    auto vt = Vec3f{-1., 0, 1} + 0.2;
    REQUIRE(vt.x == Approx(-0.8f));;
    REQUIRE(vt.y == Approx(0.2f));;
    REQUIRE(vt.z == Approx(1.2f));;
  }
  {
    auto vt = Vec3f{10.4, -2.2, 5.5};
    vt += 3.2f;
    REQUIRE(vt.x == Approx(13.6f));;
    REQUIRE(vt.y == Approx(1.0f));;
    REQUIRE(vt.z == Approx(8.7f));;
  }
}

TEST_CASE("float_vector3_test vector3d_subtraction")
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{1.5, 2.2, 8.9} - Vec3f{0};
    REQUIRE(vt.x == Approx(1.5f));;
    REQUIRE(vt.y == Approx(2.2f));;
    REQUIRE(vt.z == Approx(8.9f));;
  }
  {
    auto vt = Vec3f{0};
    vt -= Vec3f(-10.4, 0.4, -15.4);
    REQUIRE(vt.x == Approx(10.4f));;
    REQUIRE(vt.y == Approx(-0.4f));;
    REQUIRE(vt.z == Approx(15.4f));;
  }
  {
    auto vt = Vec3f{2.5, -0.3, 7.4} - 0.2;
    REQUIRE(vt.x == Approx(2.3f));;
    REQUIRE(vt.y == Approx(-0.5f));;
    REQUIRE(vt.z == Approx(7.2f));;
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    vt -= 3.2f;
    REQUIRE(vt.x == Approx(-1.7f));;
    REQUIRE(vt.y == Approx(-1.f));;
    REQUIRE(vt.z == Approx(5.7f));;
  }
}


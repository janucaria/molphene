#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gfxm/vec3.hpp>

using molphene::vec3;
using vec3f = vec3<float>;

TEST_CASE("float_vector3_test traits")
{
  REQUIRE(std::is_trivial_v<vec3f>);
  REQUIRE(std::is_standard_layout_v<vec3f>);
  REQUIRE(sizeof(vec3f) == (sizeof(float) * 3));
}

TEST_CASE("float_vector3_test initialization")
{
  {
    auto vt = vec3f{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vt = vec3f{1.5, 2.2, 8.9};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.2f);
    REQUIRE(vt.z() == 8.9f);
  }
  {
    auto vt = vec3f{vec3f{1.5, 2.3, 6.4}};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.3f);
    REQUIRE(vt.z() == 6.4f);
  }
  {
    auto vt = vec3f{vec3<int>{0}};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vt = vec3f{0};
    vt = vec3<int>{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vd = vec3<double>{0};
    vec3f vt = vd;
    CHECK(vt.x() == 0.0f);
    CHECK(vt.y() == 0.0f);
    CHECK(vt.z() == 0.0f);
  }
}

TEST_CASE("float_vector3_test comparison")
{
  REQUIRE((vec3f{0} == vec3f{0, 0, 0}));
  REQUIRE((vec3f{3.5} == vec3f{3.5, 3.5, 3.5}));
  REQUIRE((vec3f{-.5} == vec3f{-.5, -.5, -.5}));

  REQUIRE((vec3f{-.5} != vec3f{-.5, -.1, -.5}));
}

TEST_CASE("float_vector3_test addition")
{
  {
    auto vt = vec3f{-10.4, 0.4, -15.4};
    vt += vec3f{0};
    REQUIRE(vt.x() == Approx(-10.4f));
    REQUIRE(vt.y() == Approx(0.4f));
    REQUIRE(vt.z() == Approx(-15.4f));
  }
  {
    auto vt = vec3f{10.4, -2.2, 5.5};
    vt += 3.2;
    REQUIRE(vt.x() == Approx(13.6f));
    REQUIRE(vt.y() == Approx(1.0f));
    REQUIRE(vt.z() == Approx(8.7f));
    ;
  }
  {
    auto vt = vec3f{0} + vec3f{2.5, 0.3, 7.4};
    REQUIRE(vt.x() == Approx(2.5f));
    REQUIRE(vt.y() == Approx(0.3f));
    REQUIRE(vt.z() == Approx(7.4f));
  }
  {
    auto vt = vec3f{-1., 0, 1} + 0.2;
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
    REQUIRE(vt.z() == Approx(1.2f));
  }
  {
    auto vt = 0.2 + vec3f{-1., 0, 1};
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
    REQUIRE(vt.z() == Approx(1.2f));
  }
  {
    auto vt = vec3<float>{0} + vec3<double>{0};
    CHECK(vt.x() == Approx(0.));
    CHECK(vt.y() == Approx(0.));
    CHECK(vt.z() == Approx(0.));
  }
}

TEST_CASE("float_vector3_test subtraction")
{
  {
    auto vt = vec3f{0};
    vt -= vec3f(-10.4, 0.4, -15.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = vec3f{1.5, 2.2, 8.9};
    vt -= 3.2;
    REQUIRE(vt.x() == Approx(-1.7f));
    REQUIRE(vt.y() == Approx(-1.f));
    REQUIRE(vt.z() == Approx(5.7f));
  }
  {
    auto vt = vec3f{1.5, 2.2, 8.9} - vec3f{0};
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(2.2f));
    REQUIRE(vt.z() == Approx(8.9f));
  }
  {
    auto vt = vec3f{2.5, -0.3, 7.4} - 1;
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(-1.3f));
    REQUIRE(vt.z() == Approx(6.4f));
  }
  {
    auto vt = 1u - vec3f{2.5, -0.3, 7.4};
    REQUIRE(vt.x() == Approx(-1.5f));
    REQUIRE(vt.y() == Approx(1.3f));
    REQUIRE(vt.z() == Approx(-6.4f));
  }
  {
    auto vt = vec3<float>{0} - vec3<double>{0};
    CHECK(vt.x() == Approx(0.));
    CHECK(vt.y() == Approx(0.));
    CHECK(vt.z() == Approx(0.));
  }
}

TEST_CASE("float_vector3_test multiplication")
{
  {
    auto vt = vec3f(-10.4, 0.4, -15.4);
    vt *= vec3f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = vec3f(-10.4, 0.4, -15.4);
    vt *= -1l;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = vec3f(-10.4, 0.4, -15.4) * vec3f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = vec3f(-10.4, 0.4, -15.4) * -1.0;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = -1 * vec3f(-10.4, 0.4, -15.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = vec3<float>{0} * vec3<double>{0};
    CHECK(vt.x() == Approx(0.));
    CHECK(vt.y() == Approx(0.));
    CHECK(vt.z() == Approx(0.));
  }
}

TEST_CASE("float_vector3_test division")
{
  {
    auto vt = vec3f(-10.0, 0.5, 2);
    vt /= vec3f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = vec3f(-10.0, 0.5, 2);
    vt /= 2ull;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = vec3f(-10.0, 0.5, 2) / vec3f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = vec3f(-10.0, 0.5, 2) / 2;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = 2 / vec3f(-10.0, 0.5, 2);
    REQUIRE(vt.x() == Approx(-0.2f));
    REQUIRE(vt.y() == Approx(4.0f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = vec3<float>{0} / vec3<double>{1};
    CHECK(vt.x() == Approx(0.));
    CHECK(vt.y() == Approx(0.));
    CHECK(vt.z() == Approx(0.));
  }
}

TEST_CASE("float_vector3_test reflect")
{
  {
    auto d = vec3f{10, -2, 0};
    auto r = d.reflect({0, 1, 0});
    REQUIRE(r.x() == Approx(10.f));
    REQUIRE(r.y() == Approx(2.0f));
    REQUIRE(r.z() == Approx(0.0f));
  }
}

TEST_CASE("float_vector3_test to_unit")
{
  {
    auto vt = vec3f(-10.0, 0.5, 2) / 2;
    auto n = vt.to_unit();
    REQUIRE(n.magnitude() == Approx(1.0f));
  }
}
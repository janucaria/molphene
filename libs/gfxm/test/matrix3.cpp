#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gfxm/mat3.hpp>

using molphene::mat3;
using molphene::mat4;

using mat3f = mat3<float>;

TEST_CASE("float_matrix3_test traits")
{
  REQUIRE(std::is_trivial_v<mat3f>);
  REQUIRE(std::is_standard_layout_v<mat3f>);
  REQUIRE(sizeof(mat3f) == (sizeof(float) * 9));
}

TEST_CASE("float_matrix3_test initialization")
{
  {
    auto mat = mat3f{1};
    REQUIRE(mat.m00() == 1.0f);
    REQUIRE(mat.m01() == 0.0f);
    REQUIRE(mat.m02() == 0.0f);

    REQUIRE(mat.m10() == 0.0f);
    REQUIRE(mat.m11() == 1.0f);
    REQUIRE(mat.m12() == 0.0f);

    REQUIRE(mat.m20() == 0.0f);
    REQUIRE(mat.m21() == 0.0f);
    REQUIRE(mat.m22() == 1.0f);
  }
  {
    auto mat =
     mat3f{0.0f, 1.0f, 2.0f, 10.0f, 11.0f, 12.0f, 20.0f, 21.0f, 22.0f};

    REQUIRE(mat.m00() == 0.0f);
    REQUIRE(mat.m01() == 1.0f);
    REQUIRE(mat.m02() == 2.0f);

    REQUIRE(mat.m10() == 10.0f);
    REQUIRE(mat.m11() == 11.0f);
    REQUIRE(mat.m12() == 12.0f);

    REQUIRE(mat.m20() == 20.0f);
    REQUIRE(mat.m21() == 21.0f);
    REQUIRE(mat.m22() == 22.0f);
  }
  {
    auto mat = mat3f{mat4<int>{1}};

    REQUIRE(mat.m00() == 1.0f);
    REQUIRE(mat.m01() == 0.0f);
    REQUIRE(mat.m02() == 0.0f);

    REQUIRE(mat.m10() == 0.0f);
    REQUIRE(mat.m11() == 1.0f);
    REQUIRE(mat.m12() == 0.0f);

    REQUIRE(mat.m20() == 0.0f);
    REQUIRE(mat.m21() == 0.0f);
    REQUIRE(mat.m22() == 1.0f);
  }
}
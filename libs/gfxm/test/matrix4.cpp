#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gfxm/mat4.hpp>

using mat4f = molphene::mat4<float>;

TEST_CASE("float_matrix4_test traits")
{
  REQUIRE(std::is_trivial_v<mat4f>);
  REQUIRE(std::is_standard_layout_v<mat4f>);
  REQUIRE(sizeof(mat4f) == (sizeof(float) * 16));
}

TEST_CASE("float_matrix4_test initialization")
{
  {
    auto mat = mat4f{1};
    REQUIRE(mat.m00() == 1.0f);
    REQUIRE(mat.m01() == 0.0f);
    REQUIRE(mat.m02() == 0.0f);
    REQUIRE(mat.m03() == 0.0f);

    REQUIRE(mat.m10() == 0.0f);
    REQUIRE(mat.m11() == 1.0f);
    REQUIRE(mat.m12() == 0.0f);
    REQUIRE(mat.m13() == 0.0f);

    REQUIRE(mat.m20() == 0.0f);
    REQUIRE(mat.m21() == 0.0f);
    REQUIRE(mat.m22() == 1.0f);
    REQUIRE(mat.m23() == 0.0f);

    REQUIRE(mat.m30() == 0.0f);
    REQUIRE(mat.m31() == 0.0f);
    REQUIRE(mat.m32() == 0.0f);
    REQUIRE(mat.m33() == 1.0f);
  }
  {
    auto mat = mat4f{0.0f,
                     1.0f,
                     2.0f,
                     3.0f,
                     10.0f,
                     11.0f,
                     12.0f,
                     13.0f,
                     20.0f,
                     21.0f,
                     22.0f,
                     23.0f,
                     30.0f,
                     31.0f,
                     32.0f,
                     33.0f};

    REQUIRE(mat.m00() == 0.0f);
    REQUIRE(mat.m01() == 1.0f);
    REQUIRE(mat.m02() == 2.0f);
    REQUIRE(mat.m03() == 3.0f);

    REQUIRE(mat.m10() == 10.0f);
    REQUIRE(mat.m11() == 11.0f);
    REQUIRE(mat.m12() == 12.0f);
    REQUIRE(mat.m13() == 13.0f);

    REQUIRE(mat.m20() == 20.0f);
    REQUIRE(mat.m21() == 21.0f);
    REQUIRE(mat.m22() == 22.0f);
    REQUIRE(mat.m23() == 23.0f);
    
    REQUIRE(mat.m30() == 30.0f);
    REQUIRE(mat.m31() == 31.0f);
    REQUIRE(mat.m32() == 32.0f);
    REQUIRE(mat.m33() == 33.0f);
  }
}
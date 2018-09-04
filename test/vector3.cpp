#include <cfloat>
#include <type_traits>

#define BOOST_TEST_DYN_LINK
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>

#include <molphene/m3d.hpp>

BOOST_AUTO_TEST_SUITE(float_vector3_test)

BOOST_AUTO_TEST_CASE(traits)
{
  using Vec3f = molphene::Vec3<float>;

  BOOST_CHECK(std::is_trivial_v<Vec3f>);
  BOOST_CHECK(std::is_standard_layout_v<Vec3f>);
}

BOOST_AUTO_TEST_CASE(initialization)
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{0};
    BOOST_CHECK_EQUAL(vt.x, 0.0f);
    BOOST_CHECK_EQUAL(vt.y, 0.0f);
    BOOST_CHECK_EQUAL(vt.z, 0.0f);
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    BOOST_CHECK_EQUAL(vt.x, 1.5f);
    BOOST_CHECK_EQUAL(vt.y, 2.2f);
    BOOST_CHECK_EQUAL(vt.z, 8.9f);

    vt = Vec3f{2.5, 0.3, 7.4};
    BOOST_CHECK_EQUAL(vt.x, 2.5f);
    BOOST_CHECK_EQUAL(vt.y, 0.3f);
    BOOST_CHECK_EQUAL(vt.z, 7.4f);
  }
  {
    auto vt = Vec3f{Vec3f{1.5, 2.3, 6.4}};
    BOOST_CHECK_EQUAL(vt.x, 1.5f);
    BOOST_CHECK_EQUAL(vt.y, 2.3f);
    BOOST_CHECK_EQUAL(vt.z, 6.4f);
  }
}

BOOST_AUTO_TEST_CASE(comparison)
{
  using Vec3f = molphene::Vec3<float>;

  BOOST_CHECK((Vec3f{0} == Vec3f{0, 0, 0}));
  BOOST_CHECK((Vec3f{3.5} == Vec3f{3.5, 3.5, 3.5}));
  BOOST_CHECK((Vec3f{-.5} == Vec3f{-.5, -.5, -.5}));

  BOOST_CHECK((Vec3f{-.5} != Vec3f{-.5, -.1, -.5}));
}

BOOST_AUTO_TEST_CASE(addition)
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{0} + Vec3f{2.5, 0.3, 7.4};
    BOOST_CHECK_CLOSE_FRACTION(vt.x, 2.5f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, 0.3f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 7.4f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{-10.4, 0.4, -15.4};
    vt += Vec3f{0};
    BOOST_CHECK_CLOSE_FRACTION(vt.x, -10.4f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, 0.4f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, -15.4f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{-1., 0, 1} + 0.2;
    BOOST_CHECK_CLOSE_FRACTION(vt.x, -0.8f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, 0.2f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 1.2f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{10.4, -2.2, 5.5};
    vt += 3.2f;
    BOOST_CHECK_CLOSE_FRACTION(vt.x, 13.6f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, 1.0f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 8.7f, FLT_EPSILON);
  }
}

BOOST_AUTO_TEST_CASE(vector3d_subtraction)
{
  using Vec3f = molphene::Vec3<float>;

  {
    auto vt = Vec3f{1.5, 2.2, 8.9} - Vec3f{0};
    BOOST_CHECK_CLOSE_FRACTION(vt.x, 1.5f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, 2.2f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 8.9f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{0};
    vt -= Vec3f(-10.4, 0.4, -15.4);
    BOOST_CHECK_CLOSE_FRACTION(vt.x, 10.4f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, -0.4f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 15.4f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{2.5, -0.3, 7.4} - 0.2;
    BOOST_CHECK_CLOSE_FRACTION(vt.x, 2.3f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, -0.5f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 7.2f, FLT_EPSILON);
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    vt -= 3.2f;
    BOOST_CHECK_CLOSE_FRACTION(vt.x, -1.7f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.y, -1.f, FLT_EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(vt.z, 5.7f, FLT_EPSILON);
  }
}

BOOST_AUTO_TEST_SUITE_END()

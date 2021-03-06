/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#include "core/intersection.hpp"
#include "masks/rectangle2.hpp"
#include "tools/planar_intersector.hpp"

#include <cmath>
#include <climits>

#include <gtest/gtest.h>


/// @note __plugin has to be defined with a preprocessor command
using namespace detray;

// Two-dimensional bound frame to surface
__plugin::cartesian2 cartesian2;

// Three-dimensional definitions
using transform3 = __plugin::transform3;
using vector3 = __plugin::transform3::vector3;
using point3 = __plugin::transform3::point3;

constexpr scalar epsilon = std::numeric_limits<scalar>::epsilon();
constexpr scalar isclose = 1e-5;

// This defines the local frame test suite
TEST(__plugin, translated_plane)
{
    // Create a shifted plane
    transform3 shifted(vector3{3., 2., 10.});
    planar_intersector pi;

    auto hit_unbound = pi.intersect(shifted, point3{2., 1., 0.}, vector3{0., 0., 1.});
    ASSERT_TRUE(hit_unbound.status == intersection_status::e_hit);
    ASSERT_TRUE(hit_unbound.direction == intersectiondirection::e_along);
    // Global intersection information
    ASSERT_NEAR(hit_unbound.point3[0], 2., epsilon);
    ASSERT_NEAR(hit_unbound.point3[1], 1., epsilon);
    ASSERT_NEAR(hit_unbound.point3[2], 10., epsilon);
    ASSERT_TRUE(hit_unbound.point2 == std::nullopt);

    // The same test but bound to local frame
    auto hit_bound = pi.intersect(shifted, point3{2., 1., 0.}, vector3{0., 0., 1.}, cartesian2);
    ASSERT_TRUE(hit_bound.status == intersection_status::e_hit);
    // Global intersection information - unchanged
    ASSERT_NEAR(hit_bound.point3[0], 2., epsilon);
    ASSERT_NEAR(hit_bound.point3[1], 1., epsilon);
    ASSERT_NEAR(hit_bound.point3[2], 10., epsilon);
    // Local intersection infoimation
    ASSERT_NEAR(hit_bound.point2.value()[0], -1., epsilon);
    ASSERT_NEAR(hit_bound.point2.value()[1], -1., epsilon);

    // The same test but bound to local frame & masked - inside
    rectangle2<scalar> rect_for_inside = {3., 3.};
    auto hit_bound_inside = pi.intersect(shifted, point3{2., 1., 0.}, vector3{0., 0., 1.}, cartesian2, rect_for_inside);
    ASSERT_TRUE(hit_bound_inside.status == intersection_status::e_inside);
    // Global intersection information - unchanged
    ASSERT_NEAR(hit_bound_inside.point3[0], 2., epsilon);
    ASSERT_NEAR(hit_bound_inside.point3[1], 1., epsilon);
    ASSERT_NEAR(hit_bound_inside.point3[2], 10., epsilon);
    // Local intersection infoimation - unchanged
    ASSERT_NEAR(hit_bound_inside.point2.value()[0], -1., epsilon);
    ASSERT_NEAR(hit_bound_inside.point2.value()[1], -1., epsilon);

    // The same test but bound to local frame & masked - outside
    rectangle2<scalar> rect_for_outside = {0.5, 3.5};
    auto hit_bound_outside = pi.intersect(shifted, point3{2., 1., 0.}, vector3{0., 0., 1.}, cartesian2, rect_for_outside);
    ASSERT_TRUE(hit_bound_outside.status == intersection_status::e_outside);
    // Global intersection information - unchanged
    ASSERT_NEAR(hit_bound_outside.point3[0], 2., epsilon);
    ASSERT_NEAR(hit_bound_outside.point3[1], 1., epsilon);
    ASSERT_NEAR(hit_bound_outside.point3[2], 10., epsilon);
    // Local intersection infoimation - unchanged
    ASSERT_NEAR(hit_bound_outside.point2.value()[0], -1., epsilon);
    ASSERT_NEAR(hit_bound_outside.point2.value()[1], -1., epsilon);
}

// Google Test can be run manually from the main() function
// or, it can be linked to the gtest_main library for an already
// set-up main() function primed to accept Google Test test cases.
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

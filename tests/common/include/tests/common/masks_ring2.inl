/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#include "masks/ring2.hpp"

#include <gtest/gtest.h>

using namespace detray;
using namespace __plugin;

// This tests the basic function of a rectangle
TEST(mask, ring2)
{
    using cartesian = __plugin::cartesian2;
    using polar     = __plugin::polar2;
    using point2_pl = polar::point2;
    using point2_c  = cartesian::point2;

    point2_pl p2_pl_in = {0.5, -2.};
    point2_pl p2_pl_edge = {0., 3.5};
    point2_pl p2_pl_out = {3.6, 5.};

    point2_c p2_c_in = {0.5, -2.};
    point2_c p2_c_edge = {0., 3.5};
    point2_c p2_c_out = {3.5, 3.5};

    ring2<scalar> r2 = {0., 3.5};

    ASSERT_EQ(r2[0], 0.);
    ASSERT_EQ(r2[1], 3.5);

    ASSERT_TRUE(r2.is_inside<polar>(p2_pl_in) == intersection_status::e_inside);
    ASSERT_TRUE(r2.is_inside<polar>(p2_pl_edge) == intersection_status::e_inside);
    ASSERT_TRUE(r2.is_inside<polar>(p2_pl_out) == intersection_status::e_outside);
    // Move outside point inside using a tolerance
    ASSERT_TRUE(r2.is_inside<polar>(p2_pl_out, 1.2, 1.2) == intersection_status::e_inside);

    ASSERT_TRUE(r2.is_inside<cartesian>(p2_c_in) == intersection_status::e_inside);
    ASSERT_TRUE(r2.is_inside<cartesian>(p2_c_edge) == intersection_status::e_inside);
    ASSERT_TRUE(r2.is_inside<cartesian>(p2_c_out) == intersection_status::e_outside);
    // Move outside point inside using a tolerance
    ASSERT_TRUE(r2.is_inside<cartesian>(p2_c_out, 1.45, 1.45) == intersection_status::e_inside);
}

// Google Test can be run manually from the main() function
// or, it can be linked to the gtest_main library for an already
// set-up main() function primed to accept Google Test test cases.
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

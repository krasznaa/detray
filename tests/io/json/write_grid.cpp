/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#include "plugins/array_defs.hpp"
#include "grids/axis.hpp"
#include "grids/grid2.hpp"
#include "grids/populator.hpp"
#include "grids/serializer2.hpp"
#include "json/json_grids.hpp"

#include <fstream>

int main(int argc, char **argv)
{

    using namespace detray;
    std::ofstream output_file;

    replace_populator<guaranteed_index, std::numeric_limits<guaranteed_index>::max()> replacer;
    serializer2 serializer;

    // A rectangular grid 
    axis::closed<10> xaxis{-5., 5.};
    axis::closed<10> yaxis{-5., 5.};
    using grid2r = grid2<decltype(replacer), decltype(xaxis), decltype(yaxis), decltype(serializer)>;

    grid2r gr(std::move(xaxis), std::move(yaxis));

    output_file.open("grid_rect.json");
    output_file << json::write_grid(gr).dump(2);
    output_file.close();

    // A polar sectoral grid
    axis::closed<3> raxis{1., 5.};
    axis::closed<10> phiaxis{-0.35, 0.35};

    using grid2ps = grid2<decltype(replacer), decltype(raxis), decltype(phiaxis), decltype(serializer)>;
    grid2ps gps(std::move(raxis), std::move(phiaxis));

    output_file.open("grid_pol_sect.json");
    output_file << json::write_grid(gps).dump(2);
    output_file.close();
    
    // A full polar grid
    axis::closed<3> radial_axis{1., 5.};
    axis::circular<10> full_phiaxis{-M_PI, M_PI};

    using grid2pf = grid2<decltype(replacer), decltype(radial_axis), decltype(full_phiaxis), decltype(serializer)>;
    grid2pf gpf(std::move(radial_axis), std::move(full_phiaxis));

    output_file.open("grid_pol_full.json");
    output_file << json::write_grid(gpf).dump(2);
    output_file.close();

}
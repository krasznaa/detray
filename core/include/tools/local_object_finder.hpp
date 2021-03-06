
/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#pragma once

namespace detray
{
    /** A zone finder based on a grid */
    template <typename grid_type>
    struct local_zone_finder
    {
        grid_type _grid;
        darray<unsigned int, 2> _nhood = {0, 0};
        bool _sort = true;

        /** Constructor from grid 
         **/
        local_zone_finder(grid_type &&grid)
            : _grid(std::move(grid)) {}

        /** Call operator for the object search 
         * 
         * @tparam point2_type the type of the point for the finding request
         * @param p2 the local 2d point for the grid
         * 
         * @note return a zone around a bin
         **/
        template <typename point2_type>
        auto operator()(const point2_type &p2) const
        {
            return _grid.zone(p2, _nhood, _sort);
        }
    };

    /** A zone finder for a single object */
    template <typename value_type>
    struct local_single_finder
    {

        dvector<value_type> _value = {};

        /** Constructor from a single value */
        local_single_finder(value_type &&value)
        {
            _value = {std::move(value)};
        }

        /** Call operator for the object search
         * 
         * @tparam point2_type the type of the point for the finding request
         * @param p2 the local 2d point for the grid
         * @note return always the same bin 
         **/
        template <typename point2_type>
        dvector<value_type> operator()(const point2_type &p2) const
        {
            return _value;
        }
    };

} // namespace detray
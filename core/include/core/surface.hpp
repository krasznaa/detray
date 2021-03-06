/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */
#pragma once

#include <memory>

namespace detray
{
    /** Templated surface class
     * 
     * @tparam transform_link the type of the transform/transform link for global 3D to local 3D frame
     * @tparam mask_link the type of the mask/mask link representation
     * @tparam volume_link the typ eof the volume/volume link representation
     * @tparam source_link the type of the source/source link representation 
     */
    template <typename transform_link, typename mask_link = int, typename volume_link = int, typename source_link = bool>
    class surface
    {
    public:
        /** Broadcast the transform type */
        using transform3 = transform_link;

        /** Constructor with full arguments
         * 
         * @param trf the transform for positioning and 3D local frame 
         * @param msk the mask/mask link for this surface 
         * @param vol the volume link for this surface
         * @param src the source object/source link this surface is representing
         * 
         **/
        surface(transform_link &&trf, mask_link &&mask, volume_link &&vol, source_link &&src)
            : _trf(std::move(trf)), _mask(std::move(mask)), _vol(std::move(vol)), _src(std::move(src))
        {
        }

        ~surface() = default;
        surface(const surface &lhs) = default;
        surface() = delete;

        /** Equality operator 
         * 
         * @param rhs is the right hand side to be compared to 
        */
        bool operator==(const surface<transform_link, mask_link, source_link> &rhs) const
        {
            return (_trf == rhs.__trf and _mask == rhs._mask and _vol == rhs._vol and _src == rhs._src);
        }

        /** Return the transform type */
        const transform_link &transform() const
        {
            return _trf;
        }

        /** Access to the mask  */
        mask_link &mask()
        {
            return _mask;
        }

        /** Return the mask */
        const mask_link &mask() const
        {
            return _mask;
        }

        /** Access to the volume */
        volume_link &volume()
        {
            return _vol;
        }

        /** Return the mask */
        const volume_link &volume() const
        {
            return _vol;
        }

        /** Return the source/source link type */
        const source_link &source() const
        {
            return _src;
        }

    private:
        transform_link _trf;
        mask_link _mask;
        volume_link _vol;
        source_link _src;
    };
} // namespace detray

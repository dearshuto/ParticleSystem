//
//  mc_bounding_box.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef mc_bounding_box_hpp
#define mc_bounding_box_hpp

#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/surface_construction/marching_cubes_interface.h>

namespace fj {
    class SPHMethod;
    class MCBoundingBox;
}

class fj::MCBoundingBox : public fj::BoundingBox, public MarchingCubesInterface
{
    typedef fj::BoundingBox Super;
public:
    MCBoundingBox() = delete;
    ~MCBoundingBox() = default;
    
    MCBoundingBox(const Range& xRange, const Range& yRange, const Range& zRange)
    : BoundingBox(xRange, yRange, zRange)
    {
        
    }
    void execute(fj::ParticleManager* particleManager, const fj::NeighborMap& neighborMap, const fj::Solver& solver) override;
    
    fj::Scalar getScalar(const int x, const int y, const int z, const fj::Solver& solver)const override;
};

#endif /* mc_bounding_box_hpp */

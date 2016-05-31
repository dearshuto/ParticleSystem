//
//  mc_bounding_box.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef mc_bounding_box_hpp
#define mc_bounding_box_hpp

#include <vector>

#include "partitioned_bounding_box.hpp"
#include <ParticleSystem/solver/surface_construction/marching_cubes_interface.h>

namespace fj {
    class Dynamics;
    class ParticleSystem;
    class MCBoundingBox;
}

class fj::MCBoundingBox : public fj::PartitionedBoundingBox<fj::Scalar>, public MarchingCubesInterface
{
    typedef fj::BoundingBox Super;
public:
    MCBoundingBox() = delete;
    ~MCBoundingBox() = default;
    
    MCBoundingBox(const Range& xRange, const Range& yRange, const Range& zRange, const Resolutions& resolution)
    : PartitionedBoundingBox<fj::Scalar>(xRange, yRange, zRange, resolution)
    {

    }
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override;
    
protected:
    void clearScalarMap(const fj::ParticleManager& particleManager);
    
    void updateScalarMap(const fj::ParticleManager& particleManager, const fj::Dynamics& dynamics);
    
    void setNDInterpolateValue(const int index, const int n, const fj::Scalar& scalar);
    
    void resetNDInterpolateValue(const int index, const int n);
    
    fj::Scalar* getShiftedScalar(const int kIndex, const int x, const int y, const int z);
    
    int getShiftedIndex(const int kIndex, const int x, const int y, const int z)const;
    
public:
    
    fj::Scalar getScalar(const int x, const int y, const int z)const override;
    
    void setScalar(const int x, const int y, const int z, const fj::Scalar& scalar);
    
    void setScalar(const int index, const fj::Scalar& scalar);
    
    void addScalar(const int index, const fj::Scalar& scalar);
    
    void addScalar(const int x, const int y, const int z, const fj::Scalar& scalar);
};

#endif /* mc_bounding_box_hpp */

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

#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/surface_construction/marching_cubes_interface.h>

namespace fj {
    class SPHMethod;
    class ParticleSystem;
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
        m_scalarMap.resize(xRange.getResolusion() * yRange.getResolusion() * zRange.getResolusion());
    }
    void execute(fj::ParticleSystem* particleSystem) override;
    
protected:
    void clearScalarMap(const fj::ParticleManager& particleManager);
    
    void updateScalarMap(const fj::ParticleManager& particleManager, const fj::Solver& solver);
    
    void setScalarValue(const int i, const int j, const int k, const fj::Solver& solver);
    
    void setInterpolateValue(const int i, const int j, const int k, const fj::Scalar& scalar);
    
    void setNDInterpolateValue(const int i, const int j, const int k, const fj::Scalar& scalar, const int n);
    
public:
    
    fj::Scalar getScalar(const int x, const int y, const int z)const override;
    
    void setScalar(const int x, const int y, const int z, const fj::Scalar& scalar);
    
    void setScalar(const int index, const fj::Scalar& scalar);
    
    void addScalar(const int index, const fj::Scalar& scalar);
    
    void addScalar(const int x, const int y, const int z, const fj::Scalar& scalar);
    
private:
    std::vector<fj::Scalar> m_scalarMap;
};

#endif /* mc_bounding_box_hpp */

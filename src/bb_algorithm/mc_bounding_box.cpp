//
//  mc_bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/bb_algorithm/mc_bounding_box.hpp>

void fj::MCBoundingBox::execute(fj::ParticleManager *particleManager, const fj::NeighborMap &neighborMap, const fj::Solver &solver)
{
    Super::execute(particleManager, neighborMap, solver);

}

fj::Scalar fj::MCBoundingBox::getScalar(const int x, const int y, const int z, const fj::Solver& solver)const
{
    const auto& particleIDs = this->get(x, y, z);
    fj::Scalar scalar = fj::Scalar(0);
    
    for (const auto& ID : particleIDs)
    {
        scalar += solver.calculateScalar(ID);
    }
    
    return scalar;
}
//
//  mc_bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/bb_algorithm/mc_bounding_box.hpp>

void fj::MCBoundingBox::execute(fj::ParticleSystem* particleSystem)
{
    Super::execute(particleSystem);

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
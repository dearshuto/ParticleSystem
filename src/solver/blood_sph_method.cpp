//
//  blood_sph_method.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/05.
//
//

#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/solver/blood_sph_method.hpp>

void fj::BloodSPHMethod::compute(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    updateViscosityMap(particleManager, neighborMap);
    Super::compute(particleManager, neighborMap);
}

void fj::BloodSPHMethod::updateViscosityMap(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    static float i = 0;
    for (const auto& particle : particleManager)
    {
        const fj::ParticleID& kID = particle->getID();
        m_viscosityMap[kID] = 1.0 * i;
    }
    
}
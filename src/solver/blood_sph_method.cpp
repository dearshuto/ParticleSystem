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

void fj::BloodSPHMethod::compute(const fj::Scalar& timestep, const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    updateViscosityMap(timestep, particleManager);
    Super::compute(timestep, particleManager, neighborMap);
}

void fj::BloodSPHMethod::updateViscosityMap(const fj::Scalar& timestep, const fj::ParticleManager &particleManager)
{
    constexpr fj::Scalar kMAX = 50;
    
    for (const auto& particle : particleManager)
    {
        const fj::ParticleID& kID = particle->getID();
        const fj::Scalar kViscosity = m_viscosityMap[kID] + 0.001;
        
        if (kViscosity > kMAX)
        {
            m_viscosityMap[kID] = kMAX;
        }
        else
        {
            m_viscosityMap[kID] = kViscosity;
        }
        
    }
    
}
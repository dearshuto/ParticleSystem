//
//  neighbor_map.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <cmath>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>

void fj::NeighborMap::execute(const fj::Scalar &timestep, fj::ParticleSystem *particleSystem)
{
    for (const auto neighborInfo : m_neighbors)
    {
        const fj::ParticleID& kID1 = neighborInfo.first;
        for (const auto& neighbor : neighborInfo.second)
        {
            const fj::ParticleID& kID2 = neighbor.getParticleID();
            
            particleSystem->makeCollision(kID1, kID2, neighbor.getDistance());
        }
        
    }
}

void fj::NeighborMap::registerParticle(const fj::ParticleID &particleID)
{
    m_neighbors[particleID].clear();
}

void fj::NeighborMap::addNeighborInformation(const fj::ParticleID &particle1, const fj::ParticleID &particle2, const fj::ParticleManager& particleManager)
{
    const fj::Particle& kParticle1 =  particleManager.search(particle1);
    const fj::Particle& kParticle2 = particleManager.search(particle2);
    const fj::Vector3 kDirection21 = kParticle1.getPosition() - kParticle2.getPosition();
    const fj::Scalar kDistance = kDirection21.norm();
    
    addNeighborInformation(particle1, particle2, kDistance, particleManager);
}

void fj::NeighborMap::addNeighborInformation(const fj::ParticleID &particle1, const fj::ParticleID &particle2, const fj::Scalar& distance, const fj::ParticleManager& particleManager)
{
    const fj::Particle& kParticle1 = particleManager.search(particle1);
    const fj::Particle& kParticle2 = particleManager.search(particle2);
    const fj::Vector3 kDirection21 = kParticle1.getPosition() - kParticle2.getPosition();
    
    const fj::Scalar kDistance = distance;
    const fj::Scalar kSquaredDistance = std::pow(kDistance, 2);
    const fj::Vector3 kNormalizedDirection21 = kDirection21 / kDistance;
    
    m_neighbors[particle1].emplace_back(particle2, kNormalizedDirection21, kSquaredDistance, kDistance);
}

void fj::NeighborMap::clear()
{
    for (auto& neighbor : m_neighbors)
    {
        neighbor.second.clear();
    }
    
}
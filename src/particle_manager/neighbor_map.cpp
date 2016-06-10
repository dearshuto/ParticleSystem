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

void fj::NeighborMap::allocateMemory(const fj::ParticleManager &particleManager)
{
    auto iterator = particleManager.iterator();
    
    while ( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        m_neighbors[ kParticle.getID() ].shrink_to_fit();
    }
}

void fj::NeighborMap::freeMemoryAt(const fj::ParticleID &ID)
{
    m_neighbors.erase(ID);
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
    
    m_neighbors[particle1].emplace_back(particle1, particle2, kNormalizedDirection21, kSquaredDistance, kDistance);
}

void fj::NeighborMap::clear()
{
    for (auto& neighbor : m_neighbors)
    {
        neighbor.second.clear();
    }
    
}
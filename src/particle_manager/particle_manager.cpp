//
//  particle_manager.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <ParticleSystem/particle/particle.hpp>

#include <ParticleSystem/particle_manager/particle_manager.hpp>

void fj::ParticleManager::registerParticle(std::unique_ptr<fj::Particle> particle, const bool movable)
{
    std::shared_ptr<fj::Particle> sharedParticle = std::move(particle);
    
    m_particles.push_back(sharedParticle);
    m_particleHashMap.registerParticle(sharedParticle);
    
    if (movable)
    {
        m_flowParticles.push_back(sharedParticle);
    }
    else
    {
        m_boundaryParticles.push_back(sharedParticle);
    }
}
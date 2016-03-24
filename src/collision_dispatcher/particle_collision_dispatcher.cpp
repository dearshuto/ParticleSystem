//
//  particle_collision_dispatcher.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle/particle.hpp>

#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

std::vector<const std::shared_ptr<fj::Particle>> fj::ParticleCollisionDispatcher::getNeighborParticlesAt(const fj::Particle &particle)const
{
    std::vector<const std::shared_ptr<fj::Particle>> neighborParticles;
    
    
    return neighborParticles;
}

fj::ParticleCollisionDispatcher::HashValue fj::ParticleCollisionDispatcher::computeHash(const fj::Particle& particle)const
{
    const fj::Vector3& kPosition = particle.getPosition();
    const fj::Scalar& kX = kPosition.x();
    const fj::Scalar& kY = kPosition.y();
    const fj::Scalar& kZ = kPosition.z();
    
    return kX + getWidth() * kY + getWidth() * getHeight() * kZ;
}
//
//  particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <ParticleSystem/particle/particle.hpp>

void fj::Particle::accumulateForce()
{
    accumulateForceByNeighborParticles();
}

void fj::Particle::accumulateForceByNeighborParticles()
{
    fj::Vector3 force(0, 0, 0);
    
    for (std::weak_ptr<fj::Particle>& neighborParticle : *getNeighborParticlesPtr())
    {
        force += affectedBy(neighborParticle);
    }
    
    this->applyForce(force);
}
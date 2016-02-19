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
    updateProperty();
    accumulateForceByNeighborParticles();
}

void fj::Particle::accumulateForceByNeighborParticles()
{
    fj::Vector force(0, 0, 0);
    
    for (std::weak_ptr<fj::Particle>& neighborParticle : *getNeighborParticlesPtr())
    {
        force += affectedBy(neighborParticle);
    }
    
    this->applyForce(force);
}
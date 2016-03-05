//
//  particle_system.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/fluid_particle.hpp>
#include <ParticleSystem/particle/fine_particle.hpp>
#include <ParticleSystem/type/Vector.hpp>

#include <ParticleSystem/particle_system.hpp>

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    simulateParticleBehavior();
    
    if (hasActivatedGravity()) {
        applyGravity();
    }
    
    clearParticleNeighbors();
}

void fj::ParticleSystem::simulateParticleBehavior()
{
    
    for (const std::shared_ptr<fj::Particle> particle : getParticles())
    {
        particle->updateProperty();
    }
    
    for (const std::shared_ptr<fj::Particle> particle : getParticles())
    {
        particle->accumulateForce();
    }
    
}

void fj::ParticleSystem::applyGravity()
{
    const fj::Vector kGravity = getGravity();
    
    for (std::shared_ptr<fj::Particle>& particle : *getParticlesPtr())
    {
        particle->applyForce(kGravity);
    }
    
}

void fj::ParticleSystem::clearParticleNeighbors()
{
    
    for (const std::shared_ptr<fj::Particle> particle : getParticles())
    {
        particle->clearNeighborParticles();
    }
    
}

void fj::ParticleSystem::createFluidParticle(const fj::Vector& position)
{
    std::shared_ptr<fj::Particle> particle = std::make_shared<fj::FluidParticle>(position);
    
    getParticlesPtr()->push_back(particle);
}

void fj::ParticleSystem::createFineParticle(const fj::Vector& position, const float radius, const float mass)
{
    std::shared_ptr<fj::Particle> particle = std::make_shared<fj::FineParticle>(position);
    
    particle->setRadius(radius);
    particle->setMass(mass);
    
    getParticlesPtr()->push_back(particle);
}


void fj::ParticleSystem::makeCollision(const int index1, const int index2)
{
    const std::shared_ptr<fj::Particle>& particle1 = getParticles()[index1];
    const std::shared_ptr<fj::Particle>& particle2 = getParticles()[index2];
    
    particle1->addNeighborParticle(particle2);
}

void fj::ParticleSystem::applyForceFromObject(const int index, const fj::Vector &collisionPoint)
{
    const auto& particle = getParticles()[index];
    const fj::Scalar kDistance = collisionPoint.norm();
    const fj::Vector kNormalizedDirection = (collisionPoint - particle->getPosition()).normalized();
 
    this->applyForceFromObject(index, kDistance, kNormalizedDirection);
 }

void fj::ParticleSystem::applyForceFromObject(const int index, const fj::Scalar& distance, const fj::Vector& normalizedDirection)
{
    getParticles()[index]->affectedByObject(distance, normalizedDirection);
}
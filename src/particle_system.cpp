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
    
    if (hasActivatedGravity()) {
        applyGravity();
    }
    
}

void fj::ParticleSystem::createParticleAt(const float x, const float y, const float z)
{
    const fj::Vector kPosition(x, y, z);
    std::shared_ptr<fj::Particle> particle = std::make_shared<fj::FluidParticle>(kPosition);
    
    getParticlesPtr()->push_back(particle);
}

void fj::ParticleSystem::createFineParticle(const float x, const float y, const float z, const float radius, const float mass)
{
    const fj::Vector kPosition(x, y, z);
    std::shared_ptr<fj::Particle> particle = std::make_shared<fj::FineParticle>(kPosition);

    particle->setRadius(radius);
    particle->setMass(mass);
    
    getParticlesPtr()->push_back(particle);
}

void fj::ParticleSystem::applyGravity()
{
    const fj::Vector kGravity = getGravity();
    
    for (std::shared_ptr<fj::Particle>& particle : *getParticlesPtr())
    {
        particle->applyForce(kGravity);
    }
    
}
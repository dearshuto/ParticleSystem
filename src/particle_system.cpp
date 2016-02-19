//
//  particle_system.cpp
//  blood-simulation
//
//  Created by Shuto Shikama on 2016/02/13.
//
//

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_system.hpp>

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    
}

void fj::ParticleSystem::createParticleAt(const float x, const float y, const float z)
{
    const fj::Vector kPosition(x, y, z);
    std::shared_ptr<fj::Particle> particle = std::make_shared<fj::Particle>(kPosition);
    
    getParticlesPtr()->push_back(particle);
}

void fj::ParticleSystem::applyGravity()
{
    
}
//
//  particle_system.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#include <iostream>
#include <thread>

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
    const int kParticleNum = getParticles().size();
    const int kMaxIndex = kParticleNum - 1;// 例えば50個の要素があればインデックスは0~49
    
    const int kThreadOffset = kMaxIndex / getThreadNum();
    int begin = 0;
    int end = kThreadOffset;
    
    while ( begin <= kMaxIndex )
    {
        updateParticlePropertyWithin_MT(begin, end);

        begin = end + 1;
        end = begin + kThreadOffset;
        end = std::min(end, kMaxIndex);
    }
    
    
    begin = 0;
    end = kThreadOffset;
    
    while ( begin <= kMaxIndex )
    {
        accumulateParticleForceWithin_MT(begin, end);

        begin = end + 1;
        end = begin + kThreadOffset;
        end = std::min(end, kMaxIndex);
    }
    
}

void fj::ParticleSystem::updateParticlePropertyWithin_MT(const int begin, const int end)
{
    std::shared_ptr<fj::Particle> particle;
    
    for (int i = begin; i <= end; i++)
    {
        particle = (*getParticlesPtr())[i];
        particle->updateProperty();
    }
    
}

void fj::ParticleSystem::accumulateParticleForceWithin_MT(const int begin, const int end)
{
    std::shared_ptr<fj::Particle> particle;
    
    for (int i = begin; i < end; i++)
    {
        particle = (*getParticlesPtr())[i];
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

void fj::ParticleSystem::setParticlePositionAt(const int index, const fj::Vector& position)
{
	getParticles()[index]->setPosition(position);
}

void fj::ParticleSystem::setParticleVelocityAt(const int index, const fj::Vector& velocity)
{
	getParticles()[index]->setVelocity(velocity);
}

fj::Vector fj::ParticleSystem::popParticleForceAt(const int index)
{
	return getParticles()[index]->popApliedForce();
}
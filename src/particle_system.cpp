//
//  particle_system.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#define NOMINMAX
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/fluid_particle.hpp>
#include <ParticleSystem/particle/fine_particle.hpp>

#include <ParticleSystem/particle_system.hpp>

void fj::ParticleSystem::initSimulationStatus()
{
    getCollisionDispatcherPtr()->initialize( getParticleManager()) ;
}

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    if (getCollisionDispatcherPtr())
    {
        updateParticleNeighbor();
    }
    
    simulateParticleBehavior();
    
    clearParticleNeighbors();
}

void fj::ParticleSystem::updateParticleNeighbor()
{
    getCollisionDispatcherPtr()->updated();
    
    for (auto& particle : *getParticleManagerPtr())
    {
        auto neighbors = getCollisionDispatcherPtr()->getNeighborParticlesAt(std::ref(*particle));
        
        for (const auto& a : neighbors)
        {
            getNeighborMapPtr()->addNeighborInformation(*particle, *(a.lock()));
        }
        
        particle->moveNeighborParticles( std::move(neighbors) );
    }
    
}

void fj::ParticleSystem::simulateParticleBehavior()
{
    getSolverPtr()->compute(getParticleManager(), getNeighborMap());
//    updateParticleProperty();
//    accumulateParticleForce();
}

void fj::ParticleSystem::updateParticleProperty()
{
    std::vector<std::thread> threds;
    
    const int kParticleNum = getParticleManager().getRegisteredParticleNum();
    const int kMaxIndex = kParticleNum - 1;// 例えば50個の要素があればインデックスは0~49
    
    const int kThreadOffset = kMaxIndex / getThreadNum();
    int begin = 0;
    int end = kThreadOffset;
    
    while ( begin <= kMaxIndex )
    {
        threds.emplace_back(&ParticleSystem::updateParticlePropertyWithin_MT, this, begin, end);
        
        begin = end + 1;
        end = begin + kThreadOffset;
        end = std::min(end, kMaxIndex);
    }
    
    for (auto& thread: threds)
    {
        thread.join();
    }
    
}

void fj::ParticleSystem::updateParticlePropertyWithin_MT(const int begin, const int end)
{
    
    for (int i = begin; i <= end; i++)
    {
        std::shared_ptr<fj::Particle>& particle = getParticleManagerPtr()->getParticleAt(i);
        particle->updateProperty();
    }
    
}

void fj::ParticleSystem::accumulateParticleForce()
{
    std::vector<std::thread> threds;
    
    const int kParticleNum = getParticleManager().getRegisteredParticleNum();
    const int kMaxIndex = kParticleNum - 1;// 例えば50個の要素があればインデックスは0~49
    
    const int kThreadOffset = kMaxIndex / getThreadNum();
    int begin = 0;
    int end = kThreadOffset;
    
    while ( begin <= kMaxIndex )
    {
        threds.emplace_back(&ParticleSystem::accumulateParticleForceWithin_MT, this, begin, end);
        
        begin = end + 1;
        end = begin + kThreadOffset;
        end = std::min(end, kMaxIndex);
    }
    
    for (auto& thread: threds)
    {
        thread.join();
    }

}

void fj::ParticleSystem::accumulateParticleForceWithin_MT(const int begin, const int end)
{
    
    for (int i = begin; i <= end; i++)
    {
        std::shared_ptr<fj::Particle>& particle = getParticleManagerPtr()->getParticleAt(i);
        particle->accumulateForce();
    }
    
}

void fj::ParticleSystem::clearParticleNeighbors()
{
    m_neighborMap.clear();
    for (const std::shared_ptr<fj::Particle> particle : *getParticleManagerPtr())
    {
        particle->clearNeighborParticles();
    }
    
}

void fj::ParticleSystem::createFluidParticle(const fj::Vector3& position, const bool movable)
{
    const fj::ParticleID kID = getParticleManagerPtr()->getUnusedID();
    std::unique_ptr<fj::Particle> fluidParticle(new fj::FluidParticle(kID, position));
    
    getParticleManagerPtr()->registerParticle( std::move(fluidParticle), movable );
}

void fj::ParticleSystem::createFineParticle(const fj::Vector3& position, const float radius, const float mass)
{
    const fj::ParticleID kID = getParticleManagerPtr()->getUnusedID();
    std::unique_ptr<fj::FineParticle> fineParticle(new fj::FineParticle(kID, position));
    
    fineParticle->setRadius(radius);
    fineParticle->setMass(mass);
    
    getParticleManagerPtr()->registerParticle( std::move(fineParticle), false );
}


void fj::ParticleSystem::makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2, const fj::Scalar& distance)
{
    const fj::Particle& particle1 = getParticleManager().search(ID1);
    const fj::Particle& particle2 = getParticleManager().search(ID2);
    
    getNeighborMapPtr()->addNeighborInformation(particle1, particle2);
}

void fj::ParticleSystem::applyForceFromObject(const fj::ParticleID& ID, const fj::Vector3 &collisionPoint)
{
    const auto& particle = getParticleManagerPtr()->search(ID);
    const fj::Scalar kDistance = collisionPoint.norm();
    const fj::Vector3 kNormalizedDirection = (collisionPoint - particle->getPosition()).normalized();
 
    this->applyForceFromObject(ID, kDistance, kNormalizedDirection);
 }

void fj::ParticleSystem::applyForceFromObject(const fj::ParticleID& ID, const fj::Scalar& distance, const fj::Vector3& normalizedDirection)
{
    const std::shared_ptr<fj::Particle>& particle = getParticleManagerPtr()->search(ID);
    particle->affectedByObject(distance, normalizedDirection);
}

void fj::ParticleSystem::setParticlePositionAt(const fj::ParticleID& ID, const fj::Vector3& position)
{
    const std::shared_ptr<fj::Particle>& particle = getParticleManagerPtr()->search(ID);
    particle->setPosition(position);
}

void fj::ParticleSystem::setParticleVelocityAt(const fj::ParticleID& ID, const fj::Vector3& velocity)
{
    const std::shared_ptr<fj::Particle>& particle = getParticleManagerPtr()->search(ID);
    particle->setVelocity(velocity);
}
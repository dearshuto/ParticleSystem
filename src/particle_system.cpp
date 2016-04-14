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
#include <ParticleSystem/particle/particle_id.h>

#include <ParticleSystem/particle_system.hpp>

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    if (getCollisionDispatcherPtr())
    {
        updateParticleNeighbor();
    }
    
    simulateParticleBehavior(timestep);
    
    clearParticleNeighbors();
    
    if (m_bb) {
        m_bb->update(getParticleManager());
        m_marchingCubes.execute(getParticleManager(), *m_bb);
    }
}

void fj::ParticleSystem::stepParticlePosition(const float timestep)
{
    
    for (auto& particle : *getParticleManagerPtr())
    {
        const fj::ParticleID& kID = particle->getID();
        const fj::Vector3& kAccel = getSolverPtr()->getAccellAt(kID);
        
        particle->addVelocity(kAccel * timestep);
        particle->stepSimulation(timestep);
    }
    
}

void fj::ParticleSystem::updateParticleNeighbor()
{
    getCollisionDispatcherPtr()->updated();
    
    for (auto& particle : *getParticleManagerPtr())
    {
        auto neighbors = getCollisionDispatcherPtr()->getNeighborParticlesAt(std::ref(*particle));
        
        for (const auto& neighbor : neighbors)
        {
            makeCollision(particle->getID(), (neighbor.lock())->getID());
        }
        
    }
    
}

void fj::ParticleSystem::simulateParticleBehavior(const fj::Scalar& timestep)
{
    getSolverPtr()->compute(timestep, getParticleManager(), getNeighborMap());
}

void fj::ParticleSystem::clearParticleNeighbors()
{
    m_neighborMap.clear();
}

fj::ParticleID fj::ParticleSystem::createParticle(const fj::Vector3& position, const bool movable)
{
    // 生成した粒子の管理はできるだけfj::ParticleManagerに任せたいので, fj::ParticleManager::registerParticleを最初に呼ぶ.
    const fj::ParticleID kID = getParticleManagerPtr()->getUnusedID();
    std::unique_ptr<fj::Particle> particle(new fj::Particle(kID, position));
    const std::shared_ptr<fj::Particle> sharedParticle = getParticleManagerPtr()->registerParticle( std::move(particle), movable );
    
    getNeighborMapPtr()->registerParticle( std::cref(*sharedParticle) );
    
    if (getCollisionDispatcherPtr())
    {
        getCollisionDispatcherPtr()->registerParticle(sharedParticle);
    }
    
    return kID;
}

void fj::ParticleSystem::makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2, const fj::Scalar& distance)
{
    const fj::Particle& particle1 = getParticleManager().search(ID1);
    const fj::Particle& particle2 = getParticleManager().search(ID2);
    
    getNeighborMapPtr()->addNeighborInformation(particle1, particle2, distance);
}

void fj::ParticleSystem::makeCollision(const fj::ParticleID &ID1, const fj::ParticleID &ID2)
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
//    particle->affectedByObject(distance, normalizedDirection);
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

void fj::ParticleSystem::addAccelAt(const fj::ParticleID &ID, const fj::Vector3 &accel)
{
    getSolverPtr()->addAccelAt(ID, accel);
}
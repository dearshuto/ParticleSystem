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

void fj::ParticleSystem::addSolver(std::unique_ptr<fj::Solver> solver)
{
    m_solvers.push_back( std::move(solver) );
    std::sort(std::begin(m_solvers), std::end(m_solvers)
              , [](std::shared_ptr<fj::Solver> s1, std::shared_ptr<fj::Solver> s2)
              {
                  return  (s2->getPriority() < s1->getPriority() );
              }
              );
}

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    
    for (const auto& solver : m_solvers)
    {
        solver->execute(timestep, this);
    }
    
    for (const auto& solver : m_solvers)
    {
        solver->postexecute(timestep, this);
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
    
    getSolverPtr()->clearAccel();
}

void fj::ParticleSystem::simulateParticleBehavior(const fj::Scalar& timestep)
{    
    if (m_enableGravity)
    {
        applyGravity();
    }
}

void fj::ParticleSystem::applyGravity()
{
    const fj::Vector3& kGravity = getGravity();
    auto iterator = getParticleManager().iterator();

    while ( iterator->hasNext() )
    {
        const fj::ParticleID& kID = (iterator->next()).getID();
        
        getSolverPtr()->addAccelAt(kID, kGravity);
    }
}

const fj::ParticleID& fj::ParticleSystem::createParticle(const fj::Vector3& position, const bool movable)
{
    // 生成した粒子の管理はできるだけfj::ParticleManagerに任せたいので, fj::ParticleManager::registerParticleを最初に呼ぶ.
    const fj::ParticleID& kID = getParticleManagerPtr()->getUnusedID();
    std::unique_ptr<fj::Particle> particle(new fj::Particle(kID, position));
    const fj::Particle& kRegisteredParticle = getParticleManagerPtr()->registerParticle( std::move(particle), movable );
    
    getNeighborMapPtr()->registerParticle( kID );
        
    return kRegisteredParticle.getID();
}

void fj::ParticleSystem::makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2, const fj::Scalar& distance)
{
    getNeighborMapPtr()->addNeighborInformation(ID1, ID2, distance, getParticleManager());
}

void fj::ParticleSystem::makeCollision(const fj::ParticleID &ID1, const fj::ParticleID &ID2)
{
    getNeighborMapPtr()->addNeighborInformation(ID1, ID2, getParticleManager());
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
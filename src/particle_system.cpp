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

#include <ParticleSystem/solver/additional_simulation/additional_simulation.hpp>
#include <ParticleSystem/solver/bb_algorithm/bb_algorithm.h>
#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/solver/surface_construction/surface_construction.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/solver/dynamics/dynamics.hpp>

#include <ParticleSystem/particle_system.hpp>

void fj::ParticleSystem::allocateMemory()
{
    m_solverManager.allocateMomory( getParticleManager() );
    m_neighborMap.allocateMemory( getParticleManager() );
}

void fj::ParticleSystem::removeParticle(const fj::ParticleID &ID)
{
    // ParticleManagerから粒子を削除する
    // 削除が終わったら、各クラスにおいてメモリを削除して最適化する
    
    m_solverManager.freeSimulationMemory(ID);
    m_neighborMap.freeMemoryAt(ID);
    m_particleManager.removeParticle(ID);
}

void fj::ParticleSystem::addSolver(std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher)
{
    m_solverManager.addSolver( std::move(collisionDispatcher) );
}

void fj::ParticleSystem::addSolver(std::unique_ptr<fj::BBAlgorithm> bbAlgorithm)
{
    m_solverManager.addSolver(std::move(bbAlgorithm));
}

void fj::ParticleSystem::addSolver(std::unique_ptr<fj::SurfaceConstruction> surfaceConstruction)
{
    m_solverManager.addSolver(std::move(surfaceConstruction));
}

void fj::ParticleSystem::addSolver(std::unique_ptr<fj::AdditionalSimulation> additionalSolver)
{
    m_solverManager.addSolver( std::move(additionalSolver) );
}

void fj::ParticleSystem::stepSimulation(const float timestep)
{
    for (const auto& solver : m_solverManager)
    {
        solver->execute(timestep, this);
    }

    for (const auto& solver : m_solverManager)
    {
        solver->postexecute(timestep, this);
    }
    
    getNeighborMapPtr()->clear();
}

void fj::ParticleSystem::stepParticlePosition(const float timestep)
{
    
    for (auto& particle : *getParticleManagerPtr()->getFlowParticlesPtr())
    {
        const fj::ParticleID& kID = particle->getID();
        const fj::Vector3& kAccel = getDynamicsPtr()->getAccellAt(kID);
        
        particle->addVelocity(kAccel * timestep);
        particle->stepSimulation(timestep);
    }
    
    getDynamicsPtr()->clearAccel();
}

const fj::ParticleID& fj::ParticleSystem::createParticle(const fj::Vector3& position, const bool movable)
{
    // 生成した粒子の管理はできるだけfj::ParticleManagerに任せたいので, fj::ParticleManager::registerParticleを最初に呼ぶ.
    const fj::ParticleID& kID = getParticleManagerPtr()->getUnusedID();
    std::unique_ptr<fj::Particle> particle(new fj::Particle(kID, position));
    const fj::Particle& kRegisteredParticle = getParticleManagerPtr()->registerParticle( std::move(particle), movable );
    
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

void fj::ParticleSystem::allocateIsosurface(const fj::Scalar &level)
{
    m_solverManager.allocateIsosurface(level);
}

void fj::ParticleSystem::clearMesh()
{
    
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

const fj::Vector3& fj::ParticleSystem::getAppliedAccel(const fj::ParticleID &ID)const
{
    return m_solverManager.getDynamics().getAccellAt(ID);
}

void fj::ParticleSystem::addAccelAt(const fj::ParticleID &ID, const fj::Vector3 &accel)
{
    getDynamicsPtr()->addAccelAt(ID, accel);
}
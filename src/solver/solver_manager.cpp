//
//  solver_manager.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/22.
//
//

#include <algorithm>
#include <memory>

#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/solver/additional_simulation/additional_simulation.hpp>
#include <ParticleSystem/solver/bb_algorithm/bb_algorithm.h>
#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/solver/dynamics/dynamics.hpp>
#include <ParticleSystem/solver/surface_construction/surface_construction.hpp>

#include <ParticleSystem/solver/solver_manager.hpp>

void fj::SolverManager::allocateMomory(const fj::ParticleManager& particleManager)
{
    for (auto& solver : getSolversPtr())
    {
        solver->allocateMemory(particleManager);
    }
    
}

void fj::SolverManager::addSolver(std::unique_ptr<fj::Dynamics> dynamics)
{
    std::shared_ptr<fj::Dynamics> sharedDynamics = std::move(dynamics);

    removeCurrentDynamics();
    
    m_dynamics = sharedDynamics;
    stackSolver(sharedDynamics);
}

void fj::SolverManager::addSolver(std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispathcer)
{
    stackSolver( std::move(collisionDispathcer) );
}

void fj::SolverManager::addSolver(std::unique_ptr<fj::BBAlgorithm> bbAlgorithm)
{
    stackSolver( std::move(bbAlgorithm) );
}

void fj::SolverManager::addSolver(std::unique_ptr<fj::SurfaceConstruction> surfaceConstruction)
{
    std::shared_ptr<fj::SurfaceConstruction> sharedSurface = std::move(surfaceConstruction);
    
    removeCurrentSurfaceConstruction();
    
    m_surfaceConstrucsion = sharedSurface;
    stackSolver( sharedSurface );
}

void fj::SolverManager::addSolver(std::unique_ptr<fj::AdditionalSimulation> additionalSimulation)
{
    stackSolver( std::move(additionalSimulation) );
}

void fj::SolverManager::removeCurrentDynamics()
{
    auto currentDynamics = std::find(std::begin(m_solvers), std::end(m_solvers), m_dynamics);
    if (currentDynamics != std::end(m_solvers))
    {
        m_solvers.erase(currentDynamics);
    }
}

void fj::SolverManager::removeCurrentSurfaceConstruction()
{
    auto currentDynamics = std::find(std::begin(m_solvers), std::end(m_solvers), m_surfaceConstrucsion);
    if (currentDynamics != std::end(m_solvers))
    {
        m_solvers.erase(currentDynamics);
    }
}

void fj::SolverManager::stackSolver(std::shared_ptr<fj::Solver> solver)
{
    m_solvers.push_back( std::move(solver) );
    std::sort(std::begin(m_solvers), std::end(m_solvers)
              , [](std::shared_ptr<fj::Solver> s1, std::shared_ptr<fj::Solver> s2)
              {
                  return  (s2->getPriority() < s1->getPriority() );
              }
              );
}

const fj::Mesh& fj::SolverManager::getMesh(const unsigned int index)const
{
    return std::cref( m_surfaceConstrucsion->getMesh(index) );
}
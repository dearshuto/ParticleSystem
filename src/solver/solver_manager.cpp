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
#include <ParticleSystem/solver/dynamics/dynamics.hpp>

#include <ParticleSystem/solver/solver_manager.hpp>

void fj::SolverManager::addSolver(std::unique_ptr<fj::Dynamics> dynamics)
{
    std::shared_ptr<fj::Dynamics> sharedDynamics = std::move(dynamics);

    removeCurrentDynamics();
    
    m_dynamics = sharedDynamics;
}

void fj::SolverManager::removeCurrentDynamics()
{
    auto currentDynamics = std::find(std::begin(m_solvers), std::end(m_solvers), m_dynamics);
    if (currentDynamics != std::end(m_solvers))
    {
        m_solvers.erase(currentDynamics);
    }
}

void fj::SolverManager::addSolver(std::shared_ptr<fj::Solver> solver)
{
    m_solvers.push_back( std::move(solver) );
    std::sort(std::begin(m_solvers), std::end(m_solvers)
              , [](std::shared_ptr<fj::Solver> s1, std::shared_ptr<fj::Solver> s2)
              {
                  return  (s2->getPriority() < s1->getPriority() );
              }
              );
}
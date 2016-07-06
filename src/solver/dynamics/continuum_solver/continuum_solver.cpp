//
//  continuum_solver.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/18.
//
//

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/continuum_solver.hpp>

void fj::ContinuumSolver::allocateMemoryAt(const fj::ParticleID &ID)
{
    m_accelMap[ ID ] = fj::Vector3(0, 0, 0);
    allocateContinuumMemoryAt(ID);
}

void fj::ContinuumSolver::freeDynamicsMemoryAt(const fj::ParticleID &ID)
{
    m_accelMap.erase(ID);
    freeContinuumMemoryAt(ID);
}
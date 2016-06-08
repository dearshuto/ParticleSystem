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

void fj::ContinuumSolver::allocateMemory(const fj::ParticleManager &particleManager)
{
    auto iterator = particleManager.iterator();
    
    while ( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        m_accelMap[ kParticle.getID() ] = fj::Vector3(0, 0, 0);
    }
}
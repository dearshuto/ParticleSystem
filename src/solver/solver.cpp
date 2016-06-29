//
//  solver.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/solver.hpp>

void fj::Solver::allocateMemory(const fj::ParticleManager &particleManager)
{
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        
        allocateMemoryAt( kParticle.getID() );
    }
}
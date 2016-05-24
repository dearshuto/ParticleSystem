//
//  gravity_force.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/19.
//
//

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>

#include <ParticleSystem/solver/dynamics/external_force/gravity_force.hpp>

void fj::GravityForce::executeDynamics(const fj::Scalar &timestep, fj::ParticleSystem *particleSystem)
{
    getDynamicsPtr()->executeDynamics(timestep, particleSystem);
    
    const fj::ParticleManager& kParticleManager = particleSystem->getParticleManager();
    auto iterator = kParticleManager.iterator();
    
    while(iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        
        getDynamicsPtr()->addAccelAt(kID, getGravity());
    }
}
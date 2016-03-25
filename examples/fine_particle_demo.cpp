//
//  fluid_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/25.
//
//

#include <iostream>
#include <memory>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

int main(int argc, char** argv)
{
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10));
    fj::ParticleSystem particleSystem( std::move(collisionDispatcher) );
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                particleSystem.createFluidParticle(fj::Vector3(i, j, k));
            }
        }
    }
    
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    
    for (const auto& particle: particleSystem.getParticleManager())
    {
        particle->popApliedForce().print();
    }
    
    return EXIT_SUCCESS;
}
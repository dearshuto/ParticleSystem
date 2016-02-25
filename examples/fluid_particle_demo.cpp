//
//  fine_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/21.
//
//

#include <iostream>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/type/Scalar.h>

int main(int argc, char** argv)
{
    const fj::Scalar kRafius(0.1);
    const fj::Scalar kMass(1);
    
    fj::ParticleSystem particleSystem;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 10; k++) {
                particleSystem.createFineParticle(i, j, k, kRafius, kMass);
            }
        }
    }
    
    particleSystem.makeCollision(0, 1);
    particleSystem.makeCollision(0, 2);
    particleSystem.makeCollision(0, 3);
    
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    
    for (const auto& particle: particleSystem.getParticles())
    {
        particle->popApliedForce().print();
    }
    
    return EXIT_SUCCESS;
}
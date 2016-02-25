//
//  fluid_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/25.
//
//

#include <iostream>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/type/scalar.h>

int main(int argc, char** argv)
{
    fj::ParticleSystem particleSystem;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                particleSystem.createFluidParticle(fj::Vector(i, j, k));
            }
        }
    }
    
    particleSystem.makeCollision(0, 1);
    particleSystem.makeCollision(1, 0);
    
    particleSystem.makeCollision(0, 2);
    particleSystem.makeCollision(2, 0);
    
    particleSystem.makeCollision(0, 3);
    particleSystem.makeCollision(3, 0);
    
    particleSystem.makeCollision(0, 4);
    particleSystem.makeCollision(4, 0);
    
    particleSystem.makeCollision(0, 5);
    particleSystem.makeCollision(5, 0);
    
    particleSystem.makeCollision(0, 6);
    particleSystem.makeCollision(6, 0);
    
    particleSystem.makeCollision(0, 7);
    particleSystem.makeCollision(7, 0);
    
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    
    for (const auto& particle: particleSystem.getParticles())
    {
        particle->popApliedForce().print();
    }
    
    return EXIT_SUCCESS;
}
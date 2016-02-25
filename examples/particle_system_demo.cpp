//
//  particle_system_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#include <iostream>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/type/scalar.h>

int main(int argc, char** argv)
{
    fj::ParticleSystem particleSystem;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 10; k++) {
                particleSystem.createParticleAt(i, j, k);
            }
        }
    }
    
    particleSystem.stepSimulation( fj::Scalar(1) / fj::Scalar(60) );
    
    for (const auto& particle: particleSystem.getParticles())
    {
        particle->popApliedForce().print();
    }
    
    return EXIT_SUCCESS;
}
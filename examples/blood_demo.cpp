//
//  blood_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/04/05.
//
//

#include <iostream>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/blood_particle_system.hpp>

int main(int argc, char** argv)
{

    std::unique_ptr<fj::BloodSPHMethod> solver;
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher;
    fj::BloodParticleSystem particleSystem(std::move(solver), std::move(collisionDispatcher));
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 10; k++) {
                particleSystem.createParticle( fj::Vector3(i, j, k) );
            }
        }
    }
    
    
    return EXIT_SUCCESS;
}
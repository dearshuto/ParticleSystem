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
#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/solver/sph_method.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    std::unique_ptr<fj::SPHMethod> solver(new fj::SPHMethod);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    fj::ParticleSystem particleSystem(std::move(solver), std::move(collisionDispatcher) );
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 1; k++) {
                particleSystem.createParticle(fj::Vector3(fj::Scalar(i) * kParticleRadius, fj::Scalar(j) * kParticleRadius, 0));
            }
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        auto iterator = particleSystem.getParticleManager().iterator();
        
        particleSystem.stepSimulation(kTimestep);
        particleSystem.stepParticlePosition(kTimestep);
        
        
        while ( iterator->hasNext() )
        {
            const fj::Particle& kParticle = iterator->next();
            
            std::cout << kParticle.getID().getData() << ": ";
            kParticle.getVelocity().print();
        }
        
    }
    
    return EXIT_SUCCESS;
}
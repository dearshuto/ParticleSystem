//
//  fluid_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/25.
//
//

#include <iostream>
#include <memory>

#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/solver/sph_method.hpp>
#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    std::unique_ptr<fj::SPHMethod> solver(new fj::SPHMethod);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    fj::ParticleSystem particleSystem(std::move(solver), std::move(collisionDispatcher) );
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < 1; k++) {
                particleSystem.createParticle(fj::Vector3(fj::Scalar(i) * kParticleRadius, fj::Scalar(j) * kParticleRadius, 0));
            }
        }
    }
    

    
    for (int i = 0; i < 3; i++) {
        std::cout << std::endl;
        std::cout << "step: " << (i + 1) << std::endl;
        particleSystem.stepSimulation( kTimestep );
        for (const auto& particle: particleSystem.getParticleManager())
        {
            const fj::Vector3 kAccel =  particleSystem.getAppliedAccel(particle->getID());// particle->popApliedForce();
            particle->addVelocity(kAccel * kTimestep);
            particle->addPosition(particle->getVelocity() * kTimestep);
            
//            if ( (i % 10) == 0)
            {
//                std::cout << particle->getID().getData() << ": ";
//                std::cout << "accel";
//                kAccel.print();
//                std::cout << "pressure: " << particle->getPressure() << std::endl;
//                
//                std::cout << "velocity";
//                particle->getVelocity().print();
//                std::cout << "position";
//                particle->getPosition().print();
            }
        }

    }
    
    return EXIT_SUCCESS;
}
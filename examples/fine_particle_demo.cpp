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
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_dem.hpp>
#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kOffset = 0.01 * 0.65;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    std::unique_ptr<fj::SPHDEM> solver(new fj::SPHDEM);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    fj::ParticleSystem particleSystem(std::move(solver) );
    
    particleSystem.addSolver( std::move(collisionDispatcher) );
    
    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            for (int k = 0; k < 1; k++) {
                particleSystem.createParticle(fj::Vector3(fj::Scalar(i) * kOffset, fj::Scalar(j) * kOffset, 0));
            }
        }
    }
    
    for (int i = 0; i < 30; i++)
    {
        particleSystem.stepSimulation( kTimestep );
        particleSystem.stepParticlePosition(kTimestep);
    }
    
    return EXIT_SUCCESS;
}
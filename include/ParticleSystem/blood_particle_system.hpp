//
//  blood_particle_system.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/05.
//
//

#ifndef blood_particle_system_hpp
#define blood_particle_system_hpp

#include <memory>

#include <ParticleSystem/solver/BloodSPHMethod.hpp>
#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>
#include "particle_system.hpp"

namespace fj {
    class Solver;
    class BloodParticleSystem;
}

class fj::BloodParticleSystem : public fj::ParticleSystem
{
public:
    BloodParticleSystem() = delete;
    ~BloodParticleSystem() = default;
    
    BloodParticleSystem(std::unique_ptr<fj::BloodSPHMethod> solver, std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher = nullptr)
    : ParticleSystem(std::move(solver), std::move(collisionDispatcher))
    {
        
    }
};

#endif /* blood_particle_system_hpp */

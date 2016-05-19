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

#include "particle_system.hpp"
#include "solver/dynamics/continuum_solver/blood_sph_method.hpp"
#include "solver/collision_dispatcher/particle_collision_dispatcher.hpp"

namespace fj {
    class Solver;
    class BloodParticleSystem;
}

/**
 * 血液のシミュレーション
 */
class fj::BloodParticleSystem : public fj::ParticleSystem
{
    typedef fj::ParticleSystem Super;
public:
    BloodParticleSystem() = delete;
    ~BloodParticleSystem() = default;
    
    BloodParticleSystem(std::unique_ptr<fj::BloodSPHMethod> solver)
    : ParticleSystem(std::move(solver))
    {
        
    }
    
};

#endif /* blood_particle_system_hpp */

//
//  fluid_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fluid_particle_hpp
#define fluid_particle_hpp

#include <ParticleSystem/particle/particle.hpp>

namespace fj {
    class Vector;
    class FluidParticle;
}

class fj::FluidParticle : public fj::Particle
{
public:
    FluidParticle() = default;
    virtual ~FluidParticle() = default;
    
    FluidParticle(const fj::FluidParticle& other) = delete;
    FluidParticle& operator=(const fj::FluidParticle& other) = delete;
    
    FluidParticle(const fj::Vector& position)
    : Particle(position)
    {
        
    }
    
    fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
};

#endif /* fluid_particle_hpp */

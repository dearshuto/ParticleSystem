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
#include <ParticleSystem/type/Scalar.h>

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
    
    void updateProperty()override;
    fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
    fj::Vector affect(const fj::Particle& particle)const override;
    
    void inverseItsRho()
    {
        setDensity( fj::Scalar(1) / getDensity() );
    }

private:
    fj::Vector computeForceFromObject(const fj::Vector& collisionPoint)const override;
    
// getters & setters
public:
    
        
private:

};

#endif /* fluid_particle_hpp */

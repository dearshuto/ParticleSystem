//
//  fluid_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fluid_particle_hpp
#define fluid_particle_hpp

#include <FUJIMath/type/scalar.h>

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
    
    FluidParticle(const fj::Vector3& position)
    : Particle(position)
    {
        
    }
    
    void updateProperty()override;
    fj::Vector3 affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
    fj::Vector3 affect(const fj::Particle& particle)const override;
    
    void inverseItsRho()
    {
        setDensity( fj::Scalar(1) / getDensity() );
    }

private:
    fj::Vector3 computeForceFromObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)const override;
};

#endif /* fluid_particle_hpp */

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

#include "particle.hpp"
#include "particle_id.h"

namespace fj {
    class Vector;
    class FluidParticle;
}

class fj::FluidParticle : public fj::Particle
{
public:
    FluidParticle() = delete;
    virtual ~FluidParticle() = default;
    
    FluidParticle(const fj::FluidParticle& other) = delete;
    FluidParticle& operator=(const fj::FluidParticle& other) = delete;
    
    FluidParticle(const fj::ParticleID& ID, const fj::Vector3& position)
    : Particle(ID, position)
    {
        
    }
    
    void updateProperty()override;
    fj::Vector3 affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
    fj::Vector3 affect(const fj::Particle& particle)const override;
    
    void inverseItsRho()
    {
        setDensity( fj::Scalar(1) / getDensity() );
    }

    void updateInverseDensity()
    {
        m_inverseDensity = fj::Scalar(1) / getDensity();
    }
    
    fj::Scalar getInverseDensity()const
    {
        return m_inverseDensity;
    }
    
private:
    fj::Vector3 computeForceFromObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)const override;
    
private:
    fj::Scalar m_inverseDensity;
};

#endif /* fluid_particle_hpp */

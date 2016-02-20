//
//  fine_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fine_particle_hpp
#define fine_particle_hpp

#include <ParticleSystem/type/Scalar.h>
#include <ParticleSystem/particle/particle.hpp>

namespace fj {
    class FineParticle;
}

class fj::FineParticle : public fj::Particle
{
public:
    FineParticle() = default;
    ~FineParticle() = default;
    
    FineParticle(const fj::FineParticle& other) = delete;
    
    FineParticle(const fj::Vector& position)
    : fj::Particle(position)
    {
        
    }
    
    FineParticle& operator=(const fj::FineParticle& other) = delete;
    
    void updateProperty() override;
    
    fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
    fj::Vector affect(const fj::Particle& particle)const override;

private:
    fj::Vector computeVanderWaalsForce(const fj::Particle& particle)const;
};

#endif /* fine_particle_hpp */

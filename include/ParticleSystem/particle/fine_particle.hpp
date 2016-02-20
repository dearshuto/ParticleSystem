//
//  fine_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fine_particle_hpp
#define fine_particle_hpp

#include <ParticleSystem/particle/particle.hpp>

namespace fj {
    class FineParticle;
}

class fj::FineParticle : public fj::Particle
{
public:
    FineParticle() = default;
    ~FineParticle() = default;
    
    void updateProperty() override;
    
    fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;
    fj::Vector affect(const fj::Particle& particle)const override;
};

#endif /* fine_particle_hpp */

//
//  fine_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fine_particle_hpp
#define fine_particle_hpp

#include <FUJIMath/type/scalar.h>

#include "particle.hpp"
#include "particle_id.h"


namespace fj {
    class FineParticle;
}

class fj::FineParticle : public fj::Particle
{
public:
    FineParticle() = default;
    ~FineParticle() = default;
    
    FineParticle(const fj::FineParticle& other) = delete;
    
    FineParticle(const fj::ParticleID& ID, const fj::Vector3& position)
    : fj::Particle(ID, position)
    {
        
    }
    
    FineParticle& operator=(const fj::FineParticle& other) = delete;
    
    void updateProperty() override;

    fj::Vector3 affect(const fj::Particle& particle)const override;
    fj::Vector3 affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;

private:
    fj::Vector3 computeVanderWaalsForce(const fj::Particle& particle)const;
    
    /**
     * @param convertedRadius 換算粒子径
     * @oaram distance 2物体の表万間距離
     * @param normalizedDirection 正規化してある力の方向
     */
    fj::Vector3 VanderWaalsFomula(const fj::Scalar convertedRadius, const fj::Scalar distance, const fj::Vector3& normalizedDirection)const;
    
    fj::Vector3 computeForceFromObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)const override;
};

#endif /* fine_particle_hpp */

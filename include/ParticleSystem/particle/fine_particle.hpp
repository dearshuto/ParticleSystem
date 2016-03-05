//
//  fine_particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef fine_particle_hpp
#define fine_particle_hpp

#include <ParticleSystem/type/scalar.h>
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

    fj::Vector affect(const fj::Particle& particle)const override;
    fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) override;

private:
    fj::Vector computeVanderWaalsForce(const fj::Particle& particle)const;
    
    /**
     * @param convertedRadius 換算粒子径
     * @oaram distance 2物体の表万間距離
     * @param normalizedDirection 正規化してある力の方向
     */
    fj::Vector VanderWaalsFomula(const fj::Scalar convertedRadius, const fj::Scalar distance, const fj::Vector& normalizedDirection)const;
    
    fj::Vector computeForceFromObject(const fj::Scalar& distance, const fj::Vector& normalizedDirection)const override;
};

#endif /* fine_particle_hpp */

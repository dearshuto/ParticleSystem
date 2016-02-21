//
//  fine_particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <cassert>
#include <functional>
#include <memory>

#include <ParticleSystem/type/Scalar.h>
#include <ParticleSystem/type/Vector.hpp>

#include <ParticleSystem/particle/fine_particle.hpp>

void fj::FineParticle::updateProperty()
{
    
}

fj::Vector fj::FineParticle::affect(const fj::Particle &particle)const
{
    const fj::Vector kVanderWaalsForce = computeVanderWaalsForce(particle);
    
    return kVanderWaalsForce;
}

fj::Vector fj::FineParticle::computeVanderWaalsForce(const fj::Particle &particle)const
{
    // 参考文献
    //粉体工学叢書 第7巻 「粉体層の操作とシミュレーション」 p11
    
    const fj::Vector kRelativePosition = this->getPosition() - particle.getPosition();
    
    const fj::Scalar kHamakerConstant = fj::Scalar(1);
    const fj::Scalar kConvertedParticleRadius = (this->getRadius() * particle.getRadius()) / (this->getRadius() + particle.getRadius());
    
    const fj::Scalar kDistance = kRelativePosition.norm();
    const fj::Scalar kSurfaceDistance = kDistance - (this->getRadius() + particle.getRadius());
    const fj::Vector kDirection = kRelativePosition.normalized();
    
    return kDirection * kHamakerConstant * kConvertedParticleRadius / (fj::Scalar(12) * std::pow(kSurfaceDistance, 2));
}

fj::Vector fj::FineParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticleWeakPtr)
{
    const std::shared_ptr<fj::Particle> neighborParticle = neighborParticleWeakPtr.lock();
    assert( !neighborParticleWeakPtr.expired() );
    
    return neighborParticle->affect( std::cref(*this) );
}

fj::Vector fj::FineParticle::computeForceFromObject(const fj::Scalar distance)const
{
    return fj::Vector(0, 0, 0);
}
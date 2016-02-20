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

#include <ParticleSystem/type/Vector.hpp>
#include <ParticleSystem/particle/fine_particle.hpp>

void fj::FineParticle::updateProperty()
{
    
}

fj::Vector fj::FineParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticleWeakPtr)
{
    const std::shared_ptr<fj::Particle> neighborParticle = neighborParticleWeakPtr.lock();
    assert( neighborParticleWeakPtr.expired() );
    
    return neighborParticle->affect( std::cref(*this) );
}
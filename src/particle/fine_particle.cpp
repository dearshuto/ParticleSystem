//
//  fine_particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <ParticleSystem/type/Vector.hpp>
#include <ParticleSystem/particle/fine_particle.hpp>

void fj::FineParticle::updateProperty()
{
    
}

fj::Vector fj::FineParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticle)
{
    return fj::Vector(0, 0, 0);
}
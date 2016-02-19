//
//  fluid_particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <ParticleSystem/particle/fluid_particle.hpp>

fj::Vector fj::FluidParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticle)
{
    return fj::Vector(0, 0, 0);
}
//
//  vector_particle_map.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/23.
//
//

#include <functional>
#include <memory>

#include <ParticleSystem/neighbor_search/vector_particle_map.hpp>

void fj::VectorParticleMap::registerParticle(std::shared_ptr<fj::Particle> particle)
{
    getParticlesPtr()->push_back(particle);
}

const fj::Particle& fj::VectorParticleMap::getParticleAt(const unsigned int id)const
{
    const std::shared_ptr<fj::Particle>& kParticle = getParticles()[id];
    
    return std::cref(*kParticle);
}
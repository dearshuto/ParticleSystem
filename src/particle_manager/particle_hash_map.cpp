//
//  particle_hash_map.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <ParticleSystem/particle/particle.hpp>

#include <ParticleSystem/neighbor_search/particle_hash_map.hpp>

void fj::ParticleHashMap::registerParticle(std::shared_ptr<fj::Particle> particle)
{
    const unsigned int kID = particle->getID();
    
    m_hashMap[kID] = particle;
}

int fj::ParticleHashMap::getUnusedID()
{
    // IDは毎回違う数字を用意できればなんでもいい
    // そこでこの関数がよばれた回数をIDにしておく
    static unsigned int count = 0;
    
    return count++;
}
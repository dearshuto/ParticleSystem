//
//  particle_manager.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_manager_hpp
#define particle_manager_hpp

#include <memory>
#include <vector>

#include <ParticleSystem/particle/particle_id.h>
#include "particle_hash_map.hpp"

namespace fj {
    class Particle;
    class ParticleManager;
}

class fj::ParticleManager
{
    typedef std::vector<std::shared_ptr<fj::Particle>> ParticleArray;
public:
    ParticleManager() = default;
    ~ParticleManager() = default;
    
    void registerParticle(const std::unique_ptr<fj::Particle> particle);
    
    std::shared_ptr<fj::Particle>& getParticleAt(const int i);
    
    std::shared_ptr<fj::Particle>& search(const fj::ParticleID& ID);
    
    ParticleArray::iterator begin()
    {
        return std::begin(m_particles);
    }

    ParticleArray::iterator end()
    {
        return std::end(m_particles);
    }
    
public:
    
    size_t getRegisteredParticleNum()const
    {
        return m_particles.size();
    }
    
private:
    ParticleArray m_particles;
    fj::ParticleHashMap m_particleHashMap;
};

#endif /* particle_manager_hpp */

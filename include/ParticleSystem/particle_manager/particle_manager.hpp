//
//  particle_manager.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_manager_hpp
#define particle_manager_hpp

#include <functional>
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
    class ConstIterator;
public:
    ParticleManager() = default;
    ~ParticleManager() = default;
    
    const std::shared_ptr<fj::Particle> registerParticle(std::unique_ptr<fj::Particle> particle, const bool movable);
    
    std::shared_ptr<fj::Particle>& getParticleAt(const int i)
    {
        return std::ref(m_particles[i]);
    }
    
    std::shared_ptr<fj::Particle>& search(const fj::ParticleID& ID)
    {
        return std::ref(m_particleHashMap.get(ID));
    }
    
    const fj::Particle& search(const fj::ParticleID& ID)const
    {
        return m_particleHashMap.get(ID);
    }
    
    ParticleArray::iterator begin()
    {
        return std::begin(m_particles);
    }

//    ParticleArray::const_iterator begin()const
//    {
//        return std::begin(m_particles);
//    }
    
    ParticleArray::iterator end()
    {
        return std::end(m_particles);
    }
    
//    ParticleArray::const_iterator end()const
//    {
//        return std::end(m_particles);
//    }

    std::unique_ptr<fj::ParticleManager::ConstIterator> iterator()const;
    
public:
    
    const ParticleArray& getFlowParticles()const
    {
        return m_flowParticles;
    }
    
    const ParticleArray& getBoundaryParticles()const
    {
        return m_boundaryParticles;
    }
    
    size_t getRegisteredParticleNum()const
    {
        return m_particles.size();
    }
    
    const fj::ParticleID getUnusedID()
    {
        return m_particleHashMap.getUnusedID();
    }
    
private:
    ParticleArray m_particles;
    ParticleArray m_flowParticles;
    ParticleArray m_boundaryParticles;
    fj::ParticleHashMap m_particleHashMap;
};


class fj::ParticleManager::ConstIterator
{
public:
    ConstIterator() = delete;
    ~ConstIterator() = default;
    
    ConstIterator(const fj::ParticleManager& particleManager)
    : m_particleManager(particleManager)
    , m_searchedIndex(0)
    {
        
    }
    
    bool hasNext()const;
    
    const fj::Particle& next();
    
private:
    const fj::ParticleManager& m_particleManager;
    
    size_t m_searchedIndex;
};

#endif /* particle_manager_hpp */

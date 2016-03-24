//
//  particle_hash_map.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_hash_map_hpp
#define particle_hash_map_hpp

#include <unordered_map>
#include <memory>

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class Particle;
    class ParticleHashMap;
}

class fj::ParticleHashMap
{
public:
    ParticleHashMap() = default;
    ~ParticleHashMap() = default;
    
    void registerParticle(std::shared_ptr<fj::Particle> particle);
    
    std::shared_ptr<fj::Particle>& get(const fj::ParticleID& ID)
    {
        return m_hashMap[ID];
    }
    
    /**
     * 未使用のIDを返す
     */
    const fj::ParticleID getUnusedID();
    
    size_t size()const
    {
        return m_hashMap.size();
    }
    
private:
    std::unordered_map<fj::ParticleID, std::shared_ptr<fj::Particle>> m_hashMap;
};

#endif /* particle_hash_map_hpp */

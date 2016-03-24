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
    
    std::shared_ptr<fj::Particle>& get(const int ID)
    {
        return m_hashMap[ID];
    }
    
    /**
     * 未使用のIDを返す
     */
    int getUnusedID();
    
    
private:
    std::unordered_map<unsigned int, std::shared_ptr<fj::Particle>> m_hashMap;
};

#endif /* particle_hash_map_hpp */

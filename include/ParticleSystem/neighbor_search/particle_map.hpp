//
//  particle_map.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/23.
//
//

#ifndef particle_map_hpp
#define particle_map_hpp

#include <memory>

namespace fj {
    class Particle;
    class ParticleMap;
}

class fj::ParticleMap
{
public:
    ParticleMap() = delete;
    virtual ~ParticleMap() = default;
    
    virtual void registerParticle(std::shared_ptr<fj::Particle> particle) = 0;
    
    virtual const fj::Particle& getParticleAt(const unsigned int id)const = 0;
};

#endif /* particle_map_hpp */

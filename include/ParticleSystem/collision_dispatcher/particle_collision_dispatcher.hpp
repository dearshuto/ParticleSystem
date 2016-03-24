//
//  particle_collision_dispatcher.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_collision_dispatcher_hpp
#define particle_collision_dispatcher_hpp

#include <memory>
#include <vector>

namespace fj {
    class Particle;
    class ParticleCollisionDispatcher;
}

class fj::ParticleCollisionDispatcher
{
    typedef unsigned int HashValue;
public:
    ParticleCollisionDispatcher() = delete;
    ~ParticleCollisionDispatcher() = default;
    
    ParticleCollisionDispatcher(const unsigned int width, const unsigned int height, const unsigned int depth)
    : m_width(width)
    , m_height(height)
    , m_depth(depth)
    {
        
    }
    
    std::vector<const std::shared_ptr<fj::Particle>> getNeighborParticlesAt(const fj::Particle& particle)const;
    
private:
    
    HashValue computeHash(const fj::Particle& particle)const;
    
private:
    const unsigned int getWidth()const
    {
        return m_width;
    }
    
    const unsigned int getHeight()const
    {
        return m_height;
    }
    
    const unsigned int getDepth()const
    {
        return m_depth;
    }
    
private:
    const unsigned int m_width;
    const unsigned int m_height;
    const unsigned int m_depth;
};

#endif /* particle_collision_dispatcher_hpp */

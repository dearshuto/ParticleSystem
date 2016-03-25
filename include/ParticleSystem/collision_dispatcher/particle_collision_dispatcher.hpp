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
    class ParticleManager;
    
    class ParticleCollisionDispatcher;
}

/**
 * 空間分割法を利用した衝突判定器
 */
class fj::ParticleCollisionDispatcher
{
    typedef unsigned int HashValue;
    typedef std::vector<std::shared_ptr<fj::Particle>> Particles;
public:
    ParticleCollisionDispatcher() = delete;
    ~ParticleCollisionDispatcher() = default;
    
    ParticleCollisionDispatcher(const unsigned int width, const unsigned int height, const unsigned int depth)
    : m_width(width)
    , m_height(height)
    , m_depth(depth)
    {
        m_cells.resize(width * height * depth);
    }
    
    void initialize(const fj::ParticleManager& particleManager);
    
    void updated();
    
    std::vector<const std::shared_ptr<fj::Particle>> getNeighborParticlesAt(const fj::Particle& particle)const;
    
private:
    
    void updatedAt(const HashValue& currentHash);
    
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

    std::vector<Particles> m_cells;
};

#endif /* particle_collision_dispatcher_hpp */

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

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle/particle.hpp>

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
    typedef unsigned int HashValue_t;
    typedef std::vector<std::shared_ptr<fj::Particle>> Particles;
public:
    ParticleCollisionDispatcher() = delete;
    ~ParticleCollisionDispatcher() = default;
    
    ParticleCollisionDispatcher(const unsigned int width, const unsigned int height, const unsigned int depth, const fj::Scalar& blockSize)
    : m_width(width)
    , m_height(height)
    , m_depth(depth)
    , m_blockSize(blockSize)
    {
        m_cells.resize(width * height * depth);
    }
        
    void registerParticle(const std::shared_ptr<fj::Particle>& particle);
    
    void updated();
    
    fj::Particle::NeighborParticles getNeighborParticlesAt(const fj::Particle& particle)const;
    
private:
    
    void setNeighbors(const fj::Particle& particle, const Particles& cell, fj::Particle::NeighborParticles* neighborParticles)const;
    
    /**
     * あるハッシュ値をもつセルからxyz方向に移動したセルを返す
     */
    const Particles*const getSideCell(const HashValue_t& hash, const int x, const int y, const int z)const;
    
    void updatedAt(const HashValue_t& currentHash);
    
    HashValue_t computeHash(const fj::Particle& particle)const;
    
    /**
     * スカラー値をハッシュ値計算に利用可能な範囲に丸める
     */
    unsigned int clamp(const fj::Scalar& num)const;
    
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

    const fj::Scalar& getBlockSize()const
    {
        return m_blockSize;
    }
    
private:
    const unsigned int m_width;
    const unsigned int m_height;
    const unsigned int m_depth;
    
    /**
     * 空間分割したときの分割ひとつぶん
     */
    const fj::Scalar m_blockSize;
    
    std::vector<Particles> m_cells;
};

#endif /* particle_collision_dispatcher_hpp */

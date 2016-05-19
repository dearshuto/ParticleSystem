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
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleManager;
    
    class ParticleCollisionDispatcher;
}

/**
 * 空間分割法を利用した衝突判定器
 */
class fj::ParticleCollisionDispatcher : public fj::Solver
{
    typedef unsigned int HashValue_t;
    typedef std::vector<fj::ParticleID> Particles;
public:
    ParticleCollisionDispatcher() = delete;
    ~ParticleCollisionDispatcher() = default;
    
    ParticleCollisionDispatcher(const unsigned int width, const unsigned int height, const unsigned int depth, const fj::Scalar& blockSize, const unsigned int priority = 3)
    : fj::Solver(priority)
    , m_width(width)
    , m_height(height)
    , m_depth(depth)
    , m_blockSize(blockSize)
    {
        m_cells.resize(width * height * depth);
    }
        
    void registerParticle(const fj::ParticleID& particle, const fj::ParticleManager& particleManager);
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
    fj::Particle::NeighborParticles getNeighborParticlesAt(const fj::Particle& particle, const fj::ParticleManager& particleManager)const;
    
private:
    
    void updated(const fj::ParticleManager& particleManager);
    
    void setNeighbors(const fj::Particle& particle, const Particles& cell, fj::Particle::NeighborParticles* neighborParticles, const fj::ParticleManager& particleManager)const;
    
    /**
     * あるハッシュ値をもつセルからxyz方向に移動したセルを返す
     */
    const Particles*const getSideCell(const HashValue_t& hash, const int x, const int y, const int z)const;
    
    void updatedAt(const HashValue_t& currentHash, const fj::ParticleManager& particleManager);
    
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

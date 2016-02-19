//
//  particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <vector>
#include <ParticleSystem/type/Vector.hpp>

namespace fj {
    class Particle;
}

class fj::Particle
{
    /**
     * 循環参照を起こさないように弱い参照で保持された近傍粒子
     */
    typedef std::vector<std::weak_ptr<fj::Particle>> NeighborParticles;
public:
    Particle()
    : Particle(fj::Vector(0, 0, 0))
    {
        
    }
    
    virtual~Particle() = default;
    
    
    Particle(const fj::Particle& other) = delete;
    Particle& operator=(const fj::Particle& other) = delete;
    
    
    Particle(const fj::Vector& position)
    : m_position(position)
    {
        
    }
    
    
    /**
     * 近傍粒子を追加する
     */
    void addNeighborParticle(std::shared_ptr<fj::Particle> neighborParticle)
    {
        // 引数はsharedポインタだが、保持はweakポインタで行うので循環参照は発生しない
        m_neighborParticles.push_back(neighborParticle);
    }
    
    /**
     * 保持していた近傍粒子を解放する
     */
    void clearNeighborParticles()
    {
        m_neighborParticles.clear();
    }
    
    /**
     * 近傍から受ける力を全て足し合す
     */
    void accumulateForce();
    
    void applyForce(const fj::Vector& force)
    {
        m_appliedForce += force;
    }
    
    fj::Vector popApliedForce()
    {
        const fj::Vector temp = getForce();
        m_appliedForce = fj::Vector(0, 0, 0);
        return temp;
    }
    
protected:
    void accumulateForceByNeighborParticles();
    virtual fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) = 0;
    
// getters
public:
    const fj::Vector& getPosition()const
    {
        return m_position;
    }
    
    const fj::Vector& getForce()const
    {
        return m_appliedForce;
    }
    
    const fj::Particle::NeighborParticles& getNeighborParticles()const
    {
        return m_neighborParticles;
    }
    
protected:
    fj::Particle::NeighborParticles* getNeighborParticlesPtr()
    {
        return &m_neighborParticles;
    }
    
private:
    /**
     * 地震の位置から一定の範囲内に存在するパーティクル
     */
    fj::Particle::NeighborParticles m_neighborParticles;
    
    fj::Vector m_position;
    fj::Vector m_appliedForce;
};

#endif /* particle_hpp */

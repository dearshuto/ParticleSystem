//
//  particle_system.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include <ParticleSystem/particle/FJparticle.h>
#include <ParticleSystem/type/FJtype.h>

namespace fj {
    class Particle;
    class ParticleSystem;
}

class fj::ParticleSystem
{
public:
    ParticleSystem()
    : m_gravity(0, 0, 0)
    , m_hasActivatedGravity(false)
    , m_threadNum(1)
    {

    }

    ~ParticleSystem() = default;

    void stepSimulation(const float timestep);

    
    void createFluidParticle(const fj::Vector& position);
  
    
    void createFineParticle(const fj::Vector& position, const float radius, const float mass);
    

    /**
     * @param index1 衝突を検知した粒子のID
     * @param index2 ID1と衝突した粒子のID
     */
    void makeCollision(const int index1, const int index2);


    /**
     * 剛体から受けた力を加える
     * @oaram 剛体の影響を受けた粒子のインデックス
     * @param 粒子が衝突した剛体上の点
     */
    void applyForceFromObject(const int index, const fj::Vector& collisionPoint);
    

	void applyForceFromObject(const int index, const fj::Scalar& distance, const fj::Vector& normalizedDirection);
    

    bool hasActivatedGravity()const
    {
        return m_hasActivatedGravity;
    }

    void enableGravity()
    {
        m_hasActivatedGravity = true;
    }

    void disableGravity()
    {
        m_hasActivatedGravity = false;
    }

private:
    void simulateParticleBehavior();
    void applyGravity();
    void clearParticleNeighbors();

//ge tters & setters
public:
    const std::vector<std::shared_ptr<fj::Particle>>& getParticles()const
    {
        return m_particles;
    }

    const fj::Vector& getGravity()const
    {
        return m_gravity;
    }

    void setGravity(const float x, const float y, const float z)
    {
        m_gravity = fj::Vector(x, y, z);
    }

	void setParticlePositionAt(const int index, const fj::Vector& position);

	void setParticleVelocityAt(const int index, const fj::Vector& velocity);

	fj::Vector popParticleForceAt(const int index);

    
    uint8_t getThreadNum()const
    {
        return m_threadNum;
    }
    
    void setThreadNum(const uint8_t threadNum)
    {
        m_threadNum = threadNum;
    }
    
protected:
    std::vector<std::shared_ptr<fj::Particle>>* getParticlesPtr()
    {
        return &m_particles;
    }

private:
    std::vector< std::shared_ptr<fj::Particle> > m_particles;
    fj::Vector m_gravity;
    bool m_hasActivatedGravity;
    
    /**
     * 粒子を更新する処理のスレッドの数. (ありえないけど)256スレッドまでサポートしておく.
     */
    uint8_t m_threadNum;
};

#endif /* particle_system_hpp */

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

#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

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

    ParticleSystem(std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher)
    : ParticleSystem()
    {
        m_collisionDispatcher =  std::move(collisionDispatcher);
    }
    
    void initSimulationStatus();
    
    void stepSimulation(const float timestep);

    
    void createFluidParticle(const fj::Vector3& position, const bool movable = true);
  
    
    void createFineParticle(const fj::Vector3& position, const float radius, const float mass);
    

    /**
     * @param index1 衝突を検知した粒子のID
     * @param index2 ID1と衝突した粒子のID
     */
    void makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2, const fj::Scalar& distance);


    /**
     * 剛体から受けた力を加える
     * @oaram 剛体の影響を受けた粒子のインデックス
     * @param 粒子が衝突した剛体上の点
     */
    void applyForceFromObject(const fj::ParticleID& ID, const fj::Vector3& collisionPoint);
    

    void applyForceFromObject(const fj::ParticleID& ID, const fj::Scalar& distance, const fj::Vector3& normalizedDirection);
    

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
    void updateParticleNeighbor();
    void simulateParticleBehavior();
    void updateParticleProperty();
    void updateParticlePropertyWithin_MT(const int begin, const int end);
    void accumulateParticleForce();
    void accumulateParticleForceWithin_MT(const int begin, const int end);
    
    void applyGravity();
    void clearParticleNeighbors();

//getters & setters
public:

    const fj::ParticleManager& getParticleManager()const
    {
        return m_particleManager;
    }
    
    const fj::ParticleCollisionDispatcher& getCollisionDispatcher()const
    {
        return *m_collisionDispatcher;
    }

    const fj::Vector3& getGravity()const
    {
        return m_gravity;
    }

    void setGravity(const float x, const float y, const float z)
    {
        m_gravity = fj::Vector3(x, y, z);
    }

    void setParticlePositionAt(const fj::ParticleID& ID, const fj::Vector3& position);

    void setParticleVelocityAt(const fj::ParticleID& ID, const fj::Vector3& velocity);

    fj::Vector3 popParticleForceAt(const fj::ParticleID& ID);

    
    uint8_t getThreadNum()const
    {
        return m_threadNum;
    }
    
    void setThreadNum(const uint8_t threadNum)
    {
        m_threadNum = threadNum;
    }
    
protected:
    
    std::unique_ptr<fj::ParticleCollisionDispatcher>& getCollisionDispatcherPtr()
    {
        return m_collisionDispatcher;
    }

    fj::ParticleManager* getParticleManagerPtr()
    {
        return &m_particleManager;
    }
    
    fj::NeighborMap*const getNeighborMap()
    {
        return &m_neighborMap;
    }
    
private:
    
    /**
     * 走査とID検索とを可能な状態で粒子を管理する
     */
    fj::ParticleManager m_particleManager;
    
    /**
     * 近傍情報の管理
     */
    fj::NeighborMap m_neighborMap;
    
    /**
     * 独自実装の近傍探索アルゴリズム
     * 近傍粒子探索を外部にいたくするときはnullのまま
     */
    std::unique_ptr<fj::ParticleCollisionDispatcher> m_collisionDispatcher;
    
    
    fj::Vector3 m_gravity;

    bool m_hasActivatedGravity;
    
    /**
     * 粒子を更新する処理のスレッドの数. (ありえないけど)256スレッドまでサポートしておく.
     */
    uint8_t m_threadNum;
};

#endif /* particle_system_hpp */

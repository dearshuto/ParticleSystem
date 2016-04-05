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

#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleSystem;
}

class fj::ParticleSystem
{
public:
    ParticleSystem() = default;
    ~ParticleSystem() = default;

    ParticleSystem(std::unique_ptr<fj::Solver> solver, std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher = nullptr)
    : m_threadNum(1)
    {
        m_solver = std::move(solver);
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
    
    
    const fj::Vector3 getAppliedAccel(const fj::ParticleID& ID)const
    {
        return m_solver->getAccellAt(ID);
    }
    
    void setParticlePositionAt(const fj::ParticleID& ID, const fj::Vector3& position);
    
    void setParticleVelocityAt(const fj::ParticleID& ID, const fj::Vector3& velocity);

    
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
    
    const fj::NeighborMap& getNeighborMap()const
    {
        return m_neighborMap;
    }
    
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
    
    fj::NeighborMap*const getNeighborMapPtr()
    {
        return &m_neighborMap;
    }
    
    std::unique_ptr<fj::Solver>& getSolverPtr()
    {
        return m_solver;
    }
    
private:
    
    /**
     * 走査とID検索とを可能な状態で粒子を管理する
     */
    fj::ParticleManager m_particleManager;

    /**
     * 粒子砲アルゴリズム
     */
    std::unique_ptr<fj::Solver> m_solver;
    
    /**
     * 近傍情報の管理
     */
    fj::NeighborMap m_neighborMap;
    
    /**
     * 独自実装の近傍探索アルゴリズム
     * 近傍粒子探索を外部にいたくするときはnullのまま
     */
    std::unique_ptr<fj::ParticleCollisionDispatcher> m_collisionDispatcher;
    
    
    /**
     * 粒子を更新する処理のスレッドの数. (ありえないけど)256スレッドまでサポートしておく.
     */
    uint8_t m_threadNum;
};

#endif /* particle_system_hpp */

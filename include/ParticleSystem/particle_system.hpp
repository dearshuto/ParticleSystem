//
//  particle_system.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include <string>
#include <vector>

#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/surface_construction/marching_cubes.hpp>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleSystem;
}

class fj::ParticleSystem
{
public:
    ParticleSystem() = default;
    virtual~ParticleSystem() = default;

    ParticleSystem(const fj::ParticleSystem& particleSystem) = delete;
    
    ParticleSystem(std::unique_ptr<fj::Solver> solver, std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher = nullptr, std::unique_ptr<fj::BoundingBox> bb = nullptr)
    {
        m_solver = std::move(solver);
        m_collisionDispatcher =  std::move(collisionDispatcher);
        m_bb = std::move(bb);
    }
    
    fj::ParticleSystem& operator=(const fj::ParticleSystem& other) = delete;
        
    /**
     * シミュレーションをタイムステップ分進める
     */
    void stepSimulation(const float timestep);

    /**
     * 
     */
    void stepParticlePosition(const float timestep);
    
    /**
     * 指定された位置に粒子を生成する
     * @param position 粒子の位置
     * @param movable 移動可能の判断
     */
    fj::ParticleID createParticle(const fj::Vector3& position, const bool movable = true);

    /**
     * 粒子間の衝突を作る
     * @param index1 衝突を検知した粒子のID
     * @param index2 ID1と衝突した粒子のID
     * @param distance 粒子間距離
     */
    void makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2, const fj::Scalar& distance);

    /**
     * 粒子間の衝突を作る. 内部で距離計算をするので, 距離を指定しない関数に比べると速度が劣る
     * @param index1 衝突を検知した粒子のID
     * @param index2 ID1と衝突した粒子のID
     */
    void makeCollision(const fj::ParticleID& ID1, const fj::ParticleID& ID2);
    
    /**
     * 剛体から受けた力を加える. 現在は未実装
     * @oaram 剛体の影響を受けた粒子のインデックス
     * @param 粒子が衝突した剛体上の点
     */
    void applyForceFromObject(const fj::ParticleID& ID, const fj::Vector3& collisionPoint);
    

    /**
     *現在は未実装
     */
    void applyForceFromObject(const fj::ParticleID& ID, const fj::Scalar& distance, const fj::Vector3& normalizedDirection);
    
    /**
     * 粒子の加速度を取得する
     */
    const fj::Vector3& getAppliedAccel(const fj::ParticleID& ID)const
    {
        return m_solver->getAccellAt(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel);
    
    void setParticlePositionAt(const fj::ParticleID& ID, const fj::Vector3& position);
    
    void setParticleVelocityAt(const fj::ParticleID& ID, const fj::Vector3& velocity);

protected:
    virtual void simulateParticleBehavior(const fj::Scalar& timestep);
    
private:
    void updateParticleNeighbor();
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
     * 粒子法アルゴリズム
     */
    std::unique_ptr<fj::Solver> m_solver;
    
    /**
     * 近傍情報の管理
     */
    fj::NeighborMap m_neighborMap;
    
    /**
     * 独自実装の近傍探索アルゴリズム
     * 近傍粒子探索を外部にいたくするときは必要ない
     */
    std::unique_ptr<fj::ParticleCollisionDispatcher> m_collisionDispatcher;
    
    std::unique_ptr<fj::BoundingBox> m_bb;
    
    fj::MarchingCubes m_marchingCubes;
};

#endif /* particle_system_hpp */

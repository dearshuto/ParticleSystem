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
#include <tuple>
#include <vector>

#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/surface_construction/marching_cubes.hpp>
#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/type/mesh.hpp>

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleSystem;
}

/**
 * 粒子の作成、シミュレーション、管理などなど.
 */
class fj::ParticleSystem
{
public:
    ParticleSystem() = delete;
    virtual~ParticleSystem() = default;

    ParticleSystem(const fj::ParticleSystem& particleSystem) = delete;
    
    ParticleSystem(std::unique_ptr<fj::Solver> solver, std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher = nullptr, std::unique_ptr<fj::BBAlgorithm> bb = nullptr)
    : m_enableGravity(false)
    , m_gravity( fj::Vector3(0, -9.8, 0) )
    {
        m_solver = std::move(solver);
        m_collisionDispatcher =  std::move(collisionDispatcher);
        m_bbAlgorithm = std::move(bb);
    }
    
    
    ParticleSystem(std::unique_ptr<fj::Solver> solver, std::unique_ptr<fj::BBAlgorithm> bb = nullptr)
    : ParticleSystem(std::move(solver), nullptr, std::move(bb))
    {
    }

    
    fj::ParticleSystem& operator=(const fj::ParticleSystem& other) = delete;
    
    void enableGravity()
    {
        m_enableGravity = true;
    }
    
    void disableGravity()
    {
        m_enableGravity = false;
    }
    
    /**
     * シミュレーションをタイムステップ分進める
     */
    void stepSimulation(const float timestep);

    /**
     * Solverが計算した加速度をもとに全粒子の位置を更新する
     */
    void stepParticlePosition(const float timestep);
    
    /**
     * 表面抽出されたメッシュを初期化する
     */
    void clearMesh()
    {
        for (auto& mesh : *getMeshesPtr())
        {
            mesh.clear();
        }
    }
    
    /**
     * 指定された位置に粒子を生成する
     * @param position 粒子の位置
     * @param movable 移動可能の判断
     */
    fj::ParticleID createParticle(const fj::Vector3& position, const bool movable = true);

    /**
     * 等置面を定義する.
     */
    void createIsosurface(const fj::Scalar& level)
    {
        m_meshes.emplace_back(level);
    }
    
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
    
    /**
     * 粒子に加速度を追加する
     * @params ID 粒子の識別子
     */
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel);

    /**
     * 強制的に粒子の位置を変更する
     */
    void setParticlePositionAt(const fj::ParticleID& ID, const fj::Vector3& position);
    
    /**
     * 強制的に粒子の速度を変更する
     */
    void setParticleVelocityAt(const fj::ParticleID& ID, const fj::Vector3& velocity);

protected:
    virtual void simulateParticleBehavior(const fj::Scalar& timestep);
    
    void applyGravity();
    
private:
    /**
     * ParticleCollisionDispatcherを利用して近傍粒子探索を行う. ParticleCollisionDispatcherがnullptrのときは何も起きない.
     */
    void updateParticleNeighbor();

    /**
     * NeighborMapに登録されている近傍情報をすべて消去する
     */
    void clearParticleNeighbors();

//getters & setters
public:

    const fj::Vector3& getGravity()const
    {
        return m_gravity;
    }
    
    void setGravity(const fj::Vector3& gravity)
    {
        m_gravity = gravity;
    }
    
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
    
    const fj::Solver& getSolver()const
    {
        return std::cref(*m_solver);
    }
 
    const std::vector<fj::Mesh>& getMeshes()const
    {
        return std::cref(m_meshes);
    }
    
    std::vector<fj::Mesh>* getMeshesPtr()
    {
        return &m_meshes;
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
    bool m_enableGravity;
    
    fj::Vector3 m_gravity;
    
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
    
    std::unique_ptr<fj::BBAlgorithm> m_bbAlgorithm;

    std::vector<fj::Mesh> m_meshes;
};

#endif /* particle_system_hpp */

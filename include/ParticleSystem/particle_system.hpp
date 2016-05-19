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

#include "particle_manager/particle_manager.hpp"
#include "particle_manager/neighbor_map.hpp"
#include "solver/bb_algorithm/bounding_box.hpp"
#include "solver/collision_dispatcher/particle_collision_dispatcher.hpp"
#include "solver/surface_construction/marching_cubes.hpp"
#include "solver/solver.hpp"
#include "solver/dynamics.hpp"
#include "type/mesh.hpp"

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
    
    ParticleSystem(std::unique_ptr<fj::Dynamics> solver)
    {
        m_dynamics = std::move(solver);
        m_solvers.push_back(m_dynamics);
    }

    
    fj::ParticleSystem& operator=(const fj::ParticleSystem& other) = delete;
    
    /**
     * 毎フレーム更新する処理を登録する
     */
    void addSolver(std::unique_ptr<fj::Solver> solver);
    
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
    const fj::ParticleID& createParticle(const fj::Vector3& position, const bool movable = true);

    /**
     * 等置面を定義する.
     */
    void createIsosurface(const fj::Scalar& level)
    {
        m_meshes.emplace_back(level);
    }
    
    bool hasNextSurfaceTriangle()const;
    
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
        return getSolver().getAccellAt(ID);
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
    
//getters & setters
public:
    
    const fj::ParticleManager& getParticleManager()const
    {
        return m_particleManager;
    }
    
    const fj::NeighborMap& getNeighborMap()const
    {
        return std::cref(m_neighborMap);
    }
    
    const fj::Dynamics& getSolver()const
    {
        return std::cref(*m_dynamics);
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
    
    fj::ParticleManager* getParticleManagerPtr()
    {
        return &m_particleManager;
    }
    
    fj::NeighborMap*const getNeighborMapPtr()
    {
        return &m_neighborMap;
    }
    
    std::shared_ptr<fj::Dynamics>& getSolverPtr()
    {
        return m_dynamics;
    }
        
private:
    
    /**
     * 走査とID検索とを可能な状態で粒子を管理する
     */
    fj::ParticleManager m_particleManager;
    
    /**
     * 粒子法アルゴリズム
     */
    std::shared_ptr<fj::Dynamics> m_dynamics;

    std::vector<fj::Mesh> m_meshes;
    
    std::vector<std::shared_ptr<fj::Solver>> m_solvers;
    
    /**
     * 近傍情報の管理
     */
    fj::NeighborMap m_neighborMap;
    
};

#endif /* particle_system_hpp */

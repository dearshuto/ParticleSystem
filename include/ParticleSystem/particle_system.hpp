//
//  particle_system.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

/*! \mainpage Particle-Based Simulation
 *
 * \section intro_sec Introduction
 *
 * 粒子法を実装した最強プログラム. ParticleSystemクラスがすべてを統括するクラスなので、まずは彼を見てください.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: buildフォルダを作成する
 *
 */

#ifndef particle_system_hpp
#define particle_system_hpp

#include <string>
#include <tuple>
#include <vector>

#include "particle_manager/particle_manager.hpp"
#include "particle_manager/neighbor_map.hpp"
#include "solver/solver_manager.hpp"
#include "solver/dynamics/dynamics.hpp"
#include "type/mesh.hpp"

namespace fj {
    class AdditionalSimulation;
    class BBAlgorithm;
    class Particle;
    class ParticleCollisionDispatcher;
    class ParticleID;
    class Solver;
    class ParticleSystem;
}

/**
 * 粒子の作成やシミュレーションなど、外部とのインタラクションを担う.
 */
class fj::ParticleSystem
{
public:
    ParticleSystem() = delete;
    virtual~ParticleSystem() = default;

    ParticleSystem(const fj::ParticleSystem& particleSystem) = delete;
    
    /**
     * @params dynamics 粒子法の解法
     */
    ParticleSystem(std::unique_ptr<fj::Dynamics> dynamics)
    {
        m_solverManager.addSolver( std::move(dynamics) );
    }

    
    fj::ParticleSystem& operator=(const fj::ParticleSystem& other) = delete;
    
    /**
     * 毎フレーム更新する処理を登録する
     */
    void addSolver(std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher);
    void addSolver(std::unique_ptr<fj::BBAlgorithm> bbAlgorithm);
    void addSolver(std::unique_ptr<fj::SurfaceConstruction> surfaceConstruction);
    void addSolver(std::unique_ptr<fj::AdditionalSimulation> additionalSolver);
    
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
    
    const fj::Mesh& getMesh(const unsigned int index)
    {
        return m_solverManager.getMesh(index);
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
    const fj::Vector3& getAppliedAccel(const fj::ParticleID& ID)const;
    
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
    
    const std::vector<fj::Mesh>& getMeshes()const
    {
        return std::cref(m_meshes);
    }
    
    std::vector<fj::Mesh>* getMeshesPtr()
    {
        return &m_meshes;
    }
    
    const fj::Dynamics& getDynamics()const
    {
        return m_solverManager.getDynamics();
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
    
    std::shared_ptr<fj::Dynamics>& getDynamicsPtr()
    {
        return m_solverManager.getDynamicsPtr();
    }
    
private:
    
    /**
     * 走査とID検索とを可能な状態で粒子を管理する
     */
    fj::ParticleManager m_particleManager;
    
    /**
     * 毎フレーム更新する処理の管理
     */
    fj::SolverManager m_solverManager;
    
    /**
     * 近傍情報の管理
     */
    fj::NeighborMap m_neighborMap;
    
public:
    
    /**
     * 等値面. TODO: クラス化して管理しやすくする.
     */
    std::vector<fj::Mesh> m_meshes;
};

#endif /* particle_system_hpp */

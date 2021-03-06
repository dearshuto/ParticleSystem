//
//  solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef solver_hpp
#define solver_hpp

#include <cassert>
#include <unordered_map>

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class ParticleSystem;
    class ParticleManager;
    class NeighborMap;
    class Solver;
}

/**
 * 毎フレーム更新する優先順序付きの処理。
 */
class fj::Solver
{
public:
    enum class Priority : unsigned int
    {
        kSurfaceCunstruction,
        kAdditionalSimulation,
        kSimulation,
        kNeighborMap,
        kCollisionDispatch,
    };
public:
    Solver() = delete;
    virtual~Solver() = default;

    Solver(const Priority priority = Priority::kSimulation)
    : m_priority(priority)
    {
        
    }
    
    /**
     * 毎フレーム呼び出される処理. SolverはParticleSystemの中で優先順序付きで登録されており、その順序に従って各Solverのexecute関数が呼ばれる.
     */
    virtual void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) = 0;
    
    /**
     * ParticleSystemに登録されている全てのSolverのexecuteを呼び出したあとに呼ばれる関数. この関数も優先度に従って呼ばれる.
     */
    virtual void postexecute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)
    {
        // デフォルトは空
    }

    /**
     * この関数が呼ばれた時点で作成済みのすべての粒子をシミュレーションするに必要なメモリを割当てて、そのメモリを初期化する.
     */
    void allocateMemory(const fj::ParticleManager& particleManager);
    
    /**
     * パーティクル単位でシミュレーションに必要なメモリ割当てをして、そのメモリを初期化する
     */
    virtual void allocateMemoryAt(const fj::ParticleID& ID) = 0;
    
    
    /**
     * IDで指定された粒子が削除だれたときによばれる関数。
     * 削除された粒子分のメモリを解放する。
     * @param ID 削除された粒子
     */
    virtual void freeSimulationMemoryAt(const fj::ParticleID& ID) = 0;
    
public:
    fj::Solver::Priority getPriority()const
    {
        return m_priority;
    }
    
private:
    
    /**
     * 処理の優先度。
     */
    const fj::Solver::Priority m_priority;
};

#endif /* solver_hpp */

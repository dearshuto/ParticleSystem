//
//  solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef solver_hpp
#define solver_hpp

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
 * 各粒子の加速度を求める. 
 */
class fj::Solver
{
public:
    enum class Priority : unsigned int
    {
        kSurfaceTracking,
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
     
    void clearAccel();
    
    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const
    {
        return m_accelMap.at(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        m_accelMap[ID] += accel;
    }
    
    /**
     * 粒子の物理量を返す. マーチングキューブ法などのスカラ値を必要とする処理で利用する. ソルバに起因するスカラならなんでもいい.
     */
    virtual const fj::Scalar calculateScalar(const fj::ParticleID& ID)const
    {
        
    }
    
protected:
    void setAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        m_accelMap[ID] = accel;
    }
    
public:
    fj::Solver::Priority getPriority()const
    {
        return m_priority;
    }
    
private:
    std::unordered_map<fj::ParticleID, fj::Vector3> m_accelMap;
    
    const fj::Solver::Priority m_priority;
};

#endif /* solver_hpp */

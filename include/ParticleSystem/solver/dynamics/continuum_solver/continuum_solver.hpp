//
//  continuum_solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/18.
//
//

#ifndef continuum_solver_hpp
#define continuum_solver_hpp

#include <ParticleSystem/solver/dynamics/dynamics.hpp>

namespace fj {
    class ContinuumSolver;
}

/**
 * 連続体としての解法. 粒子の加速度を更新していき、ParticleIDをキーとしたハッシュマップで保管する.
 */
class fj::ContinuumSolver : public fj::Dynamics
{
public:
    ContinuumSolver() = default;
    virtual~ContinuumSolver() = default;
    
    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const override
    {
        assert(m_accelMap.find(ID) != std::end(m_accelMap));
        return m_accelMap.at(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)override
    {
        
        m_accelMap[ID] += accel;
    }
    
    void clearAccel()override
    {
        for (auto& accel: m_accelMap)
        {
            accel.second = fj::Vector3(0, 0, 0);
        }
    }
    
    /**
     * 算出した粒子の加速度を確保しておくマップ領域を割り当てる
     */
    virtual void allocateMemory(const fj::ParticleManager& particleManager)override;
    
private:
    void freeDynamicsMemoryAt(const fj::ParticleID& ID)override;
    
    virtual void freeContinuumMemoryAt(const fj::ParticleID& ID) = 0;
    
protected:
    void setAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        m_accelMap[ID] = accel;
    }
private:
    std::unordered_map<fj::ParticleID, fj::Vector3> m_accelMap;
};

#endif /* continuum_solver_hpp */

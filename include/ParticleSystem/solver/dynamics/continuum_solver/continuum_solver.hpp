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

class fj::ContinuumSolver : public fj::Dynamics
{
public:
    ContinuumSolver() = delete;
    virtual~ContinuumSolver() = default;
    
    ContinuumSolver(const fj::Solver::Priority priority = fj::Solver::Priority::kSimulation)
    : fj::Dynamics(priority)
    {
        
    }

    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const
    {
        assert(m_accelMap.find(ID) != std::end(m_accelMap));
        return m_accelMap.at(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        
        m_accelMap[ID] += accel;
    }
    
    void clearAccel()
    {
        for (auto& accel: m_accelMap)
        {
            accel.second = fj::Vector3(0, 0, 0);
        }
    }
    
protected:
    void setAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        m_accelMap[ID] = accel;
    }
private:
    std::unordered_map<fj::ParticleID, fj::Vector3> m_accelMap;
};

#endif /* continuum_solver_hpp */

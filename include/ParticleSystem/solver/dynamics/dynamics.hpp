//
//  dynamics.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/19.
//
//

#ifndef dynamics_hpp
#define dynamics_hpp

#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Dynamics;
}

/**
 * 力学の処理
 */
class fj::Dynamics : public fj::Solver
{
public:
    Dynamics() = delete;
    virtual~Dynamics() = default;

    Dynamics(const fj::Solver::Priority priority)
    : fj::Solver(priority)
    {
        
    }
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override
    {
        // Solverとして呼ばれる処理をDynamicsに変換する。継承が深くなるとわかりにくくなるので。
        executeDynamics(timestep, particleSystem);
    }
    
    virtual void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) = 0;
    
    virtual const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const = 0;
    
    virtual void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel) = 0;
    
    virtual void clearAccel() = 0;
};

#endif /* dynamics_hpp */

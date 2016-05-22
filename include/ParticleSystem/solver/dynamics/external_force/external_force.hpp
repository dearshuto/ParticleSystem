//
//  external_force.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/22.
//
//

#ifndef external_force_hpp
#define external_force_hpp

#include <functional>
#include <ParticleSystem/solver/dynamics/dynamics.hpp>

namespace fj {
    class ExternalForce;
}

/**
 * 全ての粒子に一様にかかる外力
 */
class fj::ExternalForce : public fj::Dynamics
{
public:
    ExternalForce() = delete;
    virtual~ExternalForce() = default;
    
    ExternalForce(std::unique_ptr<fj::Dynamics> dynamics)
    : fj::Dynamics(fj::Solver::Priority::kSimulation)
    , m_dynamics( std::move(dynamics) )
    {
        
    }

    void clearAccel() override
    {
        getDynamicsPtr()->clearAccel();
    }
    
    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const override
    {
        return getDynamics().getAccellAt(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)override
    {
        getDynamicsPtr()->addAccelAt(ID, accel);
    }
    
    fj::Scalar calculateScalar(const fj::ParticleID& ID)const override
    {
        return getDynamics().calculateScalar(ID);
    }
    
public:
    const fj::Dynamics& getDynamics()const
    {
        return std::cref(*m_dynamics);
    }
    
    std::unique_ptr<fj::Dynamics>& getDynamicsPtr()
    {
        return std::ref(m_dynamics);
    }
    
private:
    std::unique_ptr<fj::Dynamics> m_dynamics;
};

#endif /* external_force_hpp */

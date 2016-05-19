//
//  gravity_force.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/19.
//
//

#ifndef gravity_force_hpp
#define gravity_force_hpp

#include <functional>
#include <memory>

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/solver/dynamics/dynamics.hpp>

namespace fj {
    class GravityForce;
}

/**
 * 一定の方向に力を与える場
 */
class fj::GravityForce : public fj::Dynamics
{
public:
    GravityForce() = delete;
    ~GravityForce() = default;
    
    GravityForce(std::unique_ptr<fj::Dynamics> dynamics, const fj::Vector3& vector)
    : fj::Dynamics( fj::Solver::Priority::kSimulation )
    , m_gravity(vector)
    , m_dynamics( std::move(dynamics) )
    {
        
    }
    
    void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override;
    
    void clearAccel() override
    {
        m_dynamics->clearAccel();
    }
    
    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const override
    {
        return m_dynamics->getAccellAt(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)override
    {
        m_dynamics->addAccelAt(ID, accel);
    }
    
public:
    
    const fj::Vector3& getGravity()const
    {
        return std::cref(m_gravity);
    }
    
private:
    fj::Vector3 m_gravity;
    
    std::unique_ptr<fj::Dynamics> m_dynamics;
};

#endif /* gravity_force_hpp */

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

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class GravityForce;
}

class fj::GravityForce : public fj::Solver
{
public:
    GravityForce() = delete;
    ~GravityForce() = default;
    
    GravityForce(const fj::Vector3& vector)
    : fj::Solver( fj::Solver::Priority::kAdditionalSimulation )
    , m_gravity(vector)
    {
        
    }
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override;
    
public:
    
    const fj::Vector3& getGravity()const
    {
        return std::cref(m_gravity);
    }
    
private:
    fj::Vector3 m_gravity;
};

#endif /* gravity_force_hpp */

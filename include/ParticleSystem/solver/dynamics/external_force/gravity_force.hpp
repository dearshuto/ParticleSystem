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
#include "external_force.hpp"

namespace fj {
    class GravityForce;
}

/**
 * 全ての粒子に一様に影響する重力
 */
class fj::GravityForce : public fj::ExternalForce
{
public:
    GravityForce() = delete;
    ~GravityForce() = default;
    
    GravityForce(std::unique_ptr<fj::Dynamics> dynamics, const fj::Vector3& vector)
    : fj::ExternalForce( std::move(dynamics) )
    , m_gravity(vector)
    {
        
    }
    
    void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override;
    
public:
    
    const fj::Vector3& getGravity()const
    {
        return std::cref(m_gravity);
    }
    
private:
    fj::Vector3 m_gravity;
};

#endif /* gravity_force_hpp */

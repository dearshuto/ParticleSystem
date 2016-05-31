//
//  penalty_force.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef penalty_force_hpp
#define penalty_force_hpp

#include <memory>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/solver/additional_simulation/additional_simulation.hpp>

namespace fj {
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::AdditionalSimulation
{   
public:
    PenaltyForce() = delete;
    ~PenaltyForce() = default;
    
    PenaltyForce(std::unique_ptr<fj::BoundingBox> bb, const fj::Scalar& K, const Priority& priority = Priority::kAdditionalSimulation)
    : fj::AdditionalSimulation(priority)
    , m_bb( std::move(bb) )
    , m_K(K)
    {
        
    }
    
    const fj::Scalar& getK()const
    {
        return m_K;
    }
    
private:
    void executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
public:
    const fj::BoundingBox& getBB()const
    {
        return std::cref(*m_bb);
    }
    
private:
    
    std::unique_ptr<fj::BoundingBox> m_bb;
    
    fj::Scalar m_K;
};

#endif /* penalty_force_hpp */

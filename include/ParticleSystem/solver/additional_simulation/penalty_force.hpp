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
    class IPenaltyForceRange;
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::AdditionalSimulation
{   
public:
    PenaltyForce() = delete;
    ~PenaltyForce() = default;
    
    PenaltyForce(std::unique_ptr<fj::IPenaltyForceRange> pfRange, const fj::Scalar& K, const Priority& priority = Priority::kAdditionalSimulation)
    : fj::AdditionalSimulation(priority)
    , m_pfRange( std::move(pfRange) )
    , m_K(K)
    {
        
    }
    
    const fj::Scalar& getK()const
    {
        return m_K;
    }
    
    void allocateMemoryAt(const fj::ParticleID& ID)override
    {
        // とくになし
    }
    
private:
    void executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;

    void freeAdditionalMemoryAt(const fj::ParticleID& ID)override
    {
        // とくにやることなし
    }
public:
    const fj::IPenaltyForceRange& getPFRrange()const
    {
        return std::cref(*m_pfRange);
    }
    
private:
    
    std::unique_ptr<fj::IPenaltyForceRange> m_pfRange;
    
    fj::Scalar m_K;
};

#endif /* penalty_force_hpp */

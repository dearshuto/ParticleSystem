//
//  penalty_force.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef penalty_force_hpp
#define penalty_force_hpp

#include <functional>
#include <memory>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/solver/additional_simulation/additional_simulation.hpp>

namespace fj {
    class IPenaltyForceRange;
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::AdditionalSimulation
{
    typedef std::vector<std::unique_ptr<fj::IPenaltyForceRange>> PenaltyRangePtrContainer;
public:
    PenaltyForce()
    : fj::AdditionalSimulation(Priority::kAdditionalSimulation)
    {
        
    }
    
    ~PenaltyForce() = default;
    
    PenaltyForce(const Priority& priority)
    : fj::AdditionalSimulation(priority)
    {
        
    }
    
    void allocateMemoryAt(const fj::ParticleID& ID)override
    {
        // とくになし
    }
    
    void addPenaltyForceRange(std::unique_ptr<fj::IPenaltyForceRange> pfRange);
    
private:
    void executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;

    void freeAdditionalMemoryAt(const fj::ParticleID& ID)override
    {
        // とくにやることなし
    }
public:
    const PenaltyRangePtrContainer& getPenaltyRanges()const
    {
        return std::cref(m_penaltyRanges);
    }
    
private:
    
    PenaltyRangePtrContainer m_penaltyRanges;
};

#endif /* penalty_force_hpp */

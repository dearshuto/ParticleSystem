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
#include <ParticleSystem/solver/solver.hpp>
#include "bounding_box.hpp"

namespace fj {
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::Solver
{   
public:
    PenaltyForce() = delete;
    ~PenaltyForce() = default;
    
    PenaltyForce(std::unique_ptr<fj::BoundingBox> bb, const fj::Scalar& K, const Priority& priority = Priority::kAdditionalSimulation)
    : fj::Solver(priority)
    , m_bb( std::move(bb) )
    , m_K(K)
    {
        
    }

    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem);
    
    const fj::Scalar& getK()const
    {
        return m_K;
    }
    
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

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
#include <ParticleSystem/bb_algorithm/bb_algorithm.h>

namespace fj {
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::BBAlgorithm
{
public:
    PenaltyForce() = delete;
    ~PenaltyForce() = default;
    
    PenaltyForce(std::unique_ptr<fj::BBAlgorithm> bb, const fj::Scalar& K)
    : m_bb(std::move(bb))
    , m_K(K)
    {
        
   }
    
    void execute(fj::ParticleManager* particleManager)override;
    
    const fj::BoundingBox& getBoundingBox()const override
    {
        return m_bb->getBoundingBox();
    }
    
private:
    std::unique_ptr<fj::BBAlgorithm> m_bb;
    fj::Scalar m_K;
};

#endif /* penalty_force_hpp */

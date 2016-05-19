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
#include "bb_algorithm_decorator.hpp"

namespace fj {
    class PenaltyForce;
}

class fj::PenaltyForce : public fj::BBAlgorithmDecorator
{   
public:
    PenaltyForce() = delete;
    ~PenaltyForce() = default;
    
    PenaltyForce(std::unique_ptr<fj::BBAlgorithm> bb, const fj::Scalar& K, const fj::Scalar offset)
    : BBAlgorithmDecorator( std::move(bb) )
    , m_K(K)
    , m_offset(offset)
    {
        
    }
    
    void executeBBAlgorithm(fj::ParticleSystem* particleSystem)override;
    
    const fj::Scalar& getK()const
    {
        return m_K;
    }
    
private:
    fj::Scalar m_K;
    
    fj::Scalar m_offset;
};

#endif /* penalty_force_hpp */

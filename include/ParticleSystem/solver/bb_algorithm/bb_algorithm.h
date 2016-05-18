//
//  bb_algorithm.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef bb_algorithm_h
#define bb_algorithm_h

#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class BoundingBox;
    class ParticleSystem;
    class BBAlgorithm;
}

/**
 * デコレータパターンで設計されたバウンディングボックスアルゴリズムのインタフェース.
 */
class fj::BBAlgorithm : public fj::Solver
{
public:
    BBAlgorithm() = delete;
    virtual ~BBAlgorithm() = default;
    
    BBAlgorithm(const unsigned int priority)
    : fj::Solver(priority)
    {
        
    }
    
    const fj::Scalar calculateScalar(const fj::ParticleID& ID)const override
    {
        
    }
    
    virtual const fj::BoundingBox& getBoundingBox()const = 0;
};

#endif /* bb_algorithm_h */

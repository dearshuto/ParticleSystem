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
 * 未検証!!デコレータパターンで設計されたバウンディングボックスアルゴリズムのインタフェース.
 */
class fj::BBAlgorithm : public fj::Solver
{
public:
    BBAlgorithm() = delete;
    virtual ~BBAlgorithm() = default;
    
    BBAlgorithm(const fj::Solver::Priority priority = fj::Solver::Priority::kAdditionalSimulation)
    : fj::Solver(priority)
    {
        
    }
        
    virtual const fj::BoundingBox& getBoundingBox()const = 0;
};

#endif /* bb_algorithm_h */

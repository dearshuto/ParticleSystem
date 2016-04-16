//
//  bb_algorithm.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef bb_algorithm_h
#define bb_algorithm_h

namespace fj {
    class BoundingBox;
    class NeighborMap;
    class ParticleManager;
    class Solver;
    class BBAlgorithm;
}

class fj::BBAlgorithm
{
public:
    virtual ~BBAlgorithm() = default;
    
    virtual void execute(fj::ParticleManager* particleManager, const fj::NeighborMap& neighborMap, const fj::Solver& solver) = 0;
    
    virtual const fj::BoundingBox& getBoundingBox()const = 0;
};

#endif /* bb_algorithm_h */

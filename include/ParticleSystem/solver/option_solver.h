//
//  option_solver.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef option_solver_h
#define option_solver_h

namespace fj {
    class ParticleManager;
    clas NeighborMap;
    class OptionSolver;
}

class fj::OptionSolver
{
public:
    virtual ~OptionSolver();
    
    virtual execute(fj::ParticleManager* particleManager, fj::NeighborMap* neighborMap) = 0;
};

#endif /* option_solver_h */

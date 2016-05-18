//
//  continuum_solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/18.
//
//

#ifndef continuum_solver_hpp
#define continuum_solver_hpp

#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class ContinuumSolver;
}

class fj::ContinuumSolver : public fj::Solver
{
public:
    ContinuumSolver() = delete;
    virtual~ContinuumSolver() = default;
    
    ContinuumSolver(const unsigned int priority = 0)
    : fj::Solver(priority)
    {
        
    }
};

#endif /* continuum_solver_hpp */

//
//  additional_simulation.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/31.
//
//

#ifndef additional_simulation_hpp
#define additional_simulation_hpp

#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class AdditionalSimulation;
}

class fj::AdditionalSimulation : public fj::Solver
{
public:
    AdditionalSimulation()
    : AdditionalSimulation(Priority::kAdditionalSimulation)
    {
        
    }
    ~AdditionalSimulation() = default;
    
    AdditionalSimulation(const Priority& priority = Priority::kAdditionalSimulation)
    : fj::Solver(priority)
    {
        
    }
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override
    {
        executeAdditionalSimulation(timestep, particleSystem);
    }
    
protected:
    
    virtual void executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) = 0;
};

#endif /* additional_simulation_hpp */

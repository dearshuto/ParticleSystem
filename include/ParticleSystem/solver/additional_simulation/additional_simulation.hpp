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
    
private:
    
    void freeSimulationMemoryAt(const fj::ParticleID& ID)override
    {
        //このクラスで解放すべきメモリは存在しない。
        // 継承先から呼ばれる関数を呼ぶだけでOK
        freeAdditionalMemoryAt(ID);
    }
    
    virtual void freeAdditionalMemoryAt(const fj::ParticleID& ID) = 0;
protected:
    
    virtual void executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) = 0;
};

#endif /* additional_simulation_hpp */

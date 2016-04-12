//
//  solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef solver_hpp
#define solver_hpp

#include <unordered_map>

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class ParticleManager;
    class NeighborMap;
    class Solver;
}

/**
 * 各粒子の加速度を求める. 
 */
class fj::Solver
{
public:
    Solver() = default;
    virtual~Solver() = default;
    
    virtual void compute(const fj::Scalar& timestep, const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap) = 0;
        
    const fj::Vector3& getAccellAt(const fj::ParticleID& ID)const
    {
        return m_accelMap.at(ID);
    }
    
    void addAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel);
    
protected:
    void setAccelAt(const fj::ParticleID& ID, const fj::Vector3& accel)
    {
        m_accelMap[ID] = accel;
    }
    
private:
    std::unordered_map<fj::ParticleID, fj::Vector3> m_accelMap;
};

#endif /* solver_hpp */

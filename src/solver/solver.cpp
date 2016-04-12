//
//  solver.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <ParticleSystem/solver/solver.hpp>

void fj::Solver::addAccelAt(const fj::ParticleID &ID, const fj::Vector3 &accel)
{
    const fj::Vector3& kVector = getAccellAt(ID);
    
    setAccelAt(ID, kVector + accel);
}
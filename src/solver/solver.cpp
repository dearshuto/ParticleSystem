//
//  solver.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <ParticleSystem/solver/solver.hpp>

void fj::Solver::clearAccel()
{
    for (auto& accel: m_accelMap)
    {
        accel.second = fj::Vector3(0, 0, 0);
    }
}
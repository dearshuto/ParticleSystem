//
//  cube_penalty_range.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#include <algorithm>
#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/solver/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/solver/additional_simulation/cube_penalty_range.hpp>

fj::Vector3 fj::CubePenaltyRange::computeDirection(const fj::Vector3 &position)const
{
    fj::Vector3 returnDirection(0, 0, 0);
    const fj::BoundingBox& kBB = getBB();
    
    for (int i = 0; i < 3; i++)
    {
        const fj::Scalar kMin = std::max(fj::Scalar(0), kBB.getRange(i).getMin() - position[i]);
        const fj::Scalar kMax = std::min(fj::Scalar(0), kBB.getRange(i).getMax() - position[i]);
        
        returnDirection[i] = kMin + kMax;
    }
    
    return returnDirection;
}
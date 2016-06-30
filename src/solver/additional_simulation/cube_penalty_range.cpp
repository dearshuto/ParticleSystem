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

fj::Vector3 fj::CubePenaltyRange::direction(const fj::Vector3 &position)const
{
    const fj::BoundingBox& kBB = getBB();
    
    const fj::Scalar kMinX = std::min(fj::Scalar(0), kBB.getRangeX().getMin() - position.x());
    
    
    return fj::Vector3(0, 0, 0);
}
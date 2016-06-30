//
//  cylinder_penalty_range.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/solver/additional_simulation/cylinder_penalty_range.hpp>

fj::Vector3 fj::CylinderPenaltyRange::computeDirection(const fj::Vector3 &position)const
{
    fj::Vector3 kDirectionToCenter = position - getCenter();
    
    // yアップかzアップか選択する
    m_transpose ? (kDirectionToCenter.y() = 0) : (kDirectionToCenter.z() = 0);
    
    const fj::Scalar kDistance = kDirectionToCenter.squaredNorm();
    
    if (kDistance < getRadius())
    {
        return fj::Vector3(0, 0, 0);
    }
    
    return -kDirectionToCenter;
}
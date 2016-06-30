//
//  cylinder_penalty_range.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#ifndef cylinder_penalty_range_hpp
#define cylinder_penalty_range_hpp

#include <functional>
#include "i_penalty_force_range.h"

namespace fj {
    class CylinderPenaltyRange;
}


/**
 *
 */
class fj::CylinderPenaltyRange : public fj::IPenaltyForceRange
{
public:
    CylinderPenaltyRange() = delete;
    ~CylinderPenaltyRange() = default;
    
    CylinderPenaltyRange(const fj::Scalar& radius, const fj::Vector3& center, const bool enableTranspose = false)
    : m_radius(radius)
    , m_center(center)
    , m_transpose(enableTranspose)
    {
        
    }
    
    fj::Vector3 direction(const fj::Vector3& position)const override;
    
private:
    const fj::Scalar& getRadius()const
    {
        return std::cref(m_radius);
    }
    
    const fj::Vector3& getCenter()const
    {
        return std::cref(m_center);
    }
    
private:
    fj::Scalar m_radius;
    
    fj::Vector3 m_center;
    
    bool m_transpose;
};

#endif /* cylinder_penalty_range_hpp */

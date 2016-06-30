//
//  cube_penalty_range.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#ifndef cube_penalty_range_hpp
#define cube_penalty_range_hpp

#include <functional>
#include <memory>

#include "i_penalty_force_range.h"

namespace fj {
    class BoundingBox;
    class CubePenaltyRange;
}

class fj::CubePenaltyRange : public IPenaltyForceRange
{
public:
    CubePenaltyRange() = delete;
    ~CubePenaltyRange() = default;
    
    CubePenaltyRange(std::unique_ptr<fj::BoundingBox> bbBox)
    : fj::IPenaltyForceRange( std::move(nullptr) )
    {

    }
    
     fj::Vector3 direction(const fj::Vector3& position)const override;
    
protected:
    const fj::BoundingBox& getBB()const
    {
        return std::cref(*m_bb);
    }
    
private:
    std::unique_ptr<fj::BoundingBox> m_bb;
};

#endif /* cube_penalty_range_hpp */

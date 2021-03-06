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

/**
 * 軸平行バウンディングボックスの内部に戻るようなペナルティレンジ
 */
class fj::CubePenaltyRange : public IPenaltyForceRange
{
public:
    CubePenaltyRange() = delete;
    ~CubePenaltyRange() = default;
    
    CubePenaltyRange(const fj::Scalar& K, std::unique_ptr<fj::BoundingBox> bbBox)
    : fj::IPenaltyForceRange(K)
    , m_bb( std::move(bbBox) )
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

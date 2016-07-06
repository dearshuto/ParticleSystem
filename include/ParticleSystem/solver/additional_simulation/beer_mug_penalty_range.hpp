//
//  beer_mug_penalty_range.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/07/02.
//
//

#ifndef beer_mug_penalty_range_hpp
#define beer_mug_penalty_range_hpp

#include <memory>
#include <FUJIMath/type/scalar.h>
#include "i_penalty_force_range.h"

namespace fj {
    class BeerMugPenaltyRange;
}

/**
 * ビールジョッキのシーンを作るために用意したペナルティレンジ
 * 形状は単純なシリンダーで、デフォルトはyアップ.
 * 内部では上方に一定の力が働く
 */
class fj::BeerMugPenaltyRange : public fj::IPenaltyForceRange
{
public:
    BeerMugPenaltyRange() = delete;
    ~BeerMugPenaltyRange() = default;
    
    BeerMugPenaltyRange(const fj::Scalar& K, const fj::Scalar& radius, const fj::Vector3& center, const fj::Scalar& height, const bool transpose)
    : fj::IPenaltyForceRange(K)
    , m_radius(radius)
    , m_center(center)
    , m_height(height)
    , m_transpose(transpose)
    {
        
    }
    
    fj::Vector3 direction(const fj::Vector3& position)const override;
    
public:
    /**
     * 底辺の円の半径
     */
    const fj::Scalar& getRadius()const
    {
        return m_radius;
    }
    
    /**
     * 底辺の中心
     */
    const fj::Vector3& getCenter()const
    {
        return m_center;
    }
    
    /**
     * 底辺からの高さ
     */
    const fj::Scalar& getHeight()const
    {
        return m_height;
    }
    
    /**
     * yアップならtrue, zアップならfalseを返す
     */
    bool isTranspose()const
    {
        return m_transpose;
    }
private:
    fj::Scalar m_radius;
    fj::Vector3 m_center;
    fj::Scalar m_height;
    bool m_transpose;
};

#endif /* beer_mug_penalty_range_hpp */

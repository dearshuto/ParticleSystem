//
//  beer_mug_penalty_range.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/07/02.
//
//

#include <algorithm>

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/solver/additional_simulation/beer_mug_penalty_range.hpp>

fj::Vector3 fj::BeerMugPenaltyRange::computeDirection(const fj::Vector3 &position)const
{
    // 円柱を定義して、円柱の中では上方に力を加える
    // 「円の内部か→高さは範囲内か」のようにチェックする
    // 円の内部判定に高さ成分はいらないので、いったん0にして計算する
    // 高さ方向は定数
    
    const fj::Vector3 kNoForce(0, 0, 0);
    fj::Vector3 direction = getCenter() - position;


    // zアップかyアップか
    if (isTranspose())
    {
        direction.z() = 0;
    }
    else
    {
        direction.y() = 0;
    }
    
    
    if ( std::max(fj::Scalar(0), getRadius() - direction.norm()) )
    {
        direction.y() = 0.01;
        return direction.normalized();
    }
    
    return kNoForce;
}
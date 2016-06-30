//
//  i_penalty_force_range.h
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#ifndef i_penalty_force_range_h
#define i_penalty_force_range_h

namespace fj {
    class Vector3;
    class IPenaltyForceRange;
}

class fj::IPenaltyForceRange
{
protected:
    IPenaltyForceRange() = default;
public:
    virtual~IPenaltyForceRange() = default;
    
    /**
     * ペナルティ法が適用される領域に入っているときに押し出される方向を返す. 領域外の時は0ベクトルを返す
     */
    virtual fj::Vector3 direction(const fj::Vector3& position)const = 0;
};

#endif /* i_penalty_force_range_h */

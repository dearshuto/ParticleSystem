//
//  i_penalty_force_range.h
//  ParticleSystem
//
//  Created by Shuto on 2016/06/30.
//
//

#ifndef i_penalty_force_range_h
#define i_penalty_force_range_h

#include <functional>
#include <memory>

namespace fj {
    class Vector3;
    class IPenaltyForceRange;
}

// TODO: インタフェースじゃじゃないので名前を変えたい
class fj::IPenaltyForceRange
{
public:
    IPenaltyForceRange() = delete;
    virtual~IPenaltyForceRange() = default;
    
    IPenaltyForceRange(const fj::Scalar& K)
    : m_K(K)
    {
        
    }
    
    /**
     * ペナルティ法が適用される領域に入っているときに押し出される力を返す. 領域外の時は0ベクトルを返す
     */
    virtual fj::Vector3 direction(const fj::Vector3& position)const = 0;
    
protected:
    
    /**
     * バネ係数を取得する
     */
    const fj::Scalar& getK()const
    {
        return m_K;
    }
private:
    const fj::Scalar m_K;
};

#endif /* i_penalty_force_range_h */

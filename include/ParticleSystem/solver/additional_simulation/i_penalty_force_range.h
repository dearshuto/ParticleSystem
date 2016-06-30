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

// TODO インタフェースじゃないから名前を変えたい
class fj::IPenaltyForceRange
{
public:
    IPenaltyForceRange() = delete;
    virtual~IPenaltyForceRange() = default;
    
    IPenaltyForceRange(std::unique_ptr<IPenaltyForceRange> other = nullptr)
    : m_other( std::move(other) )
    {
        
    }
    
    /**
     * ペナルティ法が適用される領域に入っているときに押し出される方向を返す. 領域外の時は0ベクトルを返す
     */
    fj::Vector3 direction(const fj::Vector3& position)const
    {
        return computeDirection(position) + ( m_other ?  getOther().computeDirection(position) : fj::Vector3(0, 0, 0));
    }
    
protected:
    virtual fj::Vector3 computeDirection(const fj::Vector3& position)const = 0;
    
    const fj::IPenaltyForceRange& getOther()const
    {
        return std::cref(*m_other);
    }
private:
    std::unique_ptr<IPenaltyForceRange> m_other;
};

#endif /* i_penalty_force_range_h */

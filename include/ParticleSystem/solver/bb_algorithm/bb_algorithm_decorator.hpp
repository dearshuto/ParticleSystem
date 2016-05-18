//
//  bb_algorithm_decorator.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/17.
//
//

#ifndef bb_algorithm_decorator_hpp
#define bb_algorithm_decorator_hpp

#include <functional>
#include <memory>

#include "bb_algorithm.h"
#include "bounding_box.hpp"

namespace fj {
    class BoundingBox;
    class BBAlgorithmDecorator;
}

/**
 * デコレータパターンの装飾アルゴリズム. バウンディングボックスを利用するアルゴリズムはこのクラスを継承する.
 */
class fj::BBAlgorithmDecorator : public fj::BBAlgorithm
{
public:
    BBAlgorithmDecorator() = delete;
    virtual ~BBAlgorithmDecorator() = default;
    
    BBAlgorithmDecorator(std::unique_ptr<fj::BBAlgorithm> bb, const unsigned int priority = 0)
    : fj::BBAlgorithm(priority)
    , m_bbAlgorithm( std::move(bb) )
    , m_tickSkipCount(0)
    , m_TickSkipNum(1)
    {
        
    }
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override
    {
        getBBPAlgorithPtr()->execute(timestep, particleSystem);
        
        if ( getTickSkipNum() <= (++m_tickSkipCount) )
        {
            m_tickSkipCount = 0;
            executeBBAlgorithm(particleSystem);
        }
        
    }
    
    const fj::BoundingBox& getBoundingBox()const override
    {
        return getBBAlgorithm().getBoundingBox();
    }
    
protected:
    
    virtual void executeBBAlgorithm(fj::ParticleSystem* particleSystem) = 0;
    
public:
    
    const fj::BBAlgorithm& getBBAlgorithm()const
    {
        return std::cref(*m_bbAlgorithm);
    }
    
    void setTickSkipNum(const unsigned int step)
    {
        m_TickSkipNum = step;
    }
    
protected:
    
    std::unique_ptr<fj::BBAlgorithm>& getBBPAlgorithPtr()
    {
        return std::ref(m_bbAlgorithm);
    }
    
    unsigned int getTickSkipNum()const
    {
        return m_TickSkipNum;
    }
    
private:
    std::unique_ptr<fj::BBAlgorithm> m_bbAlgorithm;
    
    /**
     * 更新を飛ばした回数
     */
    unsigned int m_tickSkipCount;
    
    /**
     * 更新を飛ばす回数
     */
    unsigned int m_TickSkipNum;
};

#endif /* bb_algorithm_decorator_hpp */

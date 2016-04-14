//
//  bounding_box.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/14.
//
//

#ifndef bounding_box_hpp
#define bounding_box_hpp

#include <tuple>
#include <memory>
#include <vector>

#include <FUJIMath/type/scalar.h>

namespace fj {
    class Particle;
    class ParticleManager;
    class BoundingBox;
}



class fj::BoundingBox
{
public:
   class Range
    {
    public:
        Range() = delete;
        ~Range() = default;
        
        Range(const fj::Scalar& min, const fj::Scalar& max, const int& resolution)
        : m_range(min, max)
        , m_resolution(resolution)
        , m_divisionSize( std::abs(max - min) / fj::Scalar(resolution))
        {
            
        }
        
        const fj::Scalar& getMin()const
        {
            return std::get<0>(m_range);
        }
        
        const fj::Scalar& getMax()const
        {
            return std::get<1>(m_range);
        }
        
        const int getResolusion()const
        {
            return m_resolution;
        }
        
        const fj::Scalar& getDivisionSize()const
        {
            return m_divisionSize;
        }
        
    private:
        const std::pair<fj::Scalar, fj::Scalar> m_range;
        const int m_resolution;
        const fj::Scalar m_divisionSize;
    };

public:
    BoundingBox() = delete;
    ~BoundingBox() = default;
    
    BoundingBox(const Range& xRange, const Range& yRange, const Range& zRange, const fj::Scalar& resolution)
    : m_xRange(xRange)
    , m_yRange(yRange)
    , m_zRange(zRange)

    {
        m_inBox.resize(xRange.getResolusion() * yRange.getResolusion() * zRange.getResolusion());
    }
    
    void registerParticle(const std::shared_ptr<fj::Particle>& particle);
    
    bool isOutOfRange(const fj::Particle& particle)const;

protected:
    
    void registerInBox(const std::shared_ptr<fj::Particle>& particle);
    
public:

    const Range& getRangeX()const
    {
        return m_xRange;
    }
    
    const Range& getRangeY()const
    {
        return m_yRange;
    }

    const Range& getRangeZ()const
    {
        return m_zRange;
    }

private:
    Range m_xRange;
    Range m_yRange;
    Range m_zRange;

    std::vector<std::shared_ptr<fj::Particle>> m_inBox;
    std::vector<std::shared_ptr<fj::Particle>> m_outOfRangeParticle;
};

#endif /* bounding_box_hpp */

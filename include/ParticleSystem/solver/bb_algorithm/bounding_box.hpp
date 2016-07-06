//
//  bounding_box.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/14.
//
//

#ifndef bounding_box_hpp
#define bounding_box_hpp

#include <algorithm>
#include <tuple>
#include <memory>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleManager;
    class Solver;
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
        
        Range(const fj::Scalar& min, const fj::Scalar& max)
        : m_range(min, max)
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
        
    private:
        const std::pair<fj::Scalar, fj::Scalar> m_range;
    };

public:
    BoundingBox() = delete;
    ~BoundingBox() = default;
    
    BoundingBox(const Range& xRange, const Range& yRange, const Range& zRange)
    : m_xRange(xRange)
    , m_yRange(yRange)
    , m_zRange(zRange)

    {

    }
    
protected:

    bool isWithinRange(const fj::Particle& particle)const;
    
public:

    const Range& getRange(const int index)const
    {
        switch (index) {
            case 0:
                return getRangeX();
                break;
            case 1:
                return getRangeY();
                break;
            case 2:
                return getRangeZ();
                break;
            default:
                break;
        }
        
        return getRangeX();
    }
    
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

    const std::vector<std::vector<fj::ParticleID>>& getBB()const
    {
        return m_inBox;
    }
    
    const std::vector<fj::ParticleID>& getInBoxParticle()const
    {
        return m_inBoxParticle;
    }
    
private:
    Range m_xRange;
    Range m_yRange;
    Range m_zRange;

    std::vector< std::vector<fj::ParticleID> > m_inBox;
    std::vector<fj::ParticleID> m_inBoxParticle;
    std::vector<fj::ParticleID> m_outOfRangeParticle;
};

#endif /* bounding_box_hpp */

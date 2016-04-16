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

#include <ParticleSystem/particle/particle_id.h>
#include "bb_algorithm.h"

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleManager;
    class Solver;
    class BoundingBox;
}

class fj::BoundingBox : public fj::BBAlgorithm
{
public:
   class Range
    {
    public:
        Range() = delete;
        ~Range() = default;
        
        Range(const fj::Scalar& min, const fj::Scalar& max, const fj::Scalar& divisionSize)
        : m_range(min, max)
        , m_resolution( (max - min) / divisionSize )
        , m_divisionSize( divisionSize )
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
    
    BoundingBox(const Range& xRange, const Range& yRange, const Range& zRange)
    : m_xRange(xRange)
    , m_yRange(yRange)
    , m_zRange(zRange)

    {
        m_inBox.resize(xRange.getResolusion() * yRange.getResolusion() * zRange.getResolusion());
    }
    
    void execute(fj::ParticleSystem* particleSystem)override;
    
    const fj::BoundingBox& getBoundingBox()const override
    {
        return *this;
    }

protected:

    void update(const fj::ParticleManager& particleManager);
    
    bool isOutOfRange(const fj::Particle& particle)const;
    
    bool isOutOfRange(const int x, const int y, const int z)const;
    
    void registerParticle(const fj::Particle& particle);
    
    void registerInBox(const fj::Particle& particle);
    
    int convertPositionToIndex(const int x, const int y, const int z)const
    {
        return x + getRangeX().getResolusion() * y + getRangeX().getResolusion() * getRangeY().getResolusion() * z;
    }
    
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

    const std::vector<std::vector<fj::ParticleID>>& getBB()const
    {
        return m_inBox;
    }
    
    const std::vector<fj::ParticleID>& get(const int x, const int y, const int z)const;

    
private:
    Range m_xRange;
    Range m_yRange;
    Range m_zRange;

    std::vector< std::vector<fj::ParticleID> > m_inBox;
    std::vector<fj::ParticleID> m_outOfRangeParticle;
};

#endif /* bounding_box_hpp */

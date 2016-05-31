//
//  partitioned_bounding_box.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/31.
//
//

#ifndef partitioned_bounding_box_hpp
#define partitioned_bounding_box_hpp

#include <FUJIMath/type/scalar.h>
#include "bounding_box.hpp"

namespace fj {
    class Resolutions;
    template<typename T> class PartitionedBoundingBox;
}

/**
 * 解像度を表す構造体
 */
class fj::Resolutions
{
public:
    Resolutions() = delete;
    ~Resolutions() = default;
    
    Resolutions(const unsigned int resolutionX, const unsigned int resolutionY, const unsigned int resolutionZ)
    : ResolutionX(resolutionX)
    , ResolutionY(resolutionY)
    , ResolutionZ(resolutionZ)
    {
        
    }
    
    const unsigned int ResolutionX;
    const unsigned int ResolutionY;
    const unsigned int ResolutionZ;
};


template<typename T>
class fj::PartitionedBoundingBox : public fj::BoundingBox
{
public:
    
public:
    PartitionedBoundingBox() = delete;
    ~PartitionedBoundingBox() = default;
    
    PartitionedBoundingBox(const Range& rangeX, const Range& rangeY, const Range& rangeZ, const fj::Resolutions& resolutions)
    : fj::BoundingBox(rangeX, rangeY, rangeZ)
    , m_resolutions(resolutions)
    , m_divisionsSizeX( (rangeX.getMax() - rangeX.getMin()) / fj::Scalar(resolutions.ResolutionX))
    , m_divisionsSizeY( (rangeY.getMax() - rangeY.getMin()) / fj::Scalar(resolutions.ResolutionY))
    , m_divisionsSizeZ( (rangeZ.getMax() - rangeZ.getMin()) / fj::Scalar(resolutions.ResolutionZ))
    {
        m_components.resize(resolutions.ResolutionX * resolutions.ResolutionY * resolutions.ResolutionZ);
    }

protected:
    int convertIndex(const int i, const int j, const int k)const
    {
        return i + getResolutions().ResolutionX * j + getResolutions().ResolutionX * getResolutions().ResolutionZ * k;
    }
    
    int convertIndex(const fj::Vector3& position)const
    {
        const int kIndexX = (position.x() - getRangeX().getMin()) / getDivisionsSizeX();
        const int kIndexY = (position.y() - getRangeY().getMin()) / getDivisionsSizeY();
        const int kIndexZ = (position.z() - getRangeZ().getMin()) / getDivisionsSizeZ();
        
        const int kClampedX = clamp(kIndexX, 0, getResolutions().ResolutionX);
        const int kClampedY = clamp(kIndexY, 0, getResolutions().ResolutionY);
        const int kClampedZ = clamp(kIndexZ, 0, getResolutions().ResolutionZ);
        
        return convertIndex(kClampedX, kClampedY, kClampedZ);;
    }
    
    int clamp(const int value, const int min, const int max)const
    {
        return std::max(min, std::min(value, max));
    }
    
public:
    const fj::Resolutions& getResolutions()const
    {
        return m_resolutions;
    }
    
    const T& get(const int i, const int j, const int k)const
    {
        return m_components[convertIndex(i, j, k)];
    }

    const T& get(const int index)const
    {
        return m_components[index];
    }
    
    size_t size()const
    {
        return m_components.size();
    }
    
    void set(const int i, const int j, const int k, const T& t)
    {
        const int kIndex = convertIndex(i, j, k);
        m_components[kIndex] = t;
    }
    
    void set(const int index, const T& t)
    {
        m_components[index] = t;
    }
    
    void add(const int i, const int j, const int k, const T& t)
    {
        const int kIndex = convertIndex(i, j, k);
        add(kIndex, t);
    }

    void add(const int index, const T& t)
    {
        m_components[index] += t;
    }
    
    const fj::Scalar& getDivisionsSizeX()const
    {
        return m_divisionsSizeX;
    }
    
    const fj::Scalar& getDivisionsSizeY()const
    {
        return m_divisionsSizeY;
    }
    
    const fj::Scalar& getDivisionsSizeZ()const
    {
        return m_divisionsSizeZ;
    }
    
private:
    fj::Resolutions m_resolutions;
    
    const fj::Scalar m_divisionsSizeX;

    const fj::Scalar m_divisionsSizeY;
    
    const fj::Scalar m_divisionsSizeZ;
    
    std::vector<T> m_components;
};

#endif /* partitioned_bounding_box_hpp */

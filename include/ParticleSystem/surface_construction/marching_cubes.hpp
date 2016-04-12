//
//  marching_cubes.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/12.
//
//

#ifndef marching_cubes_hpp
#define marching_cubes_hpp

#include <tuple>

namespace fj {
    class MarchingCubes;
}

class fj::MarchingCubes
{
public:
    typedef std::pair<int , int> Range_t;
public:
    MarchingCubes() = default;
    virtual~MarchingCubes() = default;
    
    MarchingCubes(const Range_t& xRange, const Range_t& yRange, const Range_t& zRange, const float resolution)
    : m_xRange(xRange)
    , m_yRange(yRange)
    , m_zRange(zRange)
    , m_resolution(resolution)
    {
        
    }
    
    /**
     * メッシュを更新する
     */
    void execute();
    
    const Range_t& getRangeX()const
    {
        return m_xRange;
    }

    const Range_t& getRangeY()const
    {
        return m_yRange;
    }

    const Range_t& getRangeZ()const
    {
        return m_zRange;
    }

    float getResolution()const
    {
        return m_resolution;
    }
    
private:
    const Range_t m_xRange;
    const Range_t m_yRange;
    const Range_t m_zRange;
    const float m_resolution;
};

#endif /* marching_cubes_hpp */

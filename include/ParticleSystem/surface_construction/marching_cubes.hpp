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
#include <vector>

#include <FUJIMath/type/vector3.hpp>

namespace fj {
    class MarchingCubes;
}

class fj::MarchingCubes
{
    typedef std::tuple<unsigned int, unsigned int, unsigned int> TriangleIndex_t;
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
    
public:
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
    
    const std::vector<fj::Vector3>& getVertices()const
    {
        return m_vertices;
    }
    
    const std::vector<TriangleIndex_t>& getTriangleIndices()const
    {
        return m_triangleIndices;
    }

private:
    std::vector<fj::Vector3>* getVertices()
    {
        return &m_vertices;
    }
    
    std::vector<TriangleIndex_t>* getTriangleIndices()
    {
        return &m_triangleIndices;
    }

    
private:
    const Range_t m_xRange;
    const Range_t m_yRange;
    const Range_t m_zRange;
    const float m_resolution;
    
    std::vector<fj::Vector3> m_vertices;
    std::vector<TriangleIndex_t> m_triangleIndices;
};

#endif /* marching_cubes_hpp */

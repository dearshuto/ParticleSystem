//
//  marching_cubes.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/12.
//
//

#ifndef marching_cubes_hpp
#define marching_cubes_hpp

#include <array>
#include <tuple>
#include <vector>

#include <FUJIMath/type/vector3.hpp>

namespace fj {
    class Vector3;
    class ParticleManager;
    class MarchingCubes;
}

class fj::MarchingCubes
{
    typedef std::array<float, 8> CubeValue_t;
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
    , m_isosurfaceValue(0.5)
    {
        
    }
    
    /**
     * メッシュを更新する
     */
    void execute(const fj::ParticleManager& particleManager);
    
private:
    
    void clear();
    
    
    void updateMesh(const fj::ParticleManager& particleManager);
    
    void addMesh(const CubeValue_t& cube);
    
    uint8_t calculateFlagIndex(const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
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
    
    float getIsosurfaceValue()const
    {
        return m_isosurfaceValue;
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
    std::vector<fj::Vector3>* getVerticesPtr()
    {
        return &m_vertices;
    }
    
    std::vector<TriangleIndex_t>* getTriangleIndicesPtr()
    {
        return &m_triangleIndices;
    }

    
private:
    const Range_t m_xRange;
    const Range_t m_yRange;
    const Range_t m_zRange;
    const float m_resolution;
    
    float m_isosurfaceValue;
    
    std::vector<fj::Vector3> m_vertices;
    std::vector<TriangleIndex_t> m_triangleIndices;
};

#endif /* marching_cubes_hpp */

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
#include <memory>
#include <vector>

#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/bb_algorithm/bb_algorithm.h>

namespace fj {
    class BoundingBox;
    class Vector3;
    class ParticleManager;
    class MarchingCubes;
}

class fj::MarchingCubes : public fj::BBAlgorithm
{
    typedef std::array<float, 8> CubeValue_t;
public:
    typedef std::tuple<unsigned int, unsigned int, unsigned int> TriangleIndex_t;
public:
    MarchingCubes() = delete;
    virtual~MarchingCubes() = default;

    MarchingCubes(std::unique_ptr<fj::BBAlgorithm> bbAlgorithm)
    : m_bbAlgorithm( std::move(bbAlgorithm) )
    {
        
    }
    
    void execute(fj::ParticleManager* particleManager) override;
    
    const fj::BoundingBox& getBoundingBox()const override
    {
        return m_bbAlgorithm->getBoundingBox();
    }

    
    /**
     * メッシュを更新する
     */
    void execute(const fj::ParticleManager& particleManager, const fj::BoundingBox& bb);
    
    
private:
    
    void clear();
    
    void updateMesh(const fj::ParticleManager& particleManager, const fj::BoundingBox& bb);
    
    void addMesh(const CubeValue_t& cube, const fj::Vector3& kOffset);
    
    uint8_t calculateFlagIndex(const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
public:
    
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
    std::unique_ptr<fj::BBAlgorithm> m_bbAlgorithm;
    float m_isosurfaceValue;
    
    std::vector<fj::Vector3> m_vertices;
    std::vector<TriangleIndex_t> m_triangleIndices;
};

#endif /* marching_cubes_hpp */

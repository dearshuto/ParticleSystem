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
#include <functional>
#include <tuple>
#include <memory>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/bb_algorithm/bb_algorithm.h>
#include <ParticleSystem/bb_algorithm/mc_bounding_box.hpp>
#include <ParticleSystem/type/mesh.h>

namespace fj {
    class BoundingBox;
    class MCBoundingBox;
    class Vector3;
    class ParticleSystem;
    class MarchingCubesInterface;
    class MarchingCubes;
}


class fj::MarchingCubes : public fj::BBAlgorithm
{
    typedef std::array<float, 8> CubeValue_t;
public:
    MarchingCubes() = delete;
    virtual~MarchingCubes() = default;

    MarchingCubes(std::unique_ptr<fj::MCBoundingBox> bbAlgorithm)
    : m_mcbb( std::move(bbAlgorithm) )
    , m_isosurfaceValue(350)
    {
        
    }
    
    virtual void execute(fj::ParticleSystem* particleSystem) override;
    
    const fj::BoundingBox& getBoundingBox()const override;
    
private:

    fj::Mesh_t createMesh()const;
    
    void addMesh(fj::Mesh_t* mesh, const CubeValue_t& cube, const fj::Vector3& kOffset)const;
    
    void setMeshFromTable(fj::Mesh_t* mesh,const uint8_t flagIndex, const uint32_t edgeFlags, const fj::Vector3& offset)const;
    
    uint8_t calculateFlagIndex(const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
public:

    const fj::MarchingCubesInterface& getMCInterface()const
    {
        return getMCBB();
    }
    
    const fj::MCBoundingBox& getMCBB()const
    {
        return std::cref(*m_mcbb);
    }
    
    float getIsosurfaceValue()const
    {
        return m_isosurfaceValue;
    }
    
private:
    std::unique_ptr<fj::MCBoundingBox> m_mcbb;
    float m_isosurfaceValue;
};

#endif /* marching_cubes_hpp */

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

#include <ParticleSystem/solver/bb_algorithm/mc_bounding_box.hpp>
#include <ParticleSystem/type/mesh.hpp>

#include "surface_construction.hpp"

namespace fj {
    class BoundingBox;
    class MCBoundingBox;
    class Vector3;
    class ParticleSystem;
    class MarchingCubesInterface;
    class MarchingCubes;
}

/**
 * マーチング・キューブ法による表面抽出.
 * 僕はこの手法の拡張を聞いたことがないので, このクラスは継承できないように実装してあります.
 */
class fj::MarchingCubes : public fj::SurfaceConstruction
{
    typedef std::array<float, 8> CubeValue_t;
public:
    MarchingCubes() = delete;
    ~MarchingCubes() = default;
    
    MarchingCubes(std::unique_ptr<fj::MCBoundingBox> mcbb)
    : m_mcbb( std::move(mcbb) )
    {
        
    }
    
    void allocateMemoryAt(const fj::ParticleID& ID)override
    {
        // とくになし
    }
    
private:
    
    fj::Mesh createMesh(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem, const fj::Scalar& level) override;
    /**
     * Levelを閾値として内部と外部を定義したメッシュを作成する
     */
    fj::Mesh createMesh(const fj::Scalar& level, const fj::Dynamics& dynamics)const;
    
    void addMesh(fj::Mesh* mesh, const fj::Scalar& level, const CubeValue_t& cube, const fj::Vector3& kOffset)const;
    
    void setMeshFromTable(fj::Mesh* mesh, const fj::Scalar& level, const uint8_t flagIndex, const uint32_t edgeFlags, const fj::Vector3& offset)const;
    
    uint8_t calculateFlagIndex(const fj::Scalar& level, const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Scalar& level, const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
    const fj::ParticleID& convertVolumePosition(const int x, const int y, const int z)const;
    
    void freeSurfaceMemoryAt(const fj::ParticleID& ID)override
    {
        
    }
    
public:
    
    const fj::MCBoundingBox& getMCBB()const
    {
        return std::cref(*m_mcbb);
    }
    
private:
    std::unique_ptr<fj::MCBoundingBox> m_mcbb;
};

#endif /* marching_cubes_hpp */

//
//  marching_cubes.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/12.
//
//

/*! \mainpage Particle-Based Simulation
 *
 * \section intro_sec Introduction
 *
 * 粒子法を実装した最強プログラム. ParticleSystemクラスがすべてを統括するクラスなので、まずは彼を見てください.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: buildフォルダを作成する
 *
 */

#ifndef marching_cubes_hpp
#define marching_cubes_hpp

#include <array>
#include <functional>
#include <tuple>
#include <memory>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/solver/bb_algorithm/bb_algorithm_decorator.hpp>
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


class fj::MarchingCubes : public fj::SurfaceConstruction
{
    typedef std::array<float, 8> CubeValue_t;
public:
    MarchingCubes() = delete;
    virtual~MarchingCubes() = default;
    
    MarchingCubes(std::unique_ptr<fj::BoundingBox> bb)
    : m_bb( std::move(bb) )
    {
        
    }
    
private:
    
    void executeSurfaceConstruction(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
    /**
     * Levelを閾値として内部と外部を定義したメッシュを作成する
     */
    virtual fj::Mesh createMesh(const fj::Scalar& level, const fj::Dynamics& dynamics)const;
    
    void addMesh(fj::Mesh* mesh, const CubeValue_t& cube, const fj::Vector3& kOffset)const;
    
    void setMeshFromTable(fj::Mesh* mesh,const uint8_t flagIndex, const uint32_t edgeFlags, const fj::Vector3& offset)const;
    
    uint8_t calculateFlagIndex(const fj::Scalar& level, const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Scalar& level, const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
    const fj::ParticleID& convertVolumePosition(const int x, const int y, const int z)const;
    
public:
    
    const fj::BoundingBox& getBB()const
    {
        return  std::cref(*m_bb);
    }
    
private:
    std::unique_ptr<fj::BoundingBox> m_bb;
};

#endif /* marching_cubes_hpp */

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

#include <ParticleSystem/bb_algorithm/bb_algorithm_decorator.hpp>
#include <ParticleSystem/bb_algorithm/mc_bounding_box.hpp>
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

    MarchingCubes(std::unique_ptr<fj::MCBoundingBox> bbAlgorithm)
    : SurfaceConstruction(std::move(bbAlgorithm))
    {
        
    }
    
private:
    

    virtual fj::Mesh createMesh(const fj::Scalar& level)const override;
    
    void addMesh(fj::Mesh* mesh, const CubeValue_t& cube, const fj::Vector3& kOffset)const;
    
    void setMeshFromTable(fj::Mesh* mesh,const uint8_t flagIndex, const uint32_t edgeFlags, const fj::Vector3& offset)const;
    
    uint8_t calculateFlagIndex(const fj::Scalar& level, const CubeValue_t& cubeValue)const;

    fj::Vector3 computeInteractionPoint(const fj::Scalar& level, const fj::Vector3& vertex1, const fj::Vector3& vertex2)const;
    
public:

    const fj::MarchingCubesInterface& getMCInterface()const
    {
        return getMCBB();
    }
    
    const fj::MCBoundingBox& getMCBB()const
    {
        return  static_cast<const fj::MCBoundingBox&>( const_cast<fj::BBAlgorithm&>( getBBAlgorithm()) );
    }
    
};

#endif /* marching_cubes_hpp */

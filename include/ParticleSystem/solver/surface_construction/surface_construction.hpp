//
//  surface_construction.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#ifndef surface_construction_h
#define surface_construction_h

#include <memory>

#include <FUJIMath/type/scalar.h>

#include <ParticleSystem/type/mesh.hpp>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Mesh;
    class SurfaceConstruction;
}

/**
 * 表面抽出
 */
class fj::SurfaceConstruction : public fj::Solver
{
public:
    SurfaceConstruction()
    : fj::Solver(fj::Solver::Priority::kSurfaceCunstruction)
    {
        
    }
    virtual~SurfaceConstruction() = default;
    
    SurfaceConstruction(const fj::SurfaceConstruction& other) = delete;
    SurfaceConstruction& operator=(const fj::SurfaceConstruction& other) = delete;
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override
    {// 表面抽出の機能だと明示するために、あえて別の関数として継承させる
        executeSurfaceConstruction(timestep, particleSystem);
    }
    
private:

    /**
     * fj::Solver::executeを通じて呼ばれる関数.
     */
    virtual void executeSurfaceConstruction(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) = 0;
    
public:
    
    const fj::Mesh& getMesh(const unsigned int index)
    {
        return std::cref(m_mesh[index]);
    }
    
private:
    std::vector<fj::Mesh> m_mesh;
};

#endif /* surface_construction_h */

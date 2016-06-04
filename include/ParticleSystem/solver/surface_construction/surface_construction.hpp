//
//  surface_construction.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#ifndef surface_construction_h
#define surface_construction_h

#include <tuple>
#include <memory>

#include <FUJIMath/type/scalar.h>

#include <ParticleSystem/type/mesh.hpp>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Mesh;
    class SurfaceConstruction;
}

/**
 * 等値面抽出
 */
class fj::SurfaceConstruction : public fj::Solver
{
    class Isosurface
    {
    public:
        Isosurface() = delete;
        ~Isosurface() = default;
        
        Isosurface(const fj::Scalar& level)
        : m_level(level)
        {
            
        }
        
        Isosurface(const Isosurface& other) = default;
        Isosurface& operator=(const Isosurface& other) = default;
        
    public:
        const fj::Scalar& getLevel()const
        {
            return std::cref(m_level);
        }
    public:
        fj::Mesh Mesh;
    private:
        const fj::Scalar m_level;
    };
public:
    SurfaceConstruction()
    : fj::Solver(fj::Solver::Priority::kSurfaceCunstruction)
    {
        
    }
    virtual~SurfaceConstruction() = default;
    
    SurfaceConstruction(const fj::SurfaceConstruction& other) = delete;
    SurfaceConstruction& operator=(const fj::SurfaceConstruction& other) = delete;
    
    void execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)override;
    
    void allocateIsosurface(const fj::Scalar& level);
    
private:
    
    virtual fj::Mesh createMesh(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem, const fj::Scalar& level) = 0;
    
public:
    
    const fj::Mesh& getMesh(const unsigned int index)
    {
        return std::cref(m_mesh[index]);
    }
    
private:
    std::vector<fj::Mesh> m_mesh;
    std::vector<Isosurface> m_surfaces;
};

#endif /* surface_construction_h */

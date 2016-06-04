//
//  surface_construction.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/solver/surface_construction/surface_construction.hpp>
#include <ParticleSystem/type/mesh.hpp>

void fj::SurfaceConstruction::execute(const fj::Scalar &timestep, fj::ParticleSystem *particleSystem)
{
    for (auto& isosurface : m_surfaces)
    {
        isosurface.Mesh = createMesh(timestep, particleSystem, isosurface.getLevel());
    }
}

void fj::SurfaceConstruction::allocateIsosurface(const fj::Scalar &level)
{
    Isosurface surface(level);
//    m_surfaces.push_back(std::move(surface));
    m_surfaces.emplace_back(level);
}
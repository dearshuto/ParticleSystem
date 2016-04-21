//
//  surface_construction.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/surface_construction/surface_construction.hpp>
#include <ParticleSystem/type/mesh.hpp>

void fj::SurfaceConstruction::executeBBAlgorithm(fj::ParticleSystem *particleSystem)
{
    particleSystem->clearMesh();
    
    for (auto& mesh : *particleSystem->getMeshesPtr())
    {
        mesh = std::move( createMesh(mesh.getLevel()) );
    }
    
}
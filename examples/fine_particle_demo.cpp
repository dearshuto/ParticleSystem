//
//  fluid_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/25.
//
//

#include <iostream>
#include <fstream>
#include <memory>

#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_dem.hpp>
#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/solver/surface_construction/marching_cubes.hpp>
#include <ParticleSystem/solver/additional_simulation/penalty_force.hpp>
#include <ParticleSystem/solver/additional_simulation/cylinder_penalty_range.hpp>
#include <ParticleSystem/solver/additional_simulation/cube_penalty_range.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kOffset = 0.01 * 0.35;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    std::unique_ptr<fj::SPHDEM> solver(new fj::SPHDEM);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    fj::BoundingBox::Range kRange(0, 0.2);
    const fj::Resolutions kResolutions(100, 100, 100);
    
    std::unique_ptr<fj::MCBoundingBox> bb(new fj::MCBoundingBox(kRange, kRange, kRange, kResolutions) );
    std::unique_ptr<fj::SurfaceConstruction> surface(new fj::MarchingCubes(std::move(bb)));

    std::unique_ptr<fj::BoundingBox> bbP(new fj::BoundingBox(kRange, kRange, kRange));
    std::unique_ptr<fj::IPenaltyForceRange> penaltyForceRange(new fj::CylinderPenaltyRange(fj::Scalar(0.2), fj::Vector3(0, 0, 0), nullptr) );
    std::unique_ptr<fj::IPenaltyForceRange> cube(new fj::CubePenaltyRange(std::move(bbP)) );
    std::unique_ptr<fj::IPenaltyForceRange> cylinder(new fj::CylinderPenaltyRange(fj::Scalar(0.1), fj::Vector3(0, 0, 0), fj::Scalar(0.5)));
    std::unique_ptr<fj::PenaltyForce> penaltyForce(new fj::PenaltyForce());
    
    penaltyForce->addPenaltyForceRange( std::move(cube) );
    penaltyForce->addPenaltyForceRange( std::move(cylinder) );
    
    fj::ParticleSystem particleSystem(std::move(solver) );
    
    particleSystem.addSolver( std::move(collisionDispatcher) );
    particleSystem.addSolver( std::move(surface) );
    particleSystem.addSolver( std::move(penaltyForce) );
    particleSystem.allocateIsosurface(fj::Scalar(120));
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < 1; k++) {
                particleSystem.createParticle(fj::Vector3(0.05, 0.05, 0.05) + fj::Vector3(fj::Scalar(i) * kOffset, fj::Scalar(j) * kOffset, 0));
            }
        }
    }
    
    particleSystem.initSimulation();

    particleSystem.removeParticle(fj::ParticleID(0));
    particleSystem.removeParticle(fj::ParticleID(1));
    
    for (int i = 0; i < 10; i++)
    {
        particleSystem.stepSimulation( kTimestep );
        particleSystem.stepParticlePosition(kTimestep);
    }
    
    const auto& verticesSub = particleSystem.getMesh(0);
    
    std::ofstream ofsSub("testSub.obj");
    
    for (const auto& vertexSub : verticesSub.getVertices())
    {
        ofsSub << "v " << vertexSub.x() << " " << vertexSub.y() << " " << vertexSub.z() << std::endl;
    }
    
    for (const auto& indexSub : verticesSub.getTriangleIndices())
    {
        ofsSub << "f " << std::get<0>(indexSub) + 1 << "// " << std::get<1>(indexSub) + 1 << "// " << std::get<2>(indexSub) + 1 << "//" << std::endl;
    }
    
    return EXIT_SUCCESS;
}
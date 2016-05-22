//
//  fine_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/21.
//
//

#include <iostream>
#include <fstream>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/solver/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_method.hpp>
#include <ParticleSystem/solver/dynamics/external_force/gravity_force.hpp>
#include <ParticleSystem/solver/surface_construction/marching_cubes.hpp>
#include <ParticleSystem/type/simulation_constant.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    fj::BoundingBox::Range kRange(0, 0.05, 0.001);
//    std::unique_ptr<fj::MCBoundingBox> bb(new fj::MCBoundingBox(kRange, kRange, kRange) );
//    std::unique_ptr<fj::MarchingCubes> mc( new fj::MarchingCubes(std::move(bb)) );
    
    std::unique_ptr<fj::SPHMethod> solver(new fj::SPHMethod);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    std::unique_ptr<fj::GravityForce> gravity(new fj::GravityForce(std::move(solver), fj::Vector3(0, -9.8, 0)));
//    fj::ParticleSystem particleSystem(std::move(solver));
    fj::ParticleSystem particleSystem(std::move(gravity));
//    fj::ParticleSystem particleSystem(std::move(solver), std::move(collisionDispatcher), std::move(mc));
    
//    particleSystem.addSolver( std::move(collisionDispatcher) );
//    particleSystem.addSolver( std::move(bb) );
    
    particleSystem.createIsosurface(150);
    particleSystem.createIsosurface(170);
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < 1; k++) {
                particleSystem.createParticle(fj::Vector3(0.02 + fj::Scalar(i) * kParticleRadius, 0.02 + fj::Scalar(j) * kParticleRadius, 0.02 + fj::Scalar(k) * kParticleRadius));
            }
        }
    }
    
    for (int i = 0; i < 100; i++)
    {
        auto iterator = particleSystem.getParticleManager().iterator();
        
        particleSystem.stepSimulation(kTimestep);
        particleSystem.stepParticlePosition(kTimestep);
    }
    
    const auto& vertices = particleSystem.getMeshes()[0].getVertices();
    const auto& indices = particleSystem.getMeshes()[0].getTriangleIndices();
    
    std::ofstream ofs("test.obj");
    
    for (const auto& vertex : vertices)
    {
        ofs << "v " << vertex.x() << " " << vertex.y() << " " << vertex.z() << std::endl;
    }
    
    for (const auto& index : indices)
    {
        ofs << "f " << std::get<0>(index) + 1 << "// " << std::get<1>(index) + 1 << "// " << std::get<2>(index) + 1 << "//" << std::endl;
    }

    
    const auto& verticesSub = particleSystem.getMeshes()[1].getVertices();
    const auto& indicesSub = particleSystem.getMeshes()[1].getTriangleIndices();
    
    std::ofstream ofsSub("testSub.obj");
    
    for (const auto& vertexSub : verticesSub)
    {
        ofsSub << "v " << vertexSub.x() << " " << vertexSub.y() << " " << vertexSub.z() << std::endl;
    }
    
    for (const auto& indexSub : indicesSub)
    {
        ofsSub << "f " << std::get<0>(indexSub) + 1 << "// " << std::get<1>(indexSub) + 1 << "// " << std::get<2>(indexSub) + 1 << "//" << std::endl;
    }

    return EXIT_SUCCESS;
}
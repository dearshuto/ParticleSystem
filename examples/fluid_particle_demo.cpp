//
//  fine_particle_demo.cpp
//  particle_system
//
//  Created by Shuto Shikama on 2016/02/21.
//
//

#include <iostream>
#include <fstream>

#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/surface_construction/marching_cubes.hpp>
#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/solver/sph_method.hpp>

int main(int argc, char** argv)
{
    constexpr fj::Scalar kTimestep = fj::Scalar(1) / fj::Scalar(250);
    constexpr fj::Scalar kParticleRadius = fj::SimulationConstant::PARTICLE_RADIUS;
    const fj::Scalar kBLockSize = kParticleRadius * 5;
    
    fj::BoundingBox::Range kRange(0, 2.0, 0.01);
    std::unique_ptr<fj::MCBoundingBox> bb(new fj::MCBoundingBox(kRange, kRange, kRange) );
    std::unique_ptr<fj::MarchingCubes> mc( new fj::MarchingCubes(std::move(bb)) );
    
    std::unique_ptr<fj::SPHMethod> solver(new fj::SPHMethod);
    std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispatcher( new fj::ParticleCollisionDispatcher(10, 10, 10, kBLockSize));
    fj::ParticleSystem particleSystem(std::move(solver), std::move(collisionDispatcher), std::move(mc));
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                particleSystem.createParticle(fj::Vector3(0.05 + fj::Scalar(i) * kParticleRadius, 0.05 + fj::Scalar(j) * kParticleRadius, 0.05 + fj::Scalar(k) * kParticleRadius));
            }
        }
    }
    
    for (int i = 0; i < 8; i++)
    {
        auto iterator = particleSystem.getParticleManager().iterator();
        
        particleSystem.stepSimulation(kTimestep);
        particleSystem.stepParticlePosition(kTimestep);
        particleSystem.clearMesh();
    }
    
    const auto& vertices = particleSystem.m_mesh.first;
    const auto& indices = particleSystem.m_mesh.second;
    
    std::ofstream ofs("test.obj");
    
    for (const auto& vertex : vertices)
    {
        ofs << "v " << vertex.x() << " " << vertex.y() << " " << vertex.z() << std::endl;
    }
    
    for (const auto& index : indices)
    {
        ofs << "f " << std::get<0>(index) << "// " << std::get<1>(index) << "// " << std::get<2>(index) << "//" << std::endl;
    }
    
    return EXIT_SUCCESS;
}
//
//  particle_system.cpp
//  blood-simulation
//
//  Created by Shuto Shikama on 2016/02/13.
//
//

//#include <iostream>
//
//#include "collision_object.hpp"
//#include "particle.hpp"
//
//#include "particle_system.hpp"
//
//void mlk::ParticleSystem::createParticle()
//{
//    createParticleAt(0, 0, 0);
//}
//
//void mlk::ParticleSystem::createParticleAt(const float x, const float y, const float z)
//{
//    std::shared_ptr<mlk::Particle> particle = std::make_shared<mlk::Particle>(x, y, z);
//    m_particles.push_back( particle );
//    
//    if (getCollisionSimulatorPtr()) {
//        getCollisionSimulatorPtr()->createCollisionParticle(particle);
//    }
//}
//
//bool mlk::ParticleSystem::loadModelFromFile(const std::string &filename)
//{
////    return m_model.loadFromFile(filename);
//}
//
//void mlk::ParticleSystem::stepSimulation(const float timestep)
//{
//
//    if (getCollisionSimulatorPtr()) {
//        applyForceUsingSimulator(timestep);
//    }
//    
//    applyGravity();
//}
//
//void mlk::ParticleSystem::applyForceUsingSimulator(const float timestep)
//{
//    
//    const int kBroadphasePairNum = getCollisionSimulatorPtr()->getCollisionPairNum();
//    
//    for (int i = 0; i < kBroadphasePairNum; i++)
//    {
//        auto collisionPair = std::move (getCollisionSimulatorPtr()->createCollisionPairAt(i) );
//        computeInteraction( std::move(collisionPair) );
//    }
//    
//    getCollisionSimulatorPtr()->stepSimulation(timestep);
//}
//
//void mlk::ParticleSystem::computeInteraction(std::unique_ptr<mlk::CollisionObjectPair> collisionPair)const
//{
//    auto object1 = collisionPair->getObject1();
//    auto object2 = collisionPair->getObject2();
//    
//    object1->affectedBy( std::ref(*object2) );
//    object2->affectedBy( std::ref(*object1) );
//}
//
//void mlk::ParticleSystem::applyGravity()
//{
//    const mlk::Vector3& kGravity = getGravity();
//    
//    for (auto& particle : getParticles())
//    {
//        particle->applyForce(kGravity.x(), kGravity.y(), kGravity.z());
//    }
//}
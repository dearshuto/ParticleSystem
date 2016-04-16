//
//  penalty_force.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/bb_algorithm/penalty_force.hpp>

void fj::PenaltyForce::execute(fj::ParticleManager* particleManager, const fj::NeighborMap& neighborMap, const fj::Solver& solver)
{
    m_bb->execute(particleManager, neighborMap, solver);
    
    const fj::BoundingBox::Range& kRangeX = getBoundingBox().getRangeX();
    const fj::BoundingBox::Range& kRangeY = getBoundingBox().getRangeY();
    const fj::BoundingBox::Range& kRangeZ = getBoundingBox().getRangeZ();
    

//    for (auto& particle : particleManager)
//    {
//        const fj::Vector3& kPosition = particle->getPosition();
//        
//        if( fj::Scalar kIX = (kRangeX.getMin() - kPosition.x()) > 0)
//        {
//            particle->addVelocity( m_K * kIX * fj::Vector3(0.1, 0, 0) );
//        }
//
//        if( fj::Scalar kAX = (kRangeX.getMax() - kPosition.x()) < 0)
//        {
//            particle->addVelocity( m_K * kAX * fj::Vector3(-0.1, 0, 0) );
//        }
//
//        if( fj::Scalar kY = (kRangeY.getMin() - kPosition.y()) > 0)
//        {
//            particle->addVelocity( m_K * kY * fj::Vector3(0, 1, 0) );
//        }
//
//        if( fj::Scalar kY = (kRangeY.getMin() - kPosition.y()) < 0)
//        {
//            particle->addVelocity( m_K * kY * fj::Vector3(0, 1, 0) );
//        }
//
//        if( fj::Scalar kZ = (kRangeZ.getMin() - kPosition.z()) > 0)
//        {
//            particle->addVelocity( m_K * kZ * fj::Vector3(0, 0, 1) );
//        }
//
//        if( fj::Scalar kZ = (kRangeZ.getMin() - kPosition.z()) < 0)
//        {
//            particle->addVelocity( m_K * kZ * fj::Vector3(0, 0, 1) );
//        }
//
//    }
    
}
//
//  penalty_force.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <FUJIMath/type/scalar.h>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/bb_algorithm/penalty_force.hpp>

void fj::PenaltyForce::executeBBAlgorithm(fj::ParticleSystem* particleSystem)
{
    const fj::BoundingBox::Range& kRangeX = getBoundingBox().getRangeX();
    const fj::BoundingBox::Range& kRangeY = getBoundingBox().getRangeY();
    const fj::BoundingBox::Range& kRangeZ = getBoundingBox().getRangeZ();

    auto iterator = particleSystem->getParticleManager().iterator();

    while ( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const fj::Vector3& kPosition = kParticle.getPosition();
        
        if( fj::Scalar kIX = (kRangeX.getMin() - kPosition.x()) > 0)
        {
            particleSystem->addAccelAt(kID, m_K * kIX * fj::Vector3(1, 0, 0) );
        }

        if( fj::Scalar kAX = (kRangeX.getMax() - kPosition.x()) < 0)
        {
            particleSystem->addAccelAt(kID, m_K * kAX * fj::Vector3(-1, 0, 0) );
        }

        if( fj::Scalar kY = (kRangeY.getMin() - kPosition.y()) > 0)
        {
            particleSystem->addAccelAt(kID, m_K * kY * fj::Vector3(0, 1, 0) );
        }

        if( fj::Scalar kY = (kRangeY.getMax() - kPosition.y()) < 0)
        {
            particleSystem->addAccelAt(kID, m_K * kY * fj::Vector3(0, -1, 0) );
        }

        if( fj::Scalar kZ = (kRangeZ.getMin() - kPosition.z()) > 0)
        {
            particleSystem->addAccelAt(kID, m_K * kZ * fj::Vector3(0, 0, 1) );
        }

        if( fj::Scalar kZ = (kRangeZ.getMax() - kPosition.z()) < 0)
        {
            particleSystem->addAccelAt(kID, m_K * kZ * fj::Vector3(0, 0, -1) );
        }

    }
    
}
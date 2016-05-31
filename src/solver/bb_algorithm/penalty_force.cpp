//
//  penalty_force.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <FUJIMath/type/scalar.h>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/bb_algorithm/bounding_box.hpp>
#include <ParticleSystem/solver/bb_algorithm/penalty_force.hpp>

void fj::PenaltyForce::execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)
{
    const fj::Scalar kOffset = 0;
    const fj::BoundingBox::Range& kRangeX = getBB().getRangeX();
    const fj::BoundingBox::Range& kRangeY = getBB().getRangeY();
    const fj::BoundingBox::Range& kRangeZ = getBB().getRangeZ();

    auto iterator = particleSystem->getParticleManager().iterator();

    while ( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const fj::Vector3& kPosition = kParticle.getPosition();
        
        if( fj::Scalar kIX = (kRangeX.getMin() - kPosition.x()) > kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kIX * fj::Vector3(1, 0, 0) );
        }

        if( fj::Scalar kAX = (kRangeX.getMax() - kPosition.x()) < kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kAX * fj::Vector3(-1, 0, 0) );
        }

        if( fj::Scalar kY = (kRangeY.getMin() - kPosition.y()) > kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kY * fj::Vector3(0, 1, 0) );
        }

        if( fj::Scalar kY = (kRangeY.getMax() - kPosition.y()) < kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kY * fj::Vector3(0, -1, 0) );
        }

        if( fj::Scalar kZ = (kRangeZ.getMin() - kPosition.z()) > kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kZ * fj::Vector3(0, 0, 1) );
        }

        if( fj::Scalar kZ = (kRangeZ.getMax() - kPosition.z()) < kOffset)
        {
            particleSystem->addAccelAt(kID, m_K * kZ * fj::Vector3(0, 0, -1) );
        }

    }
    
}
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
#include <ParticleSystem/solver/additional_simulation/i_penalty_force_range.h>
#include <ParticleSystem/solver/additional_simulation/penalty_force.hpp>

void fj::PenaltyForce::addPenaltyForceRange(std::unique_ptr<fj::IPenaltyForceRange> pfRange)
{
    m_penaltyRanges.push_back( std::move(pfRange) );
}

void fj::PenaltyForce::executeAdditionalSimulation(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)
{
    auto iterator = particleSystem->getParticleManager().iterator();

    while ( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        
        for (const auto& kRange : getPenaltyRanges())
        {
            // TODO: kRangeにポインタがはいってくるのを改善したい。const変数に->を使うのは一貫性を失うため
            const fj::Vector3 kDirection = kRange->direction( kParticle.getPosition() );

            kRange->direction( kParticle.getPosition() );
            particleSystem->addAccelAt(kParticle.getID(), m_K * kDirection );
        }
        
    }
    
}
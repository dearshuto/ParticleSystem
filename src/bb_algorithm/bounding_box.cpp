//
//  bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/14.
//
//

#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/particle_manager.hpp>

#include <ParticleSystem/bb_algorithm/bounding_box.hpp>

void fj::BoundingBox::execute(fj::ParticleSystem *particleSystem)
{
    update( particleSystem->getParticleManager() );
}

void fj::BoundingBox::update(const fj::ParticleManager &particleManager)
{
//    m_inBox.clear();
//    m_outOfRangeParticle.clear();
    
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        
        registerParticle(kParticle);
    }
    
}

void fj::BoundingBox::registerParticle(const fj::Particle &particle)
{
    
    if ( isOutOfRange( particle ) )
    {
        m_outOfRangeParticle.push_back(particle.getID());
    }
    else
    {
        registerInBox( particle );
    }
    
}

bool fj::BoundingBox::isOutOfRange(const fj::Particle &particle)const
{
    const fj::Vector3& kPosition = particle.getPosition();
    
    if ( (kPosition.x() < getRangeX().getMin()) || (getRangeX().getMax() < kPosition.x()) )
    {
        return true;
    }

    if ( (kPosition.y() < getRangeY().getMin()) || (getRangeY().getMax() < kPosition.y()) )
    {
        return true;
    }

    if ( (kPosition.z() < getRangeZ().getMin()) || (getRangeZ().getMax() < kPosition.z()) )
    {
        return true;
    }

    
    return false;
}

void fj::BoundingBox::registerInBox(const fj::Particle &particle)
{
    const fj::Vector3& kPosition = particle.getPosition();
    const int kIndexX = std::abs(kPosition.x() - getRangeX().getMin()) / getRangeX().getDivisionSize();
    const int kIndexY = std::abs(kPosition.y() - getRangeY().getMin()) / getRangeY().getDivisionSize();
    const int kIndexZ = std::abs(kPosition.z() - getRangeZ().getMin()) / getRangeZ().getDivisionSize();
    const int kIndex = kIndexX + getRangeX().getResolusion() * kIndexY + getRangeX() .getResolusion() * getRangeY().getResolusion() * kIndexZ;
    
    m_inBox[kIndex].push_back( particle.getID() );
}

const std::vector<fj::ParticleID>& fj::BoundingBox::get(const int x, const int y, const int z)const
{
    const int kIndex =x + getRangeX().getResolusion() * y + getRangeX().getResolusion() * getRangeY().getResolusion() * z;
    
    return m_inBox[kIndex];
}
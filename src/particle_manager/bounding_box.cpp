//
//  bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/14.
//
//

#include <FUJIMath/type/vector3.hpp>

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/bounding_box.hpp>

void fj::BoundingBox::registerParticle(const std::shared_ptr<fj::Particle> &particle)
{
    
    if ( isOutOfRange(std::cref(*particle)) )
    {
        registerInBox( particle );
    }
    else
    {
        m_outOfRangeParticle.push_back(particle);
    }
    
}

bool fj::BoundingBox::isOutOfRange(const fj::Particle &particle)const
{
    const fj::Vector3& kPosition = particle.getPosition();
    
    if ( (kPosition.x() < getRangeX().getMin()) || (getRangeX().getMax() < kPosition.x()) )
    {
        return false;
    }

    if ( (kPosition.y() < getRangeY().getMin()) || (getRangeY().getMax() < kPosition.y()) )
    {
        return false;
    }

    if ( (kPosition.z() < getRangeZ().getMin()) || (getRangeZ().getMax() < kPosition.z()) )
    {
        return false;
    }

    
    return true;
}

void fj::BoundingBox::registerInBox(const std::shared_ptr<fj::Particle> &particle)
{
    
}
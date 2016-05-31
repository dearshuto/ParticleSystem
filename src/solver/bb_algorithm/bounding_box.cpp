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

#include <ParticleSystem/solver/bb_algorithm/bounding_box.hpp>

//void fj::BoundingBox::update(const fj::ParticleManager &particleManager)
//{
//    auto iterator = particleManager.iterator();
//    
//    while (iterator->hasNext())
//    {
//        const fj::Particle& kParticle = iterator->next();
//        
//        registerParticle(kParticle);
//    }
//    
//}

//void fj::BoundingBox::registerParticle(const fj::Particle &particle)
//{
//    
//    if ( isOutOfRange( particle ) )
//    {
//        m_outOfRangeParticle.push_back(particle.getID());
//    }
//    else
//    {
//        m_inBoxParticle.push_back(particle.getID());
//    
//        registerInBox( particle );
//    }
//    
//}

bool fj::BoundingBox::isWithinRange(const fj::Particle &particle)const
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

//bool fj::BoundingBox::isOutOfRange(const int x, const int y, const int z)const
//{
//    const int kIndex = convertPositionToIndex(x, y, z);
//    
//    if (m_inBox.size() <= kIndex)
//    {
//        return true;
//    }
//    
//    return false;
//}
//
//void fj::BoundingBox::registerInBox(const fj::Particle &particle)
//{
//    const fj::Vector3& kPosition = particle.getPosition();
//    const int kIndex = convertPositionToIndex(kPosition);
//    
//    m_inBox[kIndex].push_back( particle.getID() );
//}

//int fj::BoundingBox::convertPositionToIndex(const fj::Vector3 &position)const
//{
//    const int kIndexX = (position.x() - getRangeX().getMin()) / getRangeX().getDivisionSize();
//    const int kIndexY = (position.y() - getRangeY().getMin()) / getRangeY().getDivisionSize();
//    const int kIndexZ = (position.z() - getRangeZ().getMin()) / getRangeZ().getDivisionSize();
//    
//    const int kClampedX = clamp(kIndexX, getRangeX());
//    const int kClampedY = clamp(kIndexY, getRangeY());
//    const int kClampedZ = clamp(kIndexZ, getRangeZ());
//    
//    return convertPositionToIndex(kClampedX, kClampedY, kClampedZ);;
//}
//
//int fj::BoundingBox::convertPositionToIndex(const int x, const int y, const int z)const
//{
//    return x + getRangeX().getResolusion() * y + getRangeX().getResolusion() * getRangeY().getResolusion() * z;
//}
//
//int fj::BoundingBox::clamp(const int value, const fj::BoundingBox::Range &range)const
//{
//    return std::max(0, std::min(value, range.getResolusion()) );
//}
//
//const std::vector<fj::ParticleID>& fj::BoundingBox::get(const int x, const int y, const int z)const
//{
//    const int kIndex = convertPositionToIndex(x, y, z);
//    
//    return m_inBox[kIndex];
//}
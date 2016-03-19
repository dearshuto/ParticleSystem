//
//  NeighborMap2D.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/18.
//
//

#include <cmath>
#include <FUJIMath/extend/position.hpp>

#include <ParticleSystem/neighbor_search/neighbor_map.hpp>
#include <ParticleSystem/particle/particle.hpp>

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
const typename fj::NeighborMap<W, H, D>::ParticleContainer&
fj::NeighborMap<W, H, D>::getNeighborParticles(const fj::Particle &particle)const
{
    const fj::Position& kPosition = particle.getPosition();
    const HashValue kHash = computeHashValueFromPosition(kPosition);
    
    return getHashMap()[kHash];
}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::update()
{
    const HashMap& kHashMap = getPartisions();
    
    for (int i = 0; i < kHashMap.size(); i++)
    {
        updateContainerAt(i);
    }
    
}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::updateContainerAt(const HashValue hash)
{
    ParticleContainer container = getPartisions()[hash];
    
    for (const auto& particle : container)
    {
        
    }

}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::registerParticle(const std::shared_ptr<fj::Particle> particle)
{
    const HashValue kHash = computeHashValueFromPosition(particle->getPosition());
    ParticleContainer* container = getContainerPtr(kHash);
    
    container->push_back(particle);
}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
typename fj::NeighborMap<W, H, D>::HashValue
fj::NeighborMap<W, H, D>::computeHashValueFromPosition(const fj::Position &position)const
{
    const int kX = std::round(position.x());
    const int kY = std::round(position.y());
    const int kZ = std::round(position.z());
    
    return getPartitionsWidth() * kX + getPartitionsHeight() * kY + getPartitionsDepth() * kZ;
}
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

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::update()
{
    
}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::registerParticle(const std::shared_ptr<fj::Particle> particle)
{
    const HashValue kHash = computeHashValueFromPosition(particle->getPosition());
}

template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D>
void fj::NeighborMap<W, H, D>::removeParticle(const std::shared_ptr<fj::Particle> particle)
{
    
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
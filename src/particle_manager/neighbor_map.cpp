//
//  neighbor_map.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <cmath>

#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>

void fj::NeighborMap::addNeighborInformation(const fj::Particle &particle1, const fj::Particle &particle2)
{
    // メモリを消費するが、アクセスを簡単にするために対象のデータ構造にする
    
    const fj::ParticleID& kID1 = particle1.getID();
    const fj::ParticleID& kID2 = particle2.getID();
    const fj::Vector3 kDirection21 = particle1.getPosition() - particle2.getPosition();
    const fj::Scalar kSquaredDistance = kDirection21.squaredNorm();
    const fj::Scalar kDistance = std::sqrt( kSquaredDistance );
    const fj::Vector3 kNormalizedDirection21 = kDirection21 / kDistance;
    
    m_neighbors[kID1].emplace_back(kID2, kNormalizedDirection21, kSquaredDistance, kDistance);
}

void fj::NeighborMap::clear()
{
    for (auto& neighbor : m_neighbors)
    {
        neighbor.second.clear();
    }
    
}
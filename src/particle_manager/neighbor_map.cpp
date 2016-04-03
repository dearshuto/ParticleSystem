//
//  neighbor_map.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>

void fj::NeighborMap::addNeighborInformation(const fj::ParticleID &ID1, const fj::ParticleID &ID2, const fj::Scalar &distance)
{
    // メモリを消費するが、アクセスを簡単にするために対象のデータ構造にする
    
    m_neighbors.emplace(std::make_pair(ID1, NeighborInformation(ID2, distance)));
    m_neighbors.emplace(std::make_pair(ID2, NeighborInformation(ID1, distance)));
}
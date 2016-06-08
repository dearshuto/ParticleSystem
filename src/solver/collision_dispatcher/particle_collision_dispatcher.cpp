//
//  particle_collision_dispatcher.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>

#include <ParticleSystem/particle_system.hpp>
#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/type/simulation_constant.hpp>

#include <ParticleSystem/solver/collision_dispatcher/particle_collision_dispatcher.hpp>

void fj::ParticleCollisionDispatcher::freeSimulationMemoryAt(const fj::ParticleID &ID)
{
    this->freeFromCell(ID);
    this->freeFromHashMap(ID);
}

void fj::ParticleCollisionDispatcher::freeFromCell(const fj::ParticleID &ID)
{
    for (auto& particles : m_cells)
    {
        particles.erase( std::remove(std::begin(particles), std::end(particles), ID) );
    }
}

void fj::ParticleCollisionDispatcher::freeFromHashMap(const fj::ParticleID &ID)
{
    m_hashTable.erase(ID);
}

void fj::ParticleCollisionDispatcher::execute(const fj::Scalar &timestep, fj::ParticleSystem *particleSystem)
{
    update( particleSystem->getParticleManager() );
    makeCollision(particleSystem);
}

void fj::ParticleCollisionDispatcher::update(const fj::ParticleManager& particleManager)
{
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const HashValue_t kHash = computeHash(kParticle);
        auto found = m_hashTable.find(kParticle.getID());

        if( found != std::end(m_hashTable) )
        {
            updateAt(kHash, found->second, kID);
        }
        else
        {
            m_hashTable[kID] = kHash;
            m_cells[kHash].push_back(kID);
        }

    }
}

void fj::ParticleCollisionDispatcher::updateAt(const HashValue_t &currentHash, const HashValue_t& previousHash,  const fj::ParticleID& ID)
{
    // ハッシュ値が変わっていたら、所属するセルを変更する
    // ハッシュテーブルの値も更新する
    
    if (previousHash != currentHash)
    {
        const Particles& kPreviousCell = m_cells[previousHash];
        const auto& found = std::find(std::begin(kPreviousCell), std::end(kPreviousCell), ID);
        assert(found != std::end(kPreviousCell));
        
        m_cells[previousHash].erase(found);
        m_cells[currentHash].push_back(ID);
        m_hashTable[ID] = currentHash;
    }
    
}

void fj::ParticleCollisionDispatcher::makeCollision(fj::ParticleSystem* particleSystem)const
{
    const fj::ParticleManager& kParticleManager = particleSystem->getParticleManager();
    auto iterator = kParticleManager.iterator();
    
    while( iterator->hasNext() )
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const auto kNeighbors = getNeighborParticlesAt(kParticle, kParticleManager);
        
        for (const auto& neighbor : kNeighbors)
        {
            particleSystem->makeCollision(kID, neighbor);
        }
        
    }
}

fj::Particle::NeighborParticles fj::ParticleCollisionDispatcher::getNeighborParticlesAt(const fj::Particle &particle, const fj::ParticleManager& particleManager)const
{
    const HashValue_t kHash = computeHash( particle );
    fj::Particle::NeighborParticles neighborParticles;
    
    for (int x = -1; x < 2; x++){
        for (int y = -1; y < 2; y++){
            for (int z = -1; z < 2; z++)
            {
                
                const Particles*const kCell = getSideCell(kHash, x, y, z);
                if (kCell) {
                    setNeighbors(particle, std::cref(*kCell), &neighborParticles, particleManager);
                }
                
            }
        }
    }

    return neighborParticles;
}

void fj::ParticleCollisionDispatcher::setNeighbors(const fj::Particle &particle, const Particles &cell, fj::Particle::NeighborParticles *neighborParticles, const fj::ParticleManager& particleManager)const
{
    constexpr fj::Scalar kH2 = 0.01 * 0.01;
    
    for (const auto& neighbor : cell)
    {
        const fj::Particle& kNeighborParticle = particleManager.search(neighbor);
        
        fj::Scalar kDistance = (kNeighborParticle.getPosition() - particle.getPosition()).squaredNorm();
        
        if (kDistance == 0) {
            continue;
        }
        
        if (kDistance < kH2)
        {
            neighborParticles->push_back(neighbor);
        }
    }
    
}

const fj::ParticleCollisionDispatcher::Particles*const fj::ParticleCollisionDispatcher::getSideCell(const HashValue_t &hash, const int x, const int y, const int z)const
{
    const int kShiftedHash = hash + x + getWidth() * y + getWidth() * getHeight() * z;
    
    if ( (0 <= kShiftedHash) && (kShiftedHash < m_cells.size()))
    {
        const HashValue_t kHash = static_cast<HashValue_t>(kShiftedHash);
        return &m_cells[kHash];
    }
    
    return nullptr;
}

fj::ParticleCollisionDispatcher::HashValue_t fj::ParticleCollisionDispatcher::computeHash(const fj::Particle& particle)const
{
    const fj::Vector3& kPosition = particle.getPosition();
    const fj::Scalar& kX = clamp( kPosition.x() );
    const fj::Scalar& kY = clamp( kPosition.y() );
    const fj::Scalar& kZ = clamp( kPosition.z() );
    const HashValue_t kHash = kX + getWidth() * kY + getWidth() * getHeight() * kZ;
    
    assert(0 <= kHash);
    assert(kHash < m_cells.size());
    
    return kHash;
}

unsigned int fj::ParticleCollisionDispatcher::clamp(const fj::Scalar &num)const
{
    const fj::Scalar kClamped = std::max<fj::Scalar>(num, fj::Scalar(0));
    
    return std::floor<unsigned int>(kClamped / getBlockSize());
}
//
//  particle_collision_dispatcher.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <algorithm>
#include <cmath>
#include <functional>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/type/simulation_constant.hpp>

#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

void fj::ParticleCollisionDispatcher::initialize(const fj::ParticleManager &particleManager)
{
    
    for (const auto& particle : particleManager)
    {
        const HashValue_t& kHash = computeHash( std::cref(*particle) );
        
        m_cells[kHash].push_back(particle);
    }
    
}

void fj::ParticleCollisionDispatcher::registerParticle(const std::shared_ptr<fj::Particle>& particle)
{
    const HashValue_t kHash = computeHash( std::cref(*particle) );
    m_cells[kHash].push_back(particle);
}

void fj::ParticleCollisionDispatcher::updated()
{
    const size_t kCellSize = m_cells.size();
    
    for (int i = 0; i < kCellSize; i++)
    {
        updatedAt(i);
    }
    
}

void fj::ParticleCollisionDispatcher::updatedAt(const HashValue_t &currentHash)
{
    // 走査しながらハッシュ値を計算していく. 走査と削除を並行して実行するにはイテレータをもちいたトリッキーなアルゴリズムを使うので要注意
    // ハッシュ値が変わっていたら削除してあらたなセルに追加する
    
    Particles& currentCell = m_cells[currentHash];
    
    for (Particles::iterator it = std::begin(currentCell); it != std::end(currentCell);)
    {
        const std::shared_ptr<fj::Particle> particle = *it;
        const HashValue_t kHash = computeHash( std::cref(*particle) );
        
        if (kHash != currentHash)
        {
            it = currentCell.erase(it);
            m_cells[kHash].push_back(particle);
        }
        else
        {
            it++;
        }
        
    }

}

fj::Particle::NeighborParticles fj::ParticleCollisionDispatcher::getNeighborParticlesAt(const fj::Particle &particle)const
{
    const HashValue_t kHash = computeHash( particle );
    fj::Particle::NeighborParticles neighborParticles;
    
    for (int x = -1; x < 2; x++){
        for (int y = -1; y < 2; y++){
            for (int z = -1; z < 2; z++)
            {
                
                const Particles*const kCell = getSideCell(kHash, x, y, z);
                if (kCell) {
                    setNeighbors(particle, std::cref(*kCell), &neighborParticles);
                }
                
            }
        }
    }

    return neighborParticles;
}

void fj::ParticleCollisionDispatcher::setNeighbors(const fj::Particle &particle, const Particles &cell, fj::Particle::NeighborParticles *neighborParticles)const
{
    constexpr fj::Scalar kH2 = fj::SimulationConstant::SQUARED_H;
    
    for (const auto& neighbor : cell)
    {
        
        fj::Scalar kDistance = (neighbor->getPosition() - particle.getPosition()).squaredNorm();
        
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
    
    return kX + getWidth() * kY + getWidth() * getHeight() * kZ;
}

unsigned int fj::ParticleCollisionDispatcher::clamp(const fj::Scalar &num)const
{
    const fj::Scalar kClamped = std::max<fj::Scalar>(num, fj::Scalar(0));
    
    return std::floor<unsigned int>(kClamped / getBlockSize());
}
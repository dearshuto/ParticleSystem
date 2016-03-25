//
//  particle_collision_dispatcher.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <cmath>
#include <functional>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>

#include <ParticleSystem/collision_dispatcher/particle_collision_dispatcher.hpp>

void fj::ParticleCollisionDispatcher::initialize(const fj::ParticleManager &particleManager)
{
    
    for (const auto& particle : particleManager)
    {
        const HashValue& kHash = computeHash( std::cref(*particle) );
        
        m_cells[kHash].push_back(particle);
    }
    
}
    
void fj::ParticleCollisionDispatcher::updated()
{
    const size_t kCellSize = m_cells.size();
    
    for (int i = 0; i < kCellSize; i++)
    {
        updatedAt(i);
    }
    
}

void fj::ParticleCollisionDispatcher::updatedAt(const HashValue &currentHash)
{
    // 走査しながらハッシュ値を計算していく. 走査と削除を並行して実行するにはイテレータをもちいたトリッキーなアルゴリズムを使うので要注意
    // ハッシュ値が変わっていたら削除してあらたなセルに追加する
    
    Particles& currentCell = m_cells[currentHash];
    
    for (Particles::iterator it = std::begin(currentCell); it != std::end(currentCell);)
    {
        const std::shared_ptr<fj::Particle> particle = *it;
        const HashValue kHash = computeHash( std::cref(*particle) );
        
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
    const HashValue kHash = computeHash( particle );
    const Particles& kParticles = m_cells[kHash];
    
    fj::Particle::NeighborParticles neighborParticles;
    
    for (const auto& particle : kParticles)
    {
        neighborParticles.push_back(particle);
    }
    
    
    return neighborParticles;
}

fj::ParticleCollisionDispatcher::HashValue fj::ParticleCollisionDispatcher::computeHash(const fj::Particle& particle)const
{
    const fj::Vector3& kPosition = particle.getPosition();
    const fj::Scalar& kX = clamp( kPosition.x() );
    const fj::Scalar& kY = clamp( kPosition.y() );
    const fj::Scalar& kZ = clamp( kPosition.z() );
    
    return kX + getWidth() * kY + getWidth() * getHeight() * kZ;
}

unsigned int fj::ParticleCollisionDispatcher::clamp(const fj::Scalar &num)const
{
    return std::floor<unsigned int>(num) / getBlockSize();
}
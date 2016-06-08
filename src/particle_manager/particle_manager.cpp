//
//  particle_manager.cpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#include <functional>
#include <memory>
#include <ParticleSystem/particle/particle.hpp>

#include <ParticleSystem/particle_manager/particle_manager.hpp>

const fj::Particle& fj::ParticleManager::registerParticle(std::unique_ptr<fj::Particle> particle, const bool movable)
{
    std::shared_ptr<fj::Particle> sharedParticle = std::move(particle);
    
    m_particles.push_back(sharedParticle);
    m_hashMap[sharedParticle->getID()] = sharedParticle;
    
    if (movable)
    {
        m_flowParticles.push_back(sharedParticle);
    }
    else
    {
        m_boundaryParticles.push_back(sharedParticle);
    
    }
    
    return getLastRegisteredParticle();
}

void fj::ParticleManager::removeParticle(const fj::ParticleID &ID)
{
    removeFromArray(ID);
    removeFromHashMap(ID);
}

void fj::ParticleManager::removeFromArray(const fj::ParticleID &ID)
{
    const std::shared_ptr<fj::Particle>& kParticle = this->search(ID);
    
    removeParticleFromArray(kParticle, &m_particles);
    removeParticleFromArray(kParticle, &m_flowParticles);
    removeParticleFromArray(kParticle, &m_boundaryParticles);
}

void fj::ParticleManager::removeParticleFromArray(const std::shared_ptr<fj::Particle> &particle, ParticleArray *array)
{
    const auto& end = std::end(*array);
    const auto& iterator = std::find(std::begin(*array), end, particle);

    if (iterator != end)
    {
        array->erase(iterator);
    }
}

void fj::ParticleManager::removeFromHashMap(const fj::ParticleID &ID)
{
    const auto& end = std::end(m_hashMap);
    const auto& found = m_hashMap.find(ID);
    
    if (found != end)
    {
        m_hashMap.erase(found);
    }
}

std::unique_ptr<fj::ParticleManager::ConstIterator> fj::ParticleManager::iterator()const
{
    return std::unique_ptr<fj::ParticleManager::ConstIterator>( new ConstIterator(std::cref(*this)) );
}

bool fj::ParticleManager::ConstIterator::hasNext()const
{
    if ( m_searchedIndex < m_particleManager.m_particles.size()) {
        return true;
    }
    
    return false;
}

const fj::Particle& fj::ParticleManager::ConstIterator::next()
{
    return std::cref( *m_particleManager.m_particles[m_searchedIndex++] );
}
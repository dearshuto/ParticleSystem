//
//  particle_manager.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_manager_hpp
#define particle_manager_hpp

#include <cassert>
#include <functional>
#include <memory>
#include <unordered_map>
#include <tuple>
#include <vector>

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class Particle;
    class ParticleManager;
}

/**
 * 粒子の入出力の管理. 粒子の識別はIDを利用する. 粒子に対する処理はこのクラスを通すことでプログラムの頑健性を高める.
 */
class fj::ParticleManager
{
    typedef std::vector<std::shared_ptr<fj::Particle>> ParticleArray;
    class ConstIterator;
public:
    ParticleManager() = default;
    ~ParticleManager() = default;
    
    ParticleManager(const fj::ParticleManager& other) = delete;
    ParticleManager& operator=(const fj::ParticleManager& other) = delete;

    const fj::Particle& operator[](const unsigned int index)const
    {
        assert(index < m_particles.size());
        return std::cref( *m_particles[index] );
    }
    
    const fj::Particle& registerParticle(std::unique_ptr<fj::Particle> particle, const bool movable = true);

    void removeParticle(const fj::ParticleID& ID);
    
    /**
     * 指定されたIDをもつ粒子を返す.
     */
    std::shared_ptr<fj::Particle>& search(const fj::ParticleID& ID)
    {
        assert(m_hashMap.find(ID) != std::end(m_hashMap));
        return std::ref(m_hashMap.at(ID));
    }

    /**
     * 指定されたIDをもつ粒子を返す.
     */
    const fj::Particle& search(const fj::ParticleID& ID)const
    {
        assert(m_hashMap.find(ID) != std::end(m_hashMap));
        return std::cref( *m_hashMap.at(ID) );
    }
    
    ParticleArray::iterator begin()
    {
        return std::begin(m_particles);
    }

    ParticleArray::iterator end()
    {
        return std::end(m_particles);
    }
    
    std::unique_ptr<fj::ParticleManager::ConstIterator> iterator()const;
    
private:
    
    void removeFromArray(const fj::ParticleID& particle);
    
    void removeParticleFromArray(const std::shared_ptr<fj::Particle>& particle, ParticleArray* array);
    
    void removeFromHashMap(const fj::ParticleID& particle);
    
    const fj::Particle& getLastRegisteredParticle()const
    {
        return std::cref( *m_particles[m_particles.size() - 1] );
    }
    
public:
    
    const ParticleArray& getFlowParticles()const
    {
        return m_flowParticles;
    }
    
    ParticleArray* getFlowParticlesPtr()
    {
        return &m_flowParticles;
    }
    
    const ParticleArray& getBoundaryParticles()const
    {
        return m_boundaryParticles;
    }
    
    size_t getRegisteredParticleNum()const
    {
        return m_particles.size();
    }
    
    /**
     * ParticleManagerで使用されていないIDを返す.
     */
    fj::ParticleID getUnusedID()
    {
        // 返す値が絶対にダブらないように死守すること
        static unsigned int i = 0;
        fj::ParticleID id(i++);
        return id;
    }
    
private:
    // ひとつの粒子をいろいろな形式で保持することで、ランダムアクセスやイテレートを可能にする
    // STLを利用すると、仕様上例外が投げられてしまうが、そうならないようにこのクラスで徹底的に管理すること
    
    /**
     * IDをハッシュ値とするハッシュマップで保管された粒子
     */
    std::unordered_map<fj::ParticleID, std::shared_ptr<fj::Particle>> m_hashMap;
    
    /**
     * 1次配列として保管された粒子
     */
    ParticleArray m_particles;

    ParticleArray m_flowParticles;
    ParticleArray m_boundaryParticles;
};


/**
 * ParticleManagerの粒子をconst状態で返すためのイテレータ
 */
class fj::ParticleManager::ConstIterator
{
public:
    ConstIterator() = delete;
    ~ConstIterator() = default;
    
    ConstIterator(const fj::ParticleManager& particleManager)
    : m_particleManager(particleManager)
    , m_searchedIndex(0)
    {
        
    }
    
    bool hasNext()const;
    
    const fj::Particle& next();
    
private:
    const fj::ParticleManager& m_particleManager;
    
    size_t m_searchedIndex;
};

#endif /* particle_manager_hpp */

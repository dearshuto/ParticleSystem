//
//  particle_manager.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef particle_manager_hpp
#define particle_manager_hpp

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
    
    const std::shared_ptr<fj::Particle> registerParticle(std::unique_ptr<fj::Particle> particle, const bool movable = true);

    /**
     * 指定されたIDをもつ粒子を返す.
     */
    std::shared_ptr<fj::Particle>& search(const fj::ParticleID& ID)
    {
        return std::ref(m_hashMap.at(ID));
    }

    /**
     * 指定されたIDをもつ粒子を返す.
     */
    const fj::Particle& search(const fj::ParticleID& ID)const
    {
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
    
public:
    
    const ParticleArray& getFlowParticles()const
    {
        return m_flowParticles;
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
    const fj::ParticleID getUnusedID()
    {
        // 返す値が絶対にダブらないように死守すること
        static unsigned int i = 0;
        return fj::ParticleID(i++);
    }
    
private:
    // ひとつの粒子をいろいろな形式で保持することで、ランダムアクセスやイテレートを可能にする
    // STLを利用すると、仕様上例外が投げられてしまう。そうならないようにこのクラスで徹底的に管理すること
    
    /**
     * 1次配列として保管された粒子
     */
    ParticleArray m_particles;
    
    /**
     * IDをハッシュ値とするハッシュマップで保管された粒子
     */
    std::unordered_map<fj::ParticleID, std::shared_ptr<fj::Particle>> m_hashMap;
    
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

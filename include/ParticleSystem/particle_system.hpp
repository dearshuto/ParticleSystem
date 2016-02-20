//
//  particle_system.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/19.
//
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include <memory>
#include <string>
#include <vector>

#include <ParticleSystem/type/Scalar.h>
#include <ParticleSystem/type/Vector.hpp>

namespace fj {
    class Particle;
    class ParticleSystem;
}

class fj::ParticleSystem
{
public:
    ParticleSystem()
    : m_gravity(0, 0, 0)
    , m_hasActivatedGravity(false)
    {
        
    }
    
    ~ParticleSystem() = default;
    
    void stepSimulation(const float timestep);
    
    
    void createParticleAt(const float x, const float y, const float z);
    void createFineParticle(const float x, const float y, const float z, const float radius, const float mass);
    
    /**
     * @param index1 衝突を検知した粒子のID
     * @param index2 ID1と衝突した粒子のID
     */
    void makeCollision(const int index1, const int index2);
    
    bool hasActivatedGravity()const
    {
        return m_hasActivatedGravity;
    }
    
    void enableGravity()
    {
        m_hasActivatedGravity = true;
    }
    
    void disableGravity()
    {
        m_hasActivatedGravity = false;
    }
    
private:
    void simulateParticleBehavior();
    void applyGravity();
    
//ge tters & setters
public:
    const std::vector<std::shared_ptr<fj::Particle>>& getParticles()const
    {
        return m_particles;
    }
    
    const fj::Vector& getGravity()const
    {
        return m_gravity;
    }
    
    void setGravity(const float x, const float y, const float z)
    {
        m_gravity = fj::Vector(x, y, z);
    }
    
protected:
    std::vector<std::shared_ptr<fj::Particle>>* getParticlesPtr()
    {
        return &m_particles;
    }
    
private:
    std::vector< std::shared_ptr<fj::Particle> > m_particles;
    fj::Vector m_gravity;
    bool m_hasActivatedGravity;
};

#endif /* particle_system_hpp */

//
//  particle_system.hpp
//  blood-simulation
//
//  Created by Shuto Shikama on 2016/02/13.
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
    
    
private:
    std::vector< std::shared_ptr<fj::Particle> > m_particles;
    fj::Vector m_gravity;
    bool m_hasActivatedGravity;
};

#endif /* particle_system_hpp */

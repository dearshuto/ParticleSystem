//
//  particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <ParticleSystem/type/Vector.hpp>


namespace fj {
    class Particle;
}

class fj::Particle
{
public:
    Particle()
    : Particle(fj::Vector(0, 0, 0))
    {
        
    }
    
    virtual~Particle() = default;
    
    Particle(const fj::Vector& position)
    : m_position(position)
    {
        
    }
    
    void applyForce(const fj::Vector& force)
    {
        m_appliedForce += force;
    }
    
// getters
public:
    const fj::Vector& getPosition()const
    {
        return m_position;
    }
    
    const fj::Vector& getForce()const
    {
        return m_appliedForce;
    }
    
private:
    fj::Vector m_position;
    fj::Vector m_appliedForce;
};

#endif /* particle_hpp */

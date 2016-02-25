//
//  particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <cmath>
#include <memory>
#include <vector>
#include <ParticleSystem/type/Vector.hpp>

namespace fj {
    class Particle;
}

class fj::Particle
{
    /**
     * 循環参照を起こさないように弱い参照で保持された近傍粒子
     */
    typedef std::vector<std::weak_ptr<fj::Particle>> NeighborParticles;
public:
    Particle()
    : Particle(fj::Vector(0, 0, 0))
    {
        
    }
    
    virtual~Particle() = default;
    
    
    Particle(const fj::Particle& other) = delete;
    Particle& operator=(const fj::Particle& other) = delete;
    
    
    Particle(const fj::Vector& position)
    : m_radius(1)
    , m_mass(1)
    , m_effectRange(0.01)
    , m_squaredEffectRange( std::pow(m_effectRange, 2) )
    , m_position(position)
    {
        
    }
    
    
    virtual void updateProperty() = 0;
    
    /**
     * 他のパーティクルに与える力を計算する
     */
    virtual fj::Vector affect(const fj::Particle& particle) const = 0;
    
    /**
     * 剛体から受ける力を加える
     * @param 剛体表面からの距離
     */
    virtual void affectedByObject(const fj::Vector& collisionPoint)
    {
        applyForce( computeForceFromObject(collisionPoint) );
    }
    
    /**
     * 近傍粒子を追加する
     */
    void addNeighborParticle(std::shared_ptr<fj::Particle> neighborParticle)
    {
        // 引数はsharedポインタだが、保持はweakポインタで行うので循環参照は発生しない
        m_neighborParticles.push_back(neighborParticle);
    }
    
    /**
     * 保持していた近傍粒子を解放する
     */
    void clearNeighborParticles()
    {
        m_neighborParticles.clear();
    }
    
    /**
     * 近傍から受ける力を全て足し合す
     */
    void accumulateForce();
    
    void applyForce(const fj::Vector& force)
    {
        m_appliedForce += force;
    }
    
    fj::Vector popApliedForce()
    {
        const fj::Vector temp = getForce();
        m_appliedForce = fj::Vector(0, 0, 0);
        return temp;
    }
    
protected:
    
    void accumulateForceByNeighborParticles();
    
    virtual fj::Vector affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) = 0;
    
    /**
     * 剛体から受ける力を計算する
     * @param 剛体表面からの距離
     */
    virtual fj::Vector computeForceFromObject(const fj::Vector& collisionPoint)const = 0;
    
// getters & setters
public:
    const fj::Vector& getPosition()const
    {
        return m_position;
    }
    
	void setPosition(const fj::Vector& position)
	{
		m_position = position;
	}

    const fj::Vector& getForce()const
    {
        return m_appliedForce;
    }
    
    const fj::Particle::NeighborParticles& getNeighborParticles()const
    {
        return m_neighborParticles;
    }
    
    fj::Scalar getRadius()const
    {
        return m_radius;
    }
    
    void setRadius(const fj::Scalar radius)
    {
        m_radius = radius;
    }
    
    fj::Scalar getEffectRange()const
    {
        return m_effectRange;
    }
    
    fj::Scalar getSquaredEffectRange()const
    {
        return m_squaredEffectRange;
    }
    
    fj::Scalar getMass()const
    {
        return m_mass;
    }
    
    void setMass(const fj::Scalar mass)
    {
        m_mass = mass;
    }
    
    const fj::Vector& getVelocity()const
    {
        return m_velocity;
    }
    void setVelocity(const fj::Vector& velocity)
    {
        m_velocity = velocity;
    }
    
    fj::Scalar getPressure()const
    {
        return m_pressure;
    }
    
    void setPressure(const fj::Scalar pressure)
    {
        m_pressure = pressure;
    }

    fj::Scalar getDensity()const
    {
        return m_density;
    }
    
    void setDensity(const fj::Scalar density)
    {
        m_density = density;
    }

protected:
    fj::Particle::NeighborParticles* getNeighborParticlesPtr()
    {
        return &m_neighborParticles;
    }
    
private:
    /**
     * 地震の位置から一定の範囲内に存在するパーティクル
     */
    fj::Particle::NeighborParticles m_neighborParticles;

    fj::Scalar m_radius;

    fj::Scalar m_mass;
    
    fj::Scalar m_effectRange;
    
    fj::Scalar m_squaredEffectRange;
    
    fj::Vector m_position;
    fj::Vector m_appliedForce;
    
    fj::Scalar m_pressure;
    
    fj::Vector m_velocity;
    
    fj::Scalar m_density;
};

#endif /* particle_hpp */

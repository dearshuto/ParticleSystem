//
//  particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef particle_hpp
#define particle_hpp

#define NOMINMAX
#include <cmath>
#include <memory>
#include <vector>
#include <FUJIMath/type/vector3.hpp>

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
    Particle() = delete;
    virtual~Particle() = default;
    
    
    Particle(const fj::Particle& other) = delete;
    Particle& operator=(const fj::Particle& other) = delete;
    
    
    Particle(const int ID, const fj::Vector3& position)
    : m_ID(ID)
    , m_radius( fj::Scalar(1) )
    , m_mass( fj::Scalar(1) )
    , m_effectRange( fj::Scalar(0.01) )
    , m_squaredEffectRange( fj::Scalar(std::pow(m_effectRange, 2)) )
    , m_position(position)
    {
        
    }
    
    /**
     * 近傍粒子の情報をもとに自身の属性を更新する
     */
    virtual void updateProperty() = 0;
    
    /**
     * 他のパーティクルに与える力を計算する
     */
    virtual fj::Vector3 affect(const fj::Particle& particle) const = 0;
    
    /**
     * 剛体から受ける力を加える
     */
    void affectedByObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)
    {
        applyForce( computeForceFromObject(distance, normalizedDirection) );
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
    
    void applyForce(const fj::Vector3& force)
    {
        m_appliedForce += force;
    }
    
    fj::Vector3 popApliedForce()
    {
        const fj::Vector3 temp = getForce();
        m_appliedForce = fj::Vector3(0, 0, 0);
        return temp;
    }
    
    
    void stepSimulation(const fj::Scalar& deltaTime)
    {
        this->addPosition( getVelocity() * deltaTime );
    }
    
protected:
    
    /**
     * 属性値が更新済みの近傍粒子から受ける力をすべて足し合わせる
     */
    void accumulateForceByNeighborParticles();
    
    
    virtual fj::Vector3 affectedBy(const std::weak_ptr<fj::Particle>& neighborParticle) = 0;
    
    
    /**
     * 剛体から受ける力を計算する
     */
    virtual fj::Vector3 computeForceFromObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)const = 0;
    
// getters & setters
public:
    
    unsigned int getID()const
    {
        return m_ID;
    }
    
    const fj::Vector3& getPosition()const
    {
        return m_position;
    }
    
	void setPosition(const fj::Vector3& position)
	{
		m_position = position;
	}

    void addPosition(const fj::Vector3& movement)
    {
        m_position += movement;
    }
    
    const fj::Vector3& getForce()const
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
    
    const fj::Vector3& getVelocity()const
    {
        return m_velocity;
    }
    
    void addVelocity(const fj::Vector3& velocity)
    {
        m_velocity += velocity;
    }
    
	void setVelocity(const fj::Vector3& velocity)
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
     * 各パーティクルを識別するのに利用する数字
     * かならず一意であるように決定し, ハッシュマップなどに利用する
     */
    const unsigned int m_ID;
    
    /**
     * 地震の位置から一定の範囲内に存在するパーティクル
     */
    fj::Particle::NeighborParticles m_neighborParticles;

    fj::Scalar m_radius;

    fj::Scalar m_mass;
    
    fj::Scalar m_effectRange;
    
    fj::Scalar m_squaredEffectRange;
    
    fj::Vector3 m_position;
    fj::Vector3 m_appliedForce;
    
    fj::Scalar m_pressure;
    
    fj::Vector3 m_velocity;
    
    fj::Scalar m_density;
};

#endif /* particle_hpp */

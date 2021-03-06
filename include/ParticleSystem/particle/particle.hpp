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

#include "particle_id.h"

namespace fj {
    class Particle;
}

/**
 * シミュレーションで利用される体積をもたない粒子.
 */
class fj::Particle
{
public:
    /**
     * 循環参照を起こさないように弱い参照で保持された近傍粒子
     */
    typedef std::vector<fj::ParticleID> NeighborParticles;
public:
    Particle() = delete;
    virtual~Particle() = default;
    
    
    Particle(const fj::Particle& other) = delete;
    Particle& operator=(const fj::Particle& other) = delete;
    
    
    Particle(const fj::ParticleID& ID, const fj::Vector3& position)
    : m_ID(ID)
    , m_mass( fj::Scalar(1) )
    , m_position(position)
    , m_velocity( fj::Vector3(0, 0, 0) )
    {
        
    }
    
    void stepSimulation(const fj::Scalar& deltaTime)
    {
        this->addPosition( getVelocity() * deltaTime );
    }

// getters & setters
public:
    
    const fj::ParticleID& getID()const
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
    
private:
    // この粒子クラスが管理する変数はこれ以上増やさないでください.
    // 粒子の計算に追加のパラメータが必要なときはこのクラスを継承したクラスを自作してください
    
    /**
     * 各パーティクルを識別するのに利用する数字
     * かならず一意であるように決定し, ハッシュマップなどに利用する
     */
    const fj::ParticleID m_ID;
    
    /**
     * 質量
     */
    fj::Scalar m_mass;
    
    /**
     * 中心の位置
     */
    fj::Vector3 m_position;

    /**
     * 中心の速度
     */
    fj::Vector3 m_velocity;
};

#endif /* particle_hpp */

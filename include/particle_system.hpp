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

#include "collision_simulator.hpp"
#include "particle.hpp"

namespace mlk {
    class ParticleSystem;
}

class mlk::ParticleSystem
{
public:
    ParticleSystem() = default;
    ~ParticleSystem() = default;
    
    void stepSimulation(const float timestep);
    
    void computeInteraction(std::unique_ptr<mlk::CollisionObjectPair> collisionPair)const;
    
    void createParticle();
    
    void createParticleAt(const float x, const float y, const float z);
    
    /**
     * Load an OBJ model from file system
     */
    bool loadModelFromFile(const std::string& filename);
    
private:
    void applyForceUsingSimulator(const float timestep);
    void applyGravity();
    
//ge tters & setters
public:
    const std::vector<std::shared_ptr<mlk::Particle>>& getParticles()const
    {
        return m_particles;
    }
    
    void setCollisionSimulator(std::unique_ptr<mlk::CollisionSimulator> simulator)
    {
        m_simulator = std::move(simulator);
    }
    
    const mlk::Vector3& getGravity()const
    {
        return m_gravity;
    }
    
    void setGravity(const float x, const float y, const float z)
    {
        m_gravity = mlk::Vector3(x, y, z);
    }
    
protected:
    mlk::CollisionSimulator* getCollisionSimulatorPtr()
    {
        return m_simulator.get();
    }
    
private:
    std::vector<std::shared_ptr<mlk::Particle>> m_particles;
    std::unique_ptr< mlk::CollisionSimulator > m_simulator;
    mlk::Vector3 m_gravity;
};

#endif /* particle_system_hpp */

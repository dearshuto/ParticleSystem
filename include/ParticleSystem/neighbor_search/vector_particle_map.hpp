//
//  vector_particle_map.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/23.
//
//

#ifndef vector_particle_map_hpp
#define vector_particle_map_hpp

#include <memory>
#include <vector>

#include <ParticleSystem/neighbor_search/particle_map.hpp>

namespace fj {
    class VectorParticleMap;
}

class fj::VectorParticleMap : public fj::ParticleMap
{
public:
    VectorParticleMap() = default;
    ~VectorParticleMap() = default;
    
    void registerParticle(std::shared_ptr<fj::Particle> particle) override;
    
    const fj::Particle& getParticleAt(const unsigned int id)const override;
    
private:
    const std::vector<std::shared_ptr<fj::Particle>>& getParticles()const
    {
        return m_particles;
    }
    
    std::vector<std::shared_ptr<fj::Particle>>* getParticlesPtr()
    {
        return &m_particles;
    }
    
private:
    std::vector<std::shared_ptr<fj::Particle>> m_particles;
};

#endif /* vector_particle_map_hpp */

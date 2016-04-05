//
//  sph_method.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef sph_method_hpp
#define sph_method_hpp

#include <memory>
#include <unordered_map>

#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleID;
    class SPHMethod;
}

class fj::SPHMethod : public fj::Solver
{
    class SPHProperty;
public:
    SPHMethod() = default;
    ~SPHMethod() = default;
    
    void compute(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap) override;
    
private:
    void updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    std::unique_ptr<SPHProperty> computePropertyAt(const fj::Particle& particle, const fj::NeighborMap& neighborMap);
    
    void updateAccel(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    
private:
    std::unordered_map<fj::ParticleID, std::unique_ptr<SPHProperty>> m_propertyMap;
    
    constexpr static const fj::Scalar RESTDENSITY = 600;//[kg/m^3] 水の密度
    constexpr static const fj::Scalar PARTICLE_RADIUS = 0.005;//[m]
    constexpr static const fj::Scalar PARTICLE_VOLUME = (4 / 3) * M_PI * PARTICLE_RADIUS * PARTICLE_RADIUS * PARTICLE_RADIUS;//[m^3]
    constexpr static const fj::Scalar PARTICLE_MASS = RESTDENSITY * PARTICLE_VOLUME;//[kg]
    constexpr static const fj::Scalar H = 0.01;//m
    constexpr static const fj::Scalar SQUARED_H = H * H;
    constexpr static const fj::Scalar INSTIFF = 3.f;
    constexpr static const fj::Scalar VISCOSITY = 1.8;
    
    static const fj::Scalar Poly6Kernel;
    static const fj::Scalar SpikyKernel;
    static const fj::Scalar LaplacianKernel;
};


class fj::SPHMethod::SPHProperty
{
public:
    SPHProperty() = delete;
    ~SPHProperty() = default;
    
    SPHProperty(const fj::Scalar& density)
    : m_density(density)
    , m_inverseDensity(fj::Scalar(1) / density)
    {
        m_pressure = (density - RESTDENSITY) * INSTIFF;
    }

    const fj::Scalar& getInverseDensity()const
    {
        return m_inverseDensity;
    }
    
    const fj::Scalar& getPressure()const
    {
        return m_pressure;
    }
    
private:
    const fj::Scalar m_density;
    const fj::Scalar m_inverseDensity;
    fj::Scalar m_pressure;
};

#endif /* sph_method_hpp */
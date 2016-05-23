//
//  sph_method.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef sph_method_hpp
#define sph_method_hpp

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <functional>
#include <memory>
#include <unordered_map>

#include <ParticleSystem/solver/solver.hpp>
#include "continuum_solver.hpp"

namespace fj {
    class Particle;
    class ParticleID;
    class SPHMethod;
}

class fj::SPHMethod : public fj::ContinuumSolver
{
    class SPHProperty;
    class SPHInformation;
public:
    SPHMethod() = default;
    virtual~SPHMethod() = default;
    
    void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
    fj::Scalar calculateScalar(const fj::ParticleID& ID)const override;
    
protected:
    void updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    void updateAccel(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    
    /**
     * 離散化された粒子の密度と圧力を求める
     */
    virtual std::unique_ptr<SPHProperty> computePropertyAt(const fj::Particle& particle, const fj::NeighborMap& neighborMap);

    fj::Vector3 computeForce(const fj::SPHMethod::SPHInformation& sphInfo)const;
    
    /**
     * ナビエストークス方程式の右辺をもとめる
     */
    virtual fj::Vector3 computeKernelTerm(const fj::SPHMethod::SPHInformation& sphInfo)const;

    /**
     * ナビエストークス方程式の右辺のにある圧力項を求める
     */
    virtual fj::Vector3 computePressureTerm(const fj::SPHMethod::SPHInformation& sphInfo)const;

    /**
     * ナビエストークス方程式の右辺にある粘性項を求める
     */
    virtual fj::Vector3 computeVelocityTerm(const fj::SPHMethod::SPHInformation& sphInfo)const;

    /**
     *  ナビエストークス方程式の右辺にあるその他の力を求める. 
     * ここで求めるのは各粒子ごとに異なる力であり、重力のようにすべての粒子に一様にかかる力はここで計算するべきではない. See the ExternalForce class
     */
    virtual fj::Vector3 computeExtraTerm(const fj::SPHMethod::SPHInformation& sphInfo)const;
    
public:
    const SPHProperty& getPropertyAt(const fj::ParticleID& ID)const
    {
        return std::cref( *m_propertyMap.at(ID) );
    }
    
    virtual fj::Scalar getViscosity(const fj::ParticleID& ID)const // 可変粘性をサポートするためにvirtualで実装しておく
    {
        return VISCOSITY;
    }
private:
    std::unordered_map<fj::ParticleID, std::unique_ptr<SPHProperty>> m_propertyMap;
    
    constexpr static const fj::Scalar RESTDENSITY = 600;//[kg/m^3] 水の密度
    constexpr static const fj::Scalar PARTICLE_RADIUS = 0.005;//[m]
    constexpr static const fj::Scalar PARTICLE_VOLUME = (4 / 3) * M_PI * PARTICLE_RADIUS * PARTICLE_RADIUS * PARTICLE_RADIUS;//[m^3]
    constexpr static const fj::Scalar PARTICLE_MASS = RESTDENSITY * PARTICLE_VOLUME;//[kg]
    constexpr static const fj::Scalar H = 0.01;//m
    constexpr static const fj::Scalar SQUARED_H = H * H;
    constexpr static const fj::Scalar INSTIFF = 3.f;
    constexpr static const fj::Scalar VISCOSITY = 10.8;
    
    static const fj::Scalar Poly6Kernel;
    static const fj::Scalar SpikyKernel;
    static const fj::Scalar LaplacianKernel;
};

/**
 * SPH法で計算された値.
 */
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

    const fj::Scalar& getDensity()const
    {
        return m_density;
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

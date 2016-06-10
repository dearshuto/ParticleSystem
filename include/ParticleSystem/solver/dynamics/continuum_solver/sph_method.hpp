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
#include <ParticleSystem/particle_manager/neighbor_map.hpp>

#include "continuum_solver.hpp"

namespace fj {
    class Particle;
    class ParticleID;
    class SPHMethod;
}

class fj::SPHMethod : public fj::ContinuumSolver
{
    typedef fj::ContinuumSolver Super;
protected:
    class SPHProperty;
    class SPHInformation;
public:
    SPHMethod() = default;
    virtual~SPHMethod() = default;
    
    virtual void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
    fj::Scalar calculateScalar(const fj::ParticleID& ID)const override;
    
    /**
     * SPH法で計算した値を保持しておくマップが必要なのでオーバーライドする
     */
    virtual void allocateMemory(const fj::ParticleManager& particleManager)override;
    
private:
    void freeContinuumMemoryAt(const fj::ParticleID& ID) override;
    
    virtual void freeSPHMemoryAt(const fj::ParticleID& ID) = 0;
    
    void updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    
    void updateProperty_ST(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    void updateProperty_MT(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    void updatePropertyIn(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap, const unsigned int min, const unsigned int max);
    
    void updateAccel(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
protected:
    /**
     * 離散化された粒子の密度と圧力を求める
     */
    virtual std::unique_ptr<SPHProperty> computePropertyAt(const fj::Particle& particle, const fj::NeighborMap& neighborMap);

    /**
     * ナビエストークス方程式の右辺を求める
     */
    fj::Vector3 computeForce(const fj::SPHMethod::SPHInformation& sphInfo);
    
    /**
     * Spikyカーネルを利用した勾配項の計算
     */
    virtual fj::Vector3 computeSpikyKernelTerm(const fj::SPHMethod::SPHInformation& sphInfo);

    /**
     * Spikyカーネルで平滑化するスカラ値
     */
    virtual fj::Scalar computeSpikyScalarValue(const fj::SPHMethod::SPHInformation& sphInfo);

    /**
     * ラプラシアンカーネルを利用した項の計算
     */
    virtual fj::Vector3 computeLaplacianKernelTerm(const fj::SPHMethod::SPHInformation& sphInfo);

    /**
     * ラプラシアンカーネルで平滑化するベクトル
     */
    virtual fj::Vector3 computeLaplacianVector(const fj::SPHMethod::SPHInformation& sphInfo);

    /**
     *  ナビエストークス方程式の右辺にあるその他の力を求める.
     * ここで求めるのは各粒子ごとに異なる力であり、重力のようにすべての粒子に一様にかかる力はここで計算するべきではない. See the ExternalForce class
     */
    virtual fj::Vector3 computeExtraTerm(const fj::SPHMethod::SPHInformation& sphInfo);

    /**
     * 圧力の計算
     */
    virtual fj::Scalar computePressureScalar(const fj::SPHMethod::SPHInformation& sphInfo)const;
    
    /**
     * 粘性の計算
     */
    virtual fj::Vector3 computeViscosity(const fj::SPHMethod::SPHInformation& sphInfo)const;
    
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
protected:
    constexpr static const fj::Scalar RESTDENSITY = 600;//[kg/m^3] 水の密度
    constexpr static const fj::Scalar PARTICLE_RADIUS = 0.005;//[m]
    constexpr static const fj::Scalar PARTICLE_VOLUME = (4 / 3) * M_PI * PARTICLE_RADIUS * PARTICLE_RADIUS * PARTICLE_RADIUS;//[m^3]
    constexpr static const fj::Scalar PARTICLE_MASS = RESTDENSITY * PARTICLE_VOLUME;//[kg]
    constexpr static const fj::Scalar H = 0.01;//m
    constexpr static const fj::Scalar SQUARED_H = H * H;
    constexpr static const fj::Scalar INSTIFF = 3.f;
    constexpr static const fj::Scalar VISCOSITY = 10.8;
    
protected:
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


/**
 * SPHの計算で必要なインスタンスの運搬.
 */
class fj::SPHMethod::SPHInformation
{
public:
    SPHInformation() = delete;
    ~SPHInformation() = default;
    
    SPHInformation(
                   const fj::Particle& targetParticle
                   , const SPHProperty& property
                   , const fj::Particle& neighbor
                   , const SPHProperty& neighborProperty
                   , const fj::NeighborMap::NeighborInformation& neighborInfo
                   , const fj::Scalar& weight
                   )
    : TargetParticle(targetParticle)
    , Property(property)
    , NeighborParticle(neighbor)
    , NeighborProperty(neighborProperty)
    , NeighborInformation( neighborInfo )
    , Weight(weight)
    {
        
    }
    
public:
    const fj::Particle& TargetParticle;
    const SPHProperty& Property;
    const fj::Particle& NeighborParticle;
    const SPHProperty& NeighborProperty;
    const fj::NeighborMap::NeighborInformation& NeighborInformation;
    const fj::Scalar Weight;
};
#endif /* sph_method_hpp */

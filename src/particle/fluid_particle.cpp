//
//  fluid_particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#define NOMINMAX
#include <cassert>
#include <cmath>

#include <FUJIMath/type/vector3.hpp>
#include <FUJIMath/type/scalar.h>

#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/particle/fluid_particle.hpp>

void fj::FluidParticle::updateProperty()
{
    // 藤代研究室OBの上田さんのコードをもとに実装されています
    
    constexpr fj::Scalar kSquaredEffectRange = SimulationConstant::SQUARED_H;
    constexpr fj::Scalar kSPH_PMASS = fj::SimulationConstant::PARTICLE_MASS;
    constexpr fj::Scalar kSPH_RESTDENSITY = fj::SimulationConstant::RESTDENSITY;
    constexpr fj::Scalar kSPH_INTSTIFF = fj::SimulationConstant::SPH_INTSTIFF;
    
    const fj::Scalar kPoly6Kern = fj::SimulationConstant::Poly6Kernel;
    
    
    fj::Scalar sum(0);
    
    for (const std::weak_ptr<fj::Particle>& neighborParticleWeakPtr : *getNeighborParticlesPtr())
    {
        const std::shared_ptr<fj::Particle>& neighborParticle = neighborParticleWeakPtr.lock();
        
        // 近傍粒子が突然消えていたらバグ
        assert( !neighborParticleWeakPtr.expired() );
        
        const fj::Vector3 kRelativePosition = this->getPosition() - neighborParticle->getPosition();
        const fj::Scalar kSquaredDistance = kRelativePosition.squaredNorm();
        const fj::Scalar kC = kSquaredEffectRange - kSquaredDistance;
        
        sum += std::pow(kC, 3);
    }
    
    sum += std::pow(kSquaredEffectRange, 3);;
 
    this->setDensity(sum * kSPH_PMASS * kPoly6Kern);
    this->setPressure( (this->getDensity() - kSPH_RESTDENSITY) *  kSPH_INTSTIFF);
    
    this->updateInverseDensity();
}

fj::Vector3 fj::FluidParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticleWeakPtr)
{
    const std::shared_ptr<fj::Particle> neighborParticle = neighborParticleWeakPtr.lock();
    
    // 近傍粒子が突然消えていたらバグ
    assert( !neighborParticleWeakPtr.expired() );
    
    return neighborParticle->affect( std::cref(*this) ) * this->getInverseDensity();
}

fj::Vector3 fj::FluidParticle::affect(const fj::Particle &particle)const
{
    // 藤代研究室0Bの上田さんのコードをもとにして実装されています
    constexpr fj::Scalar kPARTICLE_MASS = fj::SimulationConstant::PARTICLE_MASS;
    constexpr fj::Scalar kH = fj::SimulationConstant::H;
    constexpr fj::Scalar kSPH_VISCOSITY = fj::SimulationConstant::SPH_VISCOSITY;
    
    const fj::Scalar kSpikyKernel = fj::SimulationConstant::SpikyKernel;
    const fj::Scalar kLaplacianKernel = fj::SimulationConstant::LaplacianKernel;
    
    const fj::FluidParticle& kNeighborParticle = std::cref(*this);
    
    const fj::Vector3 kRelativePosition = (particle.getPosition() - kNeighborParticle.getPosition());
    const fj::Scalar kDistance = kRelativePosition.norm();
    const fj::Vector3 kNormalizedRelativePosition = kRelativePosition / kDistance;
    const fj::Scalar kC = kH - kDistance;
    
    
    const fj::Vector3 kVelocityKernelTerm = kSPH_VISCOSITY * (kNeighborParticle.getVelocity() - particle.getVelocity()) * kLaplacianKernel;
    const fj::Vector3 kPressureKernelterm = -fj::Scalar(0.5 * (particle.getPressure() + kNeighborParticle.getPressure()) * kSpikyKernel * kC) * kNormalizedRelativePosition;
    
    const fj::Vector3 kKernelTerm = kVelocityKernelTerm + kPressureKernelterm;
    const fj::Vector3 fcurr = kPARTICLE_MASS * kNeighborParticle.getInverseDensity() * kC * kKernelTerm;
    
    return fcurr;
}

fj::Vector3 fj::FluidParticle::computeForceFromObject(const fj::Scalar& distance, const fj::Vector3& normalizedDirection)const
{
    return fj::Vector3(0, 0, 0);
}
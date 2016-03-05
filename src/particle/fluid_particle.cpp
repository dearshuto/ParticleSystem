//
//  fluid_particle.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <cassert>
#include <cmath>

#include <ParticleSystem/type/Vector.hpp>
#include <ParticleSystem/type/scalar.h>
#include <ParticleSystem/type/simulation_constant.hpp>
#include <ParticleSystem/particle/fluid_particle.hpp>

void fj::FluidParticle::updateProperty()
{
    // 藤代研究室OBの上田さんのコードをもとに実装されています
    
    constexpr fj::Scalar kH = fj::SimulationConstant::H;
    constexpr fj::Scalar kSPH_PMASS = fj::SimulationConstant::SPH_PMASS;
    constexpr fj::Scalar kSPH_RESTDENSITY = fj::SimulationConstant::SPH_RESTDENSITY;
    constexpr fj::Scalar kSPH_INTSTIFF = fj::SimulationConstant::SPH_INTSTIFF;
    constexpr fj::Scalar kSPH_SIMSCALE = fj::SimulationConstant::SPH_SIMSCALE;
    
    const fj::Scalar kPoly6Kern = fj::SimulationConstant::Poly6Kernel;
    
    
    constexpr fj::Scalar kSquaredEffectRange = kH * kH;
    fj::Scalar sum(0);
    
    for (const std::weak_ptr<fj::Particle>& neighborParticleWeakPtr : *getNeighborParticlesPtr())
    {
        const std::shared_ptr<fj::Particle>& neighborParticle = neighborParticleWeakPtr.lock();
        
        // 近傍粒子が突然消えていたらバグ
        assert( !neighborParticleWeakPtr.expired() );
        
        const fj::Vector kRelativePosition = this->getPosition() - neighborParticle->getPosition();
        const fj::Scalar kSquaredDistance = (kRelativePosition * kSPH_SIMSCALE).squaredNorm();
        const fj::Scalar kC = kSquaredEffectRange - kSquaredDistance;
        
        sum += std::pow(kC, 3);
    }
    
 
    this->setDensity(sum * kSPH_PMASS * kPoly6Kern);
    this->setPressure( (this->getDensity() - kSPH_RESTDENSITY) *  kSPH_INTSTIFF);
    
    if (this->getDensity() != fj::Scalar(0))
    {
        this->inverseItsRho();
    }
    
}

fj::Vector fj::FluidParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticleWeakPtr)
{
    const std::shared_ptr<fj::Particle> neighborParticle = neighborParticleWeakPtr.lock();
    
    // 近傍粒子が突然消えていたらバグ
    assert( !neighborParticleWeakPtr.expired() );
    
    if ( this->getPosition() == neighborParticle->getPosition()) {
        return fj::Vector(0, 0, 0);
    }
 
    return neighborParticle->affect( std::cref(*this) );
}

fj::Vector fj::FluidParticle::affect(const fj::Particle &particle)const
{
    // 藤代研究室0Bの上田さんのコードをもとにして実装されています
    
    constexpr fj::Scalar kH = fj::SimulationConstant::SIM_H;
    constexpr fj::Scalar kSPH_VISCOSITY = fj::SimulationConstant::SPH_VISCOSITY;
    constexpr fj::Scalar kSPH_SIMSCALE = fj::SimulationConstant::SPH_SIMSCALE;
    
    const fj::Scalar kSpikyKernel = fj::SimulationConstant::SpikyKernel;
    const fj::Scalar kLaplacianKernel = fj::SimulationConstant::LaplacianKernel;
    
    const fj::FluidParticle& kNeighborParticle = std::cref(*this);
    
    const fj::Vector kRelativePosition = (particle.getPosition() - kNeighborParticle.getPosition()) * kSPH_SIMSCALE;
    const fj::Scalar kDistance = kRelativePosition.norm();
    
    const fj::Scalar kC = kH - kDistance;
    
    const fj::Scalar kPressureTerm = -0.5 * kC * kSpikyKernel * (particle.getPressure() + kNeighborParticle.getPressure()) / kDistance;
    const fj::Scalar kVelocityTerm = kLaplacianKernel * kSPH_VISCOSITY;
    
    fj::Vector fcurr = kRelativePosition * kPressureTerm + (kNeighborParticle.getVelocity() - particle.getVelocity()) * kVelocityTerm;
    fcurr *= kC * particle.getDensity() * kNeighborParticle.getDensity();
    
    return fcurr;
}

fj::Vector fj::FluidParticle::computeForceFromObject(const fj::Vector& collisionPoint)const
{
    return fj::Vector(0, 0, 0);
}
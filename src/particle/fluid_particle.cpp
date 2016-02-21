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
#include <ParticleSystem/type/Scalar.h>
#include <ParticleSystem/particle/fluid_particle.hpp>

void fj::FluidParticle::updateProperty()
{
    const fj::Scalar kSquaredEffectRange = getSquaredEffectRange();
    fj::Scalar sum(0);
    
    for (const std::weak_ptr<fj::Particle>& neighborParticleWeakPtr : *getNeighborParticlesPtr())
    {
        const std::shared_ptr<fj::Particle>& neighborParticle = neighborParticleWeakPtr.lock();
        
        // 近傍粒子が突然消えていたらバグ
        assert( !neighborParticleWeakPtr.expired() );
        
        const fj::Scalar kSquaredDistance = (this->getPosition() - neighborParticle->getPosition()).squaredNorm();
        const fj::Scalar kC = kSquaredEffectRange - kSquaredDistance;
        
        sum += std::pow(kC, 3);
    }
    
    this->setRho(sum);
    this->setPressure(this->getRho());
    this->inverseItsRho();
    
//    p_p.rho = sum * SPH_PMASS * Poly6Kern;
//    p_p.prs = ( p_p.rho - SPH_RESTDENSITY ) * SPH_INTSTIFF;
//    p_p.rho = 1.0 / p_p.rho;
}

fj::Vector fj::FluidParticle::affectedBy(const std::weak_ptr<fj::Particle> &neighborParticleWeakPtr)
{
    const fj::Scalar kEffectRange = getEffectRange();
    const std::shared_ptr<fj::Particle> neighborParticle = neighborParticleWeakPtr.lock();
    
    // 近傍粒子が突然消えていたらバグ
    assert( !neighborParticleWeakPtr.expired() );
    
    if ( this->getPosition() == neighborParticle->getPosition()) {
        return fj::Vector(0, 0, 0);
    }
    
    const fj::Vector kRelativePosition = this->getPosition() - neighborParticle->getPosition();
    const fj::Scalar kDistance = kRelativePosition.norm();
    
    if (kEffectRange < kDistance)
    {
        return fj::Vector(0, 0, 0);
    }
    
//    pterm = -0.5 * c * SpikyKern * (p_p.prs + p_pj->prs) / r;
//    vterm = LapKern * SPH_VISC;
//    fcurr = dr * pterm + (p_pj->vel - p_p.vel) * vterm;
//    fcurr *= c * p_p.rho * p_pj->rho;
//    force += fcurr;
    
    
    return fj::Vector(0, 0, 0);
}

fj::Vector fj::FluidParticle::affect(const fj::Particle &particle)const
{
    return fj::Vector(0, 0, 0);
}

fj::Vector fj::FluidParticle::computeForceFromObject(const fj::Vector& collisionPoint)const
{
    return fj::Vector(0, 0, 0);
}
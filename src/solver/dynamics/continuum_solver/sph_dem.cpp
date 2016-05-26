//
//  sph_dem.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/24.
//
//

#include <cmath>

#include <ParticleSystem/solver/dynamics/continuum_solver/sph_method.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_dem.hpp>
#include <ParticleSystem/particle/particle_id.h>

fj::Scalar fj::SPHDEM::computeSpikyScalarValue(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::ParticleID& kID = sphInfo.TargetParticle.getID();
    const fj::Scalar kSmoothedPressure = Super::computeSpikyScalarValue(sphInfo);
    
    m_smoothedPressure[kID] = kSmoothedPressure;
    
    return kSmoothedPressure;
}

//fj::Vector3 fj::SPHDEM::computeVelocityTerm(const fj::SPHMethod::SPHInformation &sphInfo)const
//{
//    const fj::Vector3 kForce = Super::computeVelocityTerm(sphInfo);
//
//    const fj::Particle& kTargetParticle = sphInfo.TargetParticle;
//    const fj::Particle& kNeighborParticle = sphInfo.NeighborParticle;
//    const fj::Scalar& kPressure = sphInfo.Property.getPressure();
//    const fj::Vector3 kFrictionDirection = -kTargetParticle.getVelocity().normalized();
//    
//    const fj::Vector3 kRelativeVelocity = (-kTargetParticle.getVelocity() - kNeighborParticle.getVelocity());
//    
////    return kForce;
//    if ( kRelativeVelocity.isZero() )
//    {
//        return kForce;//fj::Vector3(0, 0, 0);
//    }
//    
//    // 摩擦方向の速度
//    const fj::Vector3 kFForce = getFrictionCoefficient() * (-kTargetParticle.getVelocity()).dot(kNeighborParticle.getVelocity())* LaplacianKernel * kFrictionDirection;
//
//    
//    return kForce + kFForce;
//}

fj::Vector3 fj::SPHDEM::computeExtraTerm(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::Particle& kTargetParticle = sphInfo.TargetParticle;
    const fj::Particle& kNeighborParticle = sphInfo.NeighborParticle;
    const fj::Scalar& kPressure = sphInfo.Property.getPressure();
    const fj::Vector3 kFrictionDirection = -kTargetParticle.getVelocity().normalized();
    
    const fj::Vector3 kRelativeVelocity = (-kTargetParticle.getVelocity() - kNeighborParticle.getVelocity());
    
//    if ( kRelativeVelocity.isZero() )
    {
        return fj::Vector3(0, 0, 0);
    }
    
    // 摩擦方向の速度
    const fj::Vector3 kForce = std::abs(kPressure) * getFrictionCoefficient() * (-kTargetParticle.getVelocity()).dot(kNeighborParticle.getVelocity())* LaplacianKernel * kFrictionDirection;;
    return kForce;
}

void fj::SPHDEM::computeFrictionCoefficient()
{
    m_frictionCoefficient = std::sqrt( fj::Scalar(2) / fj::Scalar(3) ) * std::sin( getAngleOfRepose() );
}
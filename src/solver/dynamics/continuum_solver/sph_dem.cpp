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

fj::Vector3 fj::SPHDEM::computeExtraTerm(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const fj::Particle& kTargetParticle = sphInfo.TargetParticle;
    const fj::Particle& kNeighborParticle = sphInfo.NeighborParticle;
    
    // 摩擦方向の速度
    (-kTargetParticle.getVelocity()).dot(kNeighborParticle.getVelocity());
    
    return fj::Vector3(0, 0, 0);
}

void fj::SPHDEM::computeFrictionCoefficient()
{
    m_frictionCoefficient = std::sqrt(2/3) * std::sin( getAngleOfRepose() );
}
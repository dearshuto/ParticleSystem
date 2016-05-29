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
    const fj::Scalar kSmoothedPressure = std::min(fj::Scalar(0), Super::computePressureScalar(sphInfo));
    
    m_smoothedPressure[kID] = kSmoothedPressure;
    
    return kSmoothedPressure;
}

void fj::SPHDEM::computeFrictionCoefficient()
{
    m_frictionCoefficient = std::sqrt( fj::Scalar(2) / fj::Scalar(3) ) * std::sin( getAngleOfRepose() );
}

fj::Scalar fj::SPHDEM::getViscosity(const fj::ParticleID &ID)const
{
    const fj::Scalar kFrictinParameter = m_smoothedPressure.at(ID) * getFrictionCoefficient();
    return std::max(fj::Scalar(Super::getViscosity(ID)), std::min(kFrictinParameter, fj::Scalar(200)));
}
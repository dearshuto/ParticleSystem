//
//  sph_dem.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/24.
//
//

#include <algorithm>
#include <cmath>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_method.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_dem.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>

void fj::SPHDEM::allocateMemory(const fj::ParticleManager &particleManager)
{
    Super::allocateMemory(particleManager);
    
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const Particle& kParticle = iterator->next();
        
        m_smoothedPressure[ kParticle.getID() ] = fj::Scalar(0);
    }
}

void fj::SPHDEM::executeDynamics(const fj::Scalar &timestep, fj::ParticleSystem *particleSystem)
{
    Super::executeDynamics(timestep, particleSystem);
    addVanderWaalsForce(particleSystem->getParticleManager(), particleSystem->getNeighborMap());
}

void fj::SPHDEM::addVanderWaalsForce(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    // 静電気力は距離の2乗にに反比例する力として表現する
    // 近傍に引っ張られる力をすべて足し合わせる
    
    auto iterator = particleManager.iterator();
    fj::Vector3 force{0, 0, 0};
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const auto& kNeighbors = neighborMap.getAt(kID);
        
        for (const auto& neighbor : kNeighbors)
        {
            const fj::Vector3& kDirection = neighbor.getDirection();
            const fj::Scalar& kDistance = neighbor.getDistance();
            
            force += (-kDirection) / std::pow(kDistance, fj::Scalar(2.0));
        }
        
        addAccelAt(kID, PARTICLE_MASS * force);
        force = fj::Vector3(0, 0, 0);
    }
}

fj::Scalar fj::SPHDEM::computeSpikyScalarValue(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::ParticleID& kID = sphInfo.TargetParticle.getID();
    const fj::Scalar kSmoothedPressure = std::min(fj::Scalar(0), Super::computePressureScalar(sphInfo));
    
    m_smoothedPressure[kID] = kSmoothedPressure;
    
    return kSmoothedPressure;
}

fj::Vector3 fj::SPHDEM::computeLaplacianVector(const fj::SPHMethod::SPHInformation &sphInfo)
{
    return Super::computeViscosity(sphInfo);
}

void fj::SPHDEM::computeFrictionCoefficient()
{
    m_frictionCoefficient = std::sqrt( fj::Scalar(2) / fj::Scalar(3) ) * std::sin( getAngleOfRepose() );
}

fj::Scalar fj::SPHDEM::getViscosity(const fj::ParticleID &ID)const
{
    // 圧力に比例するように粘性を変化させる. 0~200でclampしておく.
    const fj::Scalar kFrictinParameter = m_smoothedPressure.at(ID) * getFrictionCoefficient();
        
    return std::max(fj::Scalar(Super::getViscosity(ID)), kFrictinParameter);
}
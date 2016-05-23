//
//  sph_method.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#define _USE_MATH_DEFINES
#include <math.h> //for using M_PI
#include <cmath>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_method.hpp>

const fj::Scalar fj::SPHMethod::Poly6Kernel = fj::Scalar(315) / ( fj::Scalar(64) * M_PI * std::pow( H, fj::Scalar(9) ));
const fj::Scalar fj::SPHMethod::SpikyKernel = fj::Scalar(-45) / ( fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));
const fj::Scalar fj::SPHMethod::LaplacianKernel = fj::Scalar(45) / (fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));

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
    )
    : TargetParticle(targetParticle)
    , Property(property)
    , NeighborParticle(neighbor)
    , NeighborProperty(neighborProperty)
    , NeighborInformation( neighborInfo )
    {
        
    }
    
public:
    const fj::Particle& TargetParticle;
    const SPHProperty& Property;
    const fj::Particle& NeighborParticle;
    const SPHProperty& NeighborProperty;
    const fj::NeighborMap::NeighborInformation& NeighborInformation;
};

void fj::SPHMethod::executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particlesystem)
{
    const fj::ParticleManager& kParticleManager = particlesystem->getParticleManager();
    const fj::NeighborMap& kNeighborMap = particlesystem->getNeighborMap();
    
    updateProperty(kParticleManager, kNeighborMap);
    updateAccel(kParticleManager, kNeighborMap);
}

void fj::SPHMethod::updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap)
{
    
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const ParticleID& kID = kParticle.getID();
        
        m_propertyMap[kID] = std::move( computePropertyAt(kParticle, neighborMap) );
    }
    
}

std::unique_ptr<fj::SPHMethod::SPHProperty> fj::SPHMethod::computePropertyAt(const fj::Particle &particle, const fj::NeighborMap &neighborMap)
{
    // 自分自身の重みで初期化しておく
    fj::Scalar sum = std::pow(SQUARED_H, 3);
    
    const fj::ParticleID& kID = particle.getID();
    const auto& kNeighbors = neighborMap.getAt(kID);
    
    for (const auto& kNeighborParticle : kNeighbors)
    {
        const fj::Vector3 kRelativePosition = kNeighborParticle.getDirection();
        const fj::Scalar kSquaredDistance = kNeighborParticle.getSquaredDistance();
        const fj::Scalar kC = SQUARED_H - kSquaredDistance;
        
        sum += std::pow(kC, 3);
    }

    return std::unique_ptr<SPHProperty>(new SPHProperty( sum * PARTICLE_MASS * Poly6Kernel ));
}

void fj::SPHMethod::updateAccel(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap)
{
    fj::Vector3 F(0, 0, 0);
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        
        const fj::ParticleID& kID = kParticle.getID();
        const SPHMethod::SPHProperty& kParticleProperty = std::cref(*m_propertyMap.at(kID));
        
        for (const auto& neighbor : neighborMap.getAt(kID))
        {
            const fj::Particle& kNeighborParticle = particleManager.search(neighbor.getParticleID());
            const fj::SPHMethod::SPHProperty& kNeighborProperty = std::cref( *m_propertyMap.at(kNeighborParticle.getID()) );
            
            const SPHInformation kSPHInfo( kParticle
                                          ,kParticleProperty
                                          ,kNeighborParticle
                                          ,kNeighborProperty
                                          ,neighbor);

            F += computeForce(kSPHInfo);
        }
        
        addAccelAt(kID, F * kParticleProperty.getInverseDensity());
        F = fj::Vector3(0, 0, 0);
    }
}

fj::Vector3 fj::SPHMethod::computeForce(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const fj::NeighborMap::NeighborInformation& kNeighborInfo = sphInfo.NeighborInformation;
    const SPHProperty& kNeighborProperty = sphInfo.NeighborProperty;
    const fj::Scalar& kDistance = kNeighborInfo.getDistance();
    const fj::Scalar kC = H - kDistance;
    const fj::Vector3 kKernelTerm = computeKernelTerm(sphInfo);
    
    return PARTICLE_MASS * kNeighborProperty.getInverseDensity() * kC * kKernelTerm;
}

fj::Vector3 fj::SPHMethod::computeKernelTerm(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const fj::Vector3 kVelocityKernelTerm = computeVelocityTerm(sphInfo);
    const fj::Vector3 kPressureKernelterm = computePressureTerm(sphInfo);
    const fj::Vector3 kExtraTerm = computeExtraTerm(sphInfo);
    
    return kVelocityKernelTerm + kPressureKernelterm + kExtraTerm;
}

fj::Vector3 fj::SPHMethod::computePressureTerm(const fj::SPHMethod::SPHInformation& sphInfo)const
{
    const SPHProperty& kProperty= sphInfo.Property;
    const SPHProperty& kNeighborProperty = sphInfo.NeighborProperty;
    const fj::Vector3& kDirection = sphInfo.NeighborInformation.getDirection();
    const fj::Scalar& kDistance = sphInfo.NeighborInformation.getDistance();
    const fj::Scalar kC = H - kDistance;
    
    return -fj::Scalar(0.5 * (kProperty.getPressure() + kNeighborProperty.getPressure()) * SpikyKernel * kC) * kDirection;
}

fj::Vector3 fj::SPHMethod::computeVelocityTerm(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const fj::Particle& kTargetParticle = sphInfo.TargetParticle;
    const fj::Particle& kNeighborParticle = sphInfo.NeighborParticle;
    const fj::ParticleID& kID = kTargetParticle.getID();
    
    return getViscosity(kID) * (kNeighborParticle.getVelocity() - kTargetParticle.getVelocity()) * LaplacianKernel;
}

fj::Vector3 fj::SPHMethod::computeExtraTerm(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    return fj::Vector3(0, 0, 0);
}

fj::Scalar fj::SPHMethod::calculateScalar(const fj::ParticleID &ID)const
{
    return (m_propertyMap.at(ID))->getDensity();
}
//
//  sph_method.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#define _USE_MATH_DEFINES
#include <math.h> //for using M_PI
#include <algorithm>
#include <cmath>
#include <thread>
#include <vector>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/dynamics/continuum_solver/sph_method.hpp>

const fj::Scalar fj::SPHMethod::Poly6Kernel = fj::Scalar(315) / ( fj::Scalar(64) * M_PI * std::pow( H, fj::Scalar(9) ));
const fj::Scalar fj::SPHMethod::SpikyKernel = fj::Scalar(-45) / ( fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));
const fj::Scalar fj::SPHMethod::LaplacianKernel = fj::Scalar(45) / (fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));

void fj::SPHMethod::allocateMemory(const fj::ParticleManager &particleManager)
{
    Super::allocateMemory(particleManager);
    
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const Particle& kParticle = iterator->next();
        
        m_propertyMap[ kParticle.getID() ] = nullptr;
    }
}

void fj::SPHMethod::freeContinuumMemoryAt(const fj::ParticleID &ID)
{
    m_propertyMap.erase(ID);
}

void fj::SPHMethod::executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particlesystem)
{
    const fj::ParticleManager& kParticleManager = particlesystem->getParticleManager();
    const fj::NeighborMap& kNeighborMap = particlesystem->getNeighborMap();
    
    updateProperty(kParticleManager, kNeighborMap);
    updateAccel(kParticleManager, kNeighborMap);
}

void fj::SPHMethod::updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap)
{
    if (getThreadNum() > 1)
    {
        updateProperty_MT(particleManager, neighborMap);
    }
    else
    {
        updateProperty_ST(particleManager, neighborMap);
    }
}

void fj::SPHMethod::updateProperty_ST(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const ParticleID& kID = kParticle.getID();
        
        m_propertyMap[kID] = std::move( computePropertyAt(kParticle, neighborMap) );
    }
    
}

void fj::SPHMethod::updateProperty_MT(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    const int kParticleNum = particleManager.getRegisteredParticleNum();
    const int kPartition = kParticleNum / getThreadNum();
    int min = 0;
    std::vector<std::thread> threadVector;
    
    for (int i = 0; i < getThreadNum(); i++)
    {
        const unsigned int kMax = std::min(min + kPartition, kParticleNum);
        const unsigned int kMin = min;
        
        threadVector.emplace_back(&fj::SPHMethod::updatePropertyIn, this, std::cref(particleManager), std::cref(neighborMap), kMin, kMax);
        
        min = kMax;
    }

    for (auto& thread : threadVector)
    {
        thread.join();
    }
}

void fj::SPHMethod::updatePropertyIn(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap, const unsigned int min, const unsigned int max)
{
    for (unsigned int i = min; i < max; i++)
    {
        const fj::Particle& kParticle = particleManager[i];
        const fj::ParticleID& kID = kParticle.getID();
        
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
            const fj::Scalar kWeight = H - neighbor.getDistance();
            
            const SPHInformation kSPHInfo( kParticle
                                          ,kParticleProperty
                                          ,kNeighborParticle
                                          ,kNeighborProperty
                                          ,neighbor
                                          ,kWeight);

            F += computeForce(kSPHInfo);
        }
        
        addAccelAt(kID, F * kParticleProperty.getInverseDensity());
        F = fj::Vector3(0, 0, 0);
    }
}

fj::Vector3 fj::SPHMethod::computeForce(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::Vector3 kPressureKernelterm = computeSpikyKernelTerm(sphInfo);
    const fj::Vector3 kVelocityKernelTerm = computeLaplacianKernelTerm(sphInfo);
    const fj::Vector3 kExtraTerm = computeExtraTerm(sphInfo);
    
    const fj::Vector3 kKernelTerm = kVelocityKernelTerm + kPressureKernelterm + kExtraTerm;
    const SPHProperty& kNeighborProperty = sphInfo.NeighborProperty;
    
    return PARTICLE_MASS * kNeighborProperty.getInverseDensity() * kKernelTerm;
}

fj::Vector3 fj::SPHMethod::computeSpikyKernelTerm(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::Vector3& kDirection = sphInfo.NeighborInformation.getDirection();
    const fj::Scalar& kC = sphInfo.Weight;
    const fj::Scalar kValue = computeSpikyScalarValue(sphInfo);
    
    return kValue * kC * kC * SpikyKernel * kDirection;
}

fj::Vector3 fj::SPHMethod::computeLaplacianKernelTerm(const fj::SPHMethod::SPHInformation &sphInfo)
{
    const fj::Vector3 kViscosityVector = computeLaplacianVector(sphInfo);
    const fj::Scalar& kC = sphInfo.Weight;
    
    return kViscosityVector * kC * LaplacianKernel;
}

fj::Scalar fj::SPHMethod::computeSpikyScalarValue(const fj::SPHMethod::SPHInformation &sphInfo)
{
    return computePressureScalar(sphInfo);
}

fj::Scalar fj::SPHMethod::computePressureScalar(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const SPHProperty& kProperty= sphInfo.Property;
    const SPHProperty& kNeighborProperty = sphInfo.NeighborProperty;
    
    return -0.5 * (kProperty.getPressure() + kNeighborProperty.getPressure());
}

fj::Vector3 fj::SPHMethod::computeLaplacianVector(const fj::SPHMethod::SPHInformation &sphInfo)
{
    return computeViscosity(sphInfo);
}

fj::Vector3 fj::SPHMethod::computeViscosity(const fj::SPHMethod::SPHInformation &sphInfo)const
{
    const fj::Particle& kTargetParticle = sphInfo.TargetParticle;
    const fj::Particle& kNeighborParticle = sphInfo.NeighborParticle;
    const fj::ParticleID& kID = kTargetParticle.getID();
    
    return getViscosity(kID) * (kNeighborParticle.getVelocity() - kTargetParticle.getVelocity());
}

fj::Vector3 fj::SPHMethod::computeExtraTerm(const fj::SPHMethod::SPHInformation &sphInfo)
{
    return fj::Vector3(0, 0, 0);
}

fj::Scalar fj::SPHMethod::calculateScalar(const fj::ParticleID &ID)const
{
    return (m_propertyMap.at(ID))->getDensity();
}
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

            const fj::Vector3 kDirection = neighbor.getDirection();
            const fj::Scalar kDistance = neighbor.getDistance();

            const fj::Scalar kC = H - kDistance;
            const fj::Vector3 kVelocityKernelTerm = getViscosity(kID) * (kNeighborParticle.getVelocity() - kParticle.getVelocity()) * LaplacianKernel;
            const fj::Vector3 kPressureKernelterm = -fj::Scalar(0.5 * (kParticleProperty.getPressure() + kNeighborProperty.getPressure()) * SpikyKernel * kC) * kDirection;
            const fj::Vector3 kKernelTerm = kVelocityKernelTerm + kPressureKernelterm;

            F += PARTICLE_MASS * kNeighborProperty.getInverseDensity() * kC * kKernelTerm;
        }
        
        addAccelAt(kID, F * kParticleProperty.getInverseDensity());
        F = fj::Vector3(0, 0, 0);

    }
}

fj::Scalar fj::SPHMethod::calculateScalar(const fj::ParticleID &ID)const
{
    return (m_propertyMap.at(ID))->getDensity();
}
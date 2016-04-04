//
//  sph_method.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle_manager/neighbor_map.hpp>
#include <ParticleSystem/particle_manager/particle_manager.hpp>
#include <ParticleSystem/solver/sph_method.hpp>

const fj::Scalar fj::SPHMethod::Poly6Kernel = fj::Scalar(315) / ( fj::Scalar(64) * M_PI * std::pow( H, fj::Scalar(9) ));
const fj::Scalar fj::SPHMethod::SpikyKernel = fj::Scalar(-45) / ( fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));
const fj::Scalar fj::SPHMethod::LaplacianKernel = fj::Scalar(45) / (fj::Scalar(M_PI) * std::pow( H, fj::Scalar(6) ));

void fj::SPHMethod::compute(const fj::ParticleManager &particleManager, const fj::NeighborMap &neighborMap)
{
    updateProperty(particleManager, neighborMap);
    updateAccel(particleManager, neighborMap);
}

void fj::SPHMethod::updateProperty(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap)
{
    
    for (const auto& particle : particleManager)
    {
        const ParticleID& kID = particle->getID();
        
        m_propertyMap[kID] = std::move( computePropertyAt(*particle, neighborMap) );
    }

}

std::unique_ptr<fj::SPHMethod::SPHProperty> fj::SPHMethod::computePropertyAt(const fj::Particle &particle, const fj::NeighborMap &neighborMap)
{
    const fj::ParticleID& kID = particle.getID();
    const auto& kNeighbors = neighborMap.getAt(kID);
    
    // 自分自身の重みで初期化しておく
    fj::Scalar sum = std::pow(SQUARED_H, 3);
    
    for (const auto& kNeighborParticle : kNeighbors)
    {
        const fj::Vector3 kRelativePosition = kNeighborParticle.getDirection();
        const fj::Scalar kSquaredDistance = kNeighborParticle.getSquaredDistance();
        const fj::Scalar kC = SQUARED_H - kSquaredDistance;
        
        sum += std::pow(kC, 3);
    }
    
    const fj::Scalar kDensity = sum * PARTICLE_MASS * Poly6Kernel;
    return std::unique_ptr<SPHProperty>(new SPHProperty(kDensity));
}

void fj::SPHMethod::updateAccel(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap)
{
    // 藤代研究室0Bの上田さんのコードをもとにして実装されています
    fj::Vector3 F(0, 0, 0);
    
    for (const auto& particle : particleManager)
    {
        const fj::ParticleID& kID = particle->getID();
        const SPHMethod::SPHProperty& kParticleProperty = std::cref(*m_propertyMap.at(kID));
        
        for (const auto& neighbor : neighborMap.getAt(kID))
        {
            const fj::Particle& kNeighborParticle = particleManager.search(neighbor.getParticleID());
            const fj::SPHMethod::SPHProperty& kNeighborProperty = std::cref( *m_propertyMap.at(kNeighborParticle.getID()) );
            
            const fj::Vector3 kDirection = neighbor.getDirection();
            const fj::Scalar kDistance = neighbor.getDistance();
            
            const fj::Scalar kC = H - kDistance;
            const fj::Vector3 kVelocityKernelTerm = VISCOSITY * (kNeighborParticle.getVelocity() - particle->getVelocity()) * LaplacianKernel;
            const fj::Vector3 kPressureKernelterm = -fj::Scalar(0.5 * (kParticleProperty.getPressure() + kNeighborProperty.getPressure()) * SpikyKernel * kC) * kDirection;
            const fj::Vector3 kKernelTerm = kVelocityKernelTerm + kPressureKernelterm;
            
            F += PARTICLE_MASS * kNeighborProperty.getInverseDensity() * kC * kKernelTerm;
        }

        setAccelAt(kID, F * kParticleProperty.getInverseDensity());
        F = fj::Vector3(0, 0, 0);
    }
}
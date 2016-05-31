//
//  mc_bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#include <cassert>
#include <numeric>

#include <ParticleSystem/particle_system.hpp>
#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/solver/dynamics/dynamics.hpp>
#include <ParticleSystem/solver/bb_algorithm/mc_bounding_box.hpp>

void fj::MCBoundingBox::execute(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem)
{
    clearScalarMap(particleSystem->getParticleManager());
    updateScalarMap(particleSystem->getParticleManager(), particleSystem->getDynamics());
}

void fj::MCBoundingBox::clearScalarMap(const fj::ParticleManager& particleManager)
{

    for (const auto& ID : getInBoxParticle())
    {
        const fj::Particle& kParticle = particleManager.search(ID);
        const int kIndex = convertIndex(kParticle.getPosition());
        
        assert(0 <= kIndex);
        
        resetNDInterpolateValue(kIndex, 3);
    }

}

void fj::MCBoundingBox::updateScalarMap(const fj::ParticleManager &particleManager, const fj::Dynamics& dynamics)
{
    auto iterator = particleManager.iterator();
    
    while (iterator->hasNext())
    {
        const fj::Particle& kParticle = iterator->next();
        const fj::ParticleID& kID = kParticle.getID();
        const int kIndex = convertIndex(kParticle.getPosition());
        const fj::Scalar kScalar = dynamics.calculateScalar(kID);
        
        setNDInterpolateValue(kIndex, 1, kScalar);
    }
    
}

void fj::MCBoundingBox::setNDInterpolateValue(const int index, const int n, const fj::Scalar& scalar)
{
    // 影響範囲 "H = 0.01"と仮定する
    constexpr fj::Scalar H = 0.01;
    const fj::Scalar kDivisionSizeX = getDivisionsSizeX();
    const fj::Scalar kDivisionSizeY = getDivisionsSizeY();
    const fj::Scalar kDivisionSizeZ = getDivisionsSizeZ();
    
    for (int x = -n; x <= n; x++){
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                const fj::Scalar kSquaredDistance = std::pow((x * kDivisionSizeX), 2) + std::pow((y * kDivisionSizeY), 2) + std::pow((z * kDivisionSizeZ), 2);
                const fj::Scalar kWeight = 1.0 - std::sqrt(kSquaredDistance) / H;
                const int kIndex = getShiftedIndex(index, x, y, z);
                
                if (0 <= kIndex)
                {
                    assert(std::isfinite(kSquaredDistance));
                    
                    if (kSquaredDistance < H*H)
                    {
                        addScalar(kIndex, scalar * kWeight);
                    }
                    
                }
                
            }
        }
    }
    
}

void fj::MCBoundingBox::resetNDInterpolateValue(const int index, const int n)
{
    
    for (int x = -n; x <= n; x++){
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                const int kIndex = getShiftedIndex(index, x, y, z);
                
                if (0 <= kIndex)
                {
                    setScalar(kIndex, 0);
                }
                
            }
        }
    }
    
}

fj::Scalar fj::MCBoundingBox::getScalar(const int x, const int y, const int z)const
{
    return get(x, y, z);
}

void fj::MCBoundingBox::setScalar(const int x, const int y, const int z, const fj::Scalar &scalar)
{
    set(x, y, z, scalar);
}

void fj::MCBoundingBox::setScalar(const int index, const fj::Scalar &scalar)
{
    set(index, scalar);
}

void fj::MCBoundingBox::addScalar(const int x, const int y, const int z, const fj::Scalar &scalar)
{
    add(x, y, z, scalar);
}

void fj::MCBoundingBox::addScalar(const int index, const float &t)
{
    add(index, t);
}

int fj::MCBoundingBox::getShiftedIndex(const int kIndex, const int x, const int y, const int z)const
{
    const int kShiftedIndex = kIndex + convertIndex(x, y, z);
    
    if ((0 <= kShiftedIndex) && (kShiftedIndex < size()) ) {
        return kShiftedIndex;
    }
    
    return -1;
}
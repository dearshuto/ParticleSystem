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
#include <ParticleSystem/bb_algorithm/mc_bounding_box.hpp>

void fj::MCBoundingBox::execute(fj::ParticleSystem* particleSystem)
{
    Super::execute(particleSystem);
    
    clearScalarMap(particleSystem->getParticleManager());
    updateScalarMap(particleSystem->getParticleManager(), particleSystem->getSolver());
}

void fj::MCBoundingBox::clearScalarMap(const fj::ParticleManager& particleManager)
{

    for (const auto& ID : getInBoxParticle())
    {
        const fj::Particle& kParticle = particleManager.search(ID);
        const int kIndex = convertPositionToIndex(kParticle.getPosition());
        
        assert(0 <= kIndex);
        
        resetNDInterpolateValue(kIndex, 3);
    }

}

void fj::MCBoundingBox::updateScalarMap(const fj::ParticleManager &particleManager, const fj::Solver &solver)
{
    
    for (const auto& ID : getInBoxParticle())
    {
        const fj::Particle& kParticle = particleManager.search(ID);
        const int kIndex = convertPositionToIndex(kParticle.getPosition());
        const fj::Scalar kScalar = solver.calculateScalar(ID);
        
        setNDInterpolateValue(kIndex, 3, kScalar);
    }
    
}

void fj::MCBoundingBox::setNDInterpolateValue(const int index, const int n, const fj::Scalar& scalar)
{
    // 影響範囲 "H = 0.01"と仮定する
    constexpr fj::Scalar H = 0.01;
    const fj::Scalar kDivisionSizeX = getRangeX().getDivisionSize();
    const fj::Scalar kDivisionSizeY = getRangeY().getDivisionSize();
    const fj::Scalar kDivisionSizeZ = getRangeZ().getDivisionSize();
    
    const int kX = H / kDivisionSizeX;
    const int kY = H / kDivisionSizeY;
    const int kZ = H / kDivisionSizeZ;

    
    for (int x = -kX; x <= kX; x++){
        for (int y = -kY; y <= kY; y++) {
            for (int z = -kZ; z <= kZ; z++) {
                const fj::Scalar kSquaredDistance = std::pow((x * kDivisionSizeX), 2) + std::pow((y * kDivisionSizeY), 2) + std::pow((z * kDivisionSizeZ), 2);
                const fj::Scalar kWeight = 1.0 - std::sqrt(kSquaredDistance) / H;
                fj::Scalar* scalarPtr = getShiftedScalar(index, x, y, z);
                
                if (scalarPtr) {
                    
                    assert(std::isfinite(kSquaredDistance));
                    
                    if (kSquaredDistance < H*H) {
                        *scalarPtr += scalar * kWeight;
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
                fj::Scalar* scalarPtr = getShiftedScalar(index, x, y, z);
                
                if (scalarPtr) {
                    *scalarPtr = 0;
                }
                
            }
        }
    }
    
}


fj::Scalar fj::MCBoundingBox::getScalar(const int x, const int y, const int z)const
{
    const int kIndex = convertPositionToIndex(x, y, z);

    return m_scalarMap[kIndex];
}

void fj::MCBoundingBox::setScalar(const int x, const int y, const int z, const fj::Scalar &scalar)
{
    const int kIndex = convertPositionToIndex(x, y, z);
    
    m_scalarMap[kIndex] = scalar;
}

void fj::MCBoundingBox::setScalar(const int index, const fj::Scalar &scalar)
{
    m_scalarMap[index] = scalar;
}


void fj::MCBoundingBox::addScalar(const int x, const int y, const int z, const fj::Scalar &scalar)
{
    const int kIndex = convertPositionToIndex(x, y, z);
    
    m_scalarMap[kIndex] += scalar;
}

void fj::MCBoundingBox::addScalar(const int index, const fj::Scalar& scalar)
{
    assert(index < m_scalarMap.size());
    
    m_scalarMap[index] += scalar;
}

fj::Scalar* fj::MCBoundingBox::getShiftedScalar(const int kIndex, const int x, const int y, const int z)
{
    const int kShiftedIndex = kIndex + convertPositionToIndex(x, y, z);

    if ((0 <= kShiftedIndex) && (kShiftedIndex < m_scalarMap.size()) ) {
        return &m_scalarMap[kShiftedIndex];
    }
    
    return nullptr;
}
//
//  mc_bounding_box.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

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
        
        resetNDInterpolateValue(kIndex, 15);
//        setScalar(kIndex, 0);
    }

}

void fj::MCBoundingBox::updateScalarMap(const fj::ParticleManager &particleManager, const fj::Solver &solver)
{
    
    for (const auto& ID : getInBoxParticle())
    {
        const fj::Particle& kParticle = particleManager.search(ID);
        const int kIndex = convertPositionToIndex(kParticle.getPosition());
        const fj::Scalar kScalar = solver.calculateScalar(ID);
        
        setNDInterpolateValue(kIndex, 15, kScalar);
    }
    
}

void fj::MCBoundingBox::setScalarValue(const int i, const int j, const int k, const fj::Solver &solver)
{
    fj::Scalar scalar = 0;
    
    for ( const auto& ID : Super::get(i, j, k))
    {
        scalar += solver.calculateScalar(ID);
    }
//    setScalar(i, j, k, scalar);
    setInterpolateValue(i, j, k, scalar);
}

void fj::MCBoundingBox::setInterpolateValue(const int i, const int j, const int k, const fj::Scalar &scalar)
{
//    setNDInterpolateValue(i, j, k, scalar, 5);
}

void fj::MCBoundingBox::setNDInterpolateValue(const int index, const int n, const fj::Scalar& scalar)
{
    
    for (int x = -n; x <= n; x++){
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                fj::Scalar* scalarPtr = getShiftedScalar(index, x, y, z);
                
                if (scalarPtr) {
                    const int kWeight = std::abs(x) + std::abs(y) + std::abs(z);
                    
                    if (kWeight == 0)
                    {
                        *scalarPtr += scalar;
                    }
                    else
                    {
                        *scalarPtr += scalar * float(1.0 / kWeight);
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
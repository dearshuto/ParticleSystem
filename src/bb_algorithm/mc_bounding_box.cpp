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
    
    clearScalarMap();
    updateScalarMap(particleSystem->getParticleManager(), particleSystem->getSolver());
}

void fj::MCBoundingBox::clearScalarMap()
{
    
    for (auto& scalar : m_scalarMap)
    {
        scalar = fj::Scalar(0);
    }
    
}

void fj::MCBoundingBox::updateScalarMap(const fj::ParticleManager &particleManager, const fj::Solver &solver)
{
    
    for (int i = 0; i < getRangeX().getResolusion(); i++) {
        for (int j = 0; j < getRangeY().getResolusion(); j++) {
            for (int k = 0; k < getRangeZ().getResolusion(); k++) {
                
                setScalarValue(i, j, k, solver);
                
            }
        }
    }
    
}

void fj::MCBoundingBox::setScalarValue(const int i, const int j, const int k, const fj::Solver &solver)
{
    fj::Scalar scalar = 0;
    
    for ( const auto& ID : Super::get(i, j, k))
    {
        scalar += solver.calculateScalar(ID);
    }
    
    setInterpolateValue(i, j, k, scalar);
}

void fj::MCBoundingBox::setInterpolateValue(const int i, const int j, const int k, const fj::Scalar &scalar)
{
    const fj::Scalar kHalfValue = scalar / fj::Scalar(2);
    
    for (int x = -1; x < 2; x++){
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                const int kX = i + x;
                const int kY = j + y;
                const int kZ = k + z;
                
                if ( !isOutOfRange(kX, kY, kZ) ) {
                    addScalar(kX, kY, kZ, kHalfValue);
                }
                
            }
        }
    }
    
    addScalar(i, j, k, kHalfValue);
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

void fj::MCBoundingBox::addScalar(const int x, const int y, const int z, const fj::Scalar &scalar)
{
    const int kIndex = convertPositionToIndex(x, y, z);
    
    m_scalarMap[kIndex] += scalar;
}
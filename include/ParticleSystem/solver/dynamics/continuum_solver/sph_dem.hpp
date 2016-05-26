//
//  sph_dem.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/24.
//
//

#ifndef sph_dem_hpp
#define sph_dem_hpp

#include <functional>
#include <unordered_map>

#include <FUJIMath/type/scalar.h>

#include "sph_method.hpp"

namespace fj {
    class ParticleID;
    class SPHDEM;
}

class fj::SPHDEM : public fj::SPHMethod
{
    typedef fj::SPHMethod Super;
public:
    SPHDEM()
    : m_angleOfRepose( fj::Scalar(30) )
    {
        computeFrictionCoefficient();
    }
    
    ~SPHDEM() = default;
    
    SPHDEM(const fj::SPHDEM& other) = delete;
    SPHDEM& operator=(const fj::SPHDEM& other) = delete;

    fj::Scalar computeSpikyScalarValue(const fj::SPHMethod::SPHInformation& sphInfo)override;
    
    fj::Vector3 computeExtraTerm(const fj::SPHMethod::SPHInformation& sphInfo)override;
    
private:
    
    void computeFrictionCoefficient();
    
public:
    const fj::Scalar& getAngleOfRepose()const
    {
        return std::cref(m_angleOfRepose);
    }
    
    void setAngleOfRange(const fj::Scalar& angleOfRepose)
    {
        m_angleOfRepose = angleOfRepose;
        computeFrictionCoefficient();
    }
    
    const fj::Scalar& getFrictionCoefficient()const
    {
        return std::cref(m_frictionCoefficient);
    }
    
private:
    
    /**
     * 安息角
     */
    fj::Scalar m_angleOfRepose;
    
    /**
     * 摩擦係数
     */
    fj::Scalar m_frictionCoefficient;
    
    std::unordered_map<fj::ParticleID, int> m_smoothedPressure;
};

#endif /* sph_dem_hpp */

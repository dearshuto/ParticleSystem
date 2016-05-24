//
//  sph_dem.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/24.
//
//

#ifndef sph_dem_hpp
#define sph_dem_hpp

#include "sph_method.hpp"

namespace fj {
    class SPHDEM;
}

class fj::SPHDEM : public fj::SPHMethod
{
public:
    SPHDEM() = default;
    ~SPHDEM() = default;
    
    SPHDEM(const fj::SPHDEM& other) = delete;
    SPHDEM& operator=(const fj::SPHDEM& other) = delete;
    
    fj::Vector3 computeVelocityTerm(const fj::SPHMethod::SPHInformation& sphInfo)const override
    {
        return fj::Vector3(0, 0, 0);
    }
};

#endif /* sph_dem_hpp */

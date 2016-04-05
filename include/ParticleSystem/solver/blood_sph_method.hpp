//
//  blood_sph_method.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/05.
//
//

#ifndef BloodSPHMethod_hpp
#define BloodSPHMethod_hpp

#include "sph_method.hpp"

namespace fj {
    class BloodSPHMethod;
}

class fj::BloodSPHMethod : public SPHMethod
{
public:
    BloodSPHMethod() = default;
    ~BloodSPHMethod() = default;
    
    const fj::Scalar getViscosity()const override
    {
        return 1.0;
    }

};

#endif /* BloodSPHMethod_hpp */

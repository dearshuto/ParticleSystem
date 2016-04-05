//
//  blood_sph_method.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/05.
//
//

#ifndef BloodSPHMethod_hpp
#define BloodSPHMethod_hpp

#include <unordered_map>
#include "sph_method.hpp"

namespace fj {
    class ParticleManager;
    class ParticleMap;
    class BloodSPHMethod;
}

class fj::BloodSPHMethod : public fj::SPHMethod
{
    typedef fj::SPHMethod Super;
public:
    BloodSPHMethod() = default;
    ~BloodSPHMethod() = default;
    
    void compute(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap) override;
    
    fj::Scalar getViscosity(const fj::ParticleID& ID)const override
    {
        return 1;//m_viscosityMap.at(ID);
    }

private:
    void updateViscosityMap(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    
private:
    std::unordered_map<fj::ParticleID, fj::Scalar> m_viscosityMap;
};

#endif /* BloodSPHMethod_hpp */

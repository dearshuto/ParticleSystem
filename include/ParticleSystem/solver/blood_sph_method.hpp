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

/**
 * 粘性が時間変化する液体の解法
 */
class fj::BloodSPHMethod : public fj::SPHMethod
{
    typedef fj::SPHMethod Super;
public:
    BloodSPHMethod() = default;
    ~BloodSPHMethod() = default;
    
    /**
     * 時間変化する情報のシミュレーション
     */
    void compute(const fj::Scalar& timestep, const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap) override;

    
    fj::Scalar getViscosity(const fj::ParticleID& ID)const override
    {
        return m_viscosityMap.at(ID);
    }
    
    void updateViscosityMap(const fj::Scalar& timestep, const fj::ParticleManager& particleManager);
    
private:
    /**
     * 時間変化する粘性
     */
    std::unordered_map<fj::ParticleID, fj::Scalar> m_viscosityMap;
};

#endif /* BloodSPHMethod_hpp */

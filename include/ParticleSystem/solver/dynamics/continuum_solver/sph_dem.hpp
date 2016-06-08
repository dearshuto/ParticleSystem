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
    : m_angleOfRepose( fj::Scalar(20) )
    {
        computeFrictionCoefficient();
    }
    
    ~SPHDEM() = default;
    
    SPHDEM(const fj::SPHDEM& other) = delete;
    SPHDEM& operator=(const fj::SPHDEM& other) = delete;

    void executeDynamics(const fj::Scalar& timestep, fj::ParticleSystem* particleSystem) override;
    
    void allocateMemory(const fj::ParticleManager& particleManager)override;
private:
    
    /**
     * ファンデルワールス力による今日着力を計算する
     */
    void addVanderWaalsForce(const fj::ParticleManager& particleManager, const fj::NeighborMap& neighborMap);
    
    /**
     * 摩擦力の計算には圧力が必要なので、計算結果を一時的に保存しておくためにオーバーライドする.
     * Spikyカーネルで平滑化する対象は圧力だけなのはSPH法と変わらない.
     */
    fj::Scalar computeSpikyScalarValue(const fj::SPHMethod::SPHInformation& sphInfo)override;
    
    /**
     *
     */
    fj::Vector3 computeLaplacianVector(const fj::SPHMethod::SPHInformation& sphInfo)override;
private:
    
    /**
     * 現在設定されている安息角から摩擦係数を算出する
     */
    void computeFrictionCoefficient();

    /**
     * Viscosityを変化させることで、内部摩擦を表現する
     */
    fj::Scalar getViscosity(const fj::ParticleID& ID)const override;

public:
    const fj::Scalar& getAngleOfRepose()const
    {
        return std::cref(m_angleOfRepose);
    }

    void setAngleOfRange(const fj::Scalar& angleOfRepose)
    {
        m_angleOfRepose = 3.14 * angleOfRepose / 180.0;
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
    
    /**
     * 粒子にかかっている圧力
     */
    std::unordered_map<fj::ParticleID, fj::Scalar> m_smoothedPressure;
};

#endif /* sph_dem_hpp */

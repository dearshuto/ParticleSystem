//
//  simulation_constant.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/07.
//
//

#ifndef simulation_constant_hpp
#define simulation_constant_hpp

#define NOMINMAX
#include <cmath>
#include <FUJIMath/type/scalar.h>

namespace fj {
    class SimulationConstant;
}

class fj::SimulationConstant
{
private:
    SimulationConstant() = default;
public:
    ~SimulationConstant() = default;


    constexpr static const fj::Scalar RESTDENSITY = 600;//[kg/m^3] 水の密度
    constexpr static const fj::Scalar PARTICLE_RADIUS = 0.005;//[m]
    constexpr static const fj::Scalar PARTICLE_VOLUME = (4 / 3) * M_PI * PARTICLE_RADIUS * PARTICLE_RADIUS * PARTICLE_RADIUS;//[m^3]
    constexpr static const fj::Scalar PARTICLE_MASS = RESTDENSITY * PARTICLE_VOLUME;//[kg]
    constexpr static const fj::Scalar H = 0.01;//m
    constexpr static const fj::Scalar SQUARED_H = H * H;

    constexpr static const fj::Scalar SPH_SIGMA = 300;
    constexpr static const fj::Scalar SPH_INTSTIFF = 3.0f;
    constexpr static const fj::Scalar SPH_VISCOSITY = 0.8;

    static const int CONGEAL_START = 2000000;
    static const int CONGEAL_FINISH = 8000000;
    constexpr static const fj::Scalar CONGEALED_VISCOSITY = 10000000000;
    static const int CLOSE_WOUND = 600000;

    constexpr static const fj::Scalar D_VISCOSITY = 30;
    static const int D_TIMESTEP = 100;

    constexpr static fj::Scalar DIS_PLUS_AT = 0.4f;

    static const fj::Scalar Poly6Kernel;
    static const fj::Scalar SpikyKernel;
    static const fj::Scalar LaplacianKernel;
};

namespace fj {
    enum class SimulationFlag
    {
        col_n = 1
        ,SURFACE = 2
        ,SUB_SURFACE = 4
        ,DISSOLUTION = 8
        ,MASSIVE = 16
        ,NULL_FLAG = 32
        ,ADSORBED = 64
        ,FIRST_ZERO = 128//�I������������
    };
}

#endif /* simulation_constant_hpp */

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
    
    constexpr static const fj::Scalar H = 0.01;
    constexpr static const fj::Scalar G_SCALE = 3;
    constexpr static const fj::Scalar SPH_LIMIT = 200.0;
    constexpr static const fj::Scalar SPH_PMASS = 0.00020543;
    constexpr static const fj::Scalar SPH_RADIUS = 0.004;
    constexpr static const fj::Scalar SPH_SIGMA = 300;
    constexpr static const fj::Scalar SPH_SIMSCALE = 0.004;
    constexpr static const fj::Scalar SPH_RESTDENSITY = 600.0f;
    constexpr static const fj::Scalar SPH_INTSTIFF = 3.0f;
    constexpr static const fj::Scalar SIM_H = H / SPH_SIMSCALE;
    constexpr static const fj::Scalar SPH_VISCOSITY = 1.0;
    
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

namespace mlk {
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
//
//  simulation_constant.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/02/07.
//
//

#ifndef simulation_constant_hpp
#define simulation_constant_hpp

#include <cmath>

namespace mlk {
    class SimulationConstant;
}

class mlk::SimulationConstant
{
private:
    SimulationConstant() = default;
public:
    ~SimulationConstant() = default;
    
    constexpr static const double H = 0.01;
    constexpr static const double G_SCALE = 3;
    constexpr static const double SPH_LIMIT = 200.0;
    constexpr static const double SPH_PMASS = 0.00020543;
    constexpr static const double SPH_RADIUS = 0.004;
    constexpr static const double SPH_SIGMA = 300;
    constexpr static const double SPH_SIMSCALE = 0.004;
    constexpr static const double SPH_RESTDENSITY = 600.0f;
    constexpr static const double SPH_INTSTIFF = 3.0f;
    constexpr static const double SIM_H = H / SPH_SIMSCALE;
    constexpr static const double SPH_VISCOSITY = 1.0;
    
    static const int CONGEAL_START = 2000000;
    static const int CONGEAL_FINISH = 8000000;
    constexpr static const float CONGEALED_VISCOSITY = 10000000000.f;
    static const int CLOSE_WOUND = 600000;
    
    constexpr static const float D_VISCOSITY = 30;
    static const int D_TIMESTEP = 100;
    
    constexpr static float DIS_PLUS_AT = 0.4f;
    
    static double Poly6Kernel()
    {
        return -315.0 / (64.0 * M_PI * std::pow(H, 9));
    }
    
    static double SpikyKernel()
    {
        return -45.0 / (M_PI * std::pow(H, 6));
    }
    
    static double LaplacianKernel()
    {
        return 45.0 / (M_PI * std::pow(H, 6));
    }
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

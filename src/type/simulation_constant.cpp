//
//  simulation_constant.cpp
//  blood-simulation
//
//  Created by Shuto Shikama on 2016/02/07.
//
//

#include <ParticleSystem/type/simulation_constant.hpp>

const fj::Scalar fj::SimulationConstant::Poly6Kernel = fj::Scalar(315) / ( fj::Scalar(64) * M_PI * std::pow( fj::SimulationConstant::H, fj::Scalar(9) ));

const fj::Scalar fj::SimulationConstant::SpikyKernel = fj::Scalar(-45) / ( fj::Scalar(M_PI) * std::pow( fj::SimulationConstant::H, fj::Scalar(6) ));

const fj::Scalar fj::SimulationConstant::LaplacianKernel = fj::Scalar(45) / (fj::Scalar(M_PI) * std::pow( fj::SimulationConstant::H, fj::Scalar(6) ));
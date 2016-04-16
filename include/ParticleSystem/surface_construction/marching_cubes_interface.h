//
//  marching_cubes_interface.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef marching_cubes_interface_h
#define marching_cubes_interface_h

namespace fj {
    class Solver;
    class MarchingCubesInterface;
}

class fj::MarchingCubesInterface
{
public:
    virtual ~MarchingCubesInterface() = default;
    
    virtual fj::Scalar getScalar(const int x, const int y, const int z)const = 0;
};

#endif /* marching_cubes_interface_h */

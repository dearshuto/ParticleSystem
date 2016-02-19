//
//  particle.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <ParticleSystem/type/Scalar.h>

namespace fj {
    class Particle;
}

class fj::Particle
{
public:
    Particle() = default;
    virtual~Particle() = default;
};

#endif /* particle_hpp */

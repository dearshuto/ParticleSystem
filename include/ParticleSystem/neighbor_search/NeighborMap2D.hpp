//
//  NeighborMap2D.hpp
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/18.
//
//

#ifndef NeighborMap2D_hpp
#define NeighborMap2D_hpp

#include <memory>

namespace fj {
    class Particle;
    class NeighborMap2D;
}

class fj::NeighborMap2D{
    NeighborMap2D() = default;
    ~NeighborMap2D() = default;
    
    void registerParticle(const std::shared_ptr<fj::Particle> particle);
    void removeParticle(const std::shared_ptr<fj::Particle> particle);
};

#endif /* NeighborMap2D_hpp */

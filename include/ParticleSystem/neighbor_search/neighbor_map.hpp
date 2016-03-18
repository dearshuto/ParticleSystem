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
#include <vector>

namespace fj {
    class Particle;
    template<constexpr int W, constexpr int H, constexpr int D = 1> class NeighborMap;
}

template<constexpr int W, constexpr int H, constexpr int D>
class fj::NeighborMap
{
public:
    NeighborMap() = default;
    ~NeighborMap() = default;
    
    NeighborMap(const int width, const int height)
    {
        
    }
    
    void update();
    void registerParticle(const std::shared_ptr<fj::Particle> particle);
    void removeParticle(const std::shared_ptr<fj::Particle> particle);
    
private:
    std::array<int, W * H> a;
};

#include <ParticleSystem/neighbor_search/neighbor_map_impl.hpp>

#endif /* NeighborMap2D_hpp */

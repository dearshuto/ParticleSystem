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
    class Position;
    
    template<constexpr int W, constexpr int H, constexpr int D> class NeighborMap;
}

template<constexpr int W, constexpr int H, constexpr int D = 1>
class fj::NeighborMap
{
    typedef int HashValue;
    typedef std::vector<fj::Particle> ParticleContainer;
    typedef std::array< ParticleContainer, W * H * D> HashMap;
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
    HashValue computeHashValueFromPosition(const fj::Position& position)const;
    
private:
    HashMap* getPartisions()
    {
        return &m_partitions;
    }
    
    int getPartitionsWidth()const
    {
        return m_partitionsWidth;
    }
    
    int getPartitionsHeight()const
    {
        return m_partitionsHeight;
    }
    
    int getPartitionsDepth()const
    {
        return m_partitionsDepth;
    }
    
// member variables
private:
    HashMap m_partitions;
    
    const int m_partitionsWidth = W;
    const int m_partitionsHeight = H;
    const int m_partitionsDepth = D;
};

#include <ParticleSystem/neighbor_search/neighbor_map_impl.hpp>

#endif /* NeighborMap2D_hpp */

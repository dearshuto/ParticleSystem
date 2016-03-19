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
    
    template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D> class NeighborMap;
}

/**
 * 空間分割法を利用した近傍探索マップ
 * テンプレートのデフォルト値を採用することで奥行きの分割数の指定を自由にし, 3次元化を可能にしてある.
 */
template<constexpr unsigned int W, constexpr unsigned int H, constexpr unsigned int D = 1>
class fj::NeighborMap
{
    typedef unsigned int HashValue;
    
    /**
     * 粒子の再登録は毎フレーム行わないが, 逐次アクセスは毎フレーム行う. 
     * よって可変長で連続したメモリにデータを確保していて高速アクセスが可能なstd::vectorを利用する.
     */
    typedef std::vector< std::shared_ptr<fj::Particle> > ParticleContainer;

    /**
     * シミュレーションの途中で分割数は変化しないので, 固定長であるがもっとも高速なstd::arrayを利用する.
     */
    typedef std::array< ParticleContainer, W * H * D> HashMap;
public:
    NeighborMap() = delete;
    ~NeighborMap() = default;
    
    NeighborMap(const unsigned int blockSize)
    : m_blockSize(blockSize)
    {
        
    }
    
    void update();
    
    /**
     * 粒子を新規に登録する.
     */
    void registerParticle(const std::shared_ptr<fj::Particle> particle);

private:
    HashValue computeHashValueFromPosition(const fj::Position& position)const;

    
private:
    
    ParticleContainer* getContainerPtr(const HashValue hash)
    {
        return &(getPartisions()[hash]);
    }
    
    HashMap* getPartisions()
    {
        return &m_partitions;
    }
    
    unsigned int getPartitionsWidth()const
    {
        return m_partitionsWidth;
    }
    
    unsigned int getPartitionsHeight()const
    {
        return m_partitionsHeight;
    }
    
    unsigned int getPartitionsDepth()const
    {
        return m_partitionsDepth;
    }
    
// member variables
private:
    HashMap m_partitions;
    
    const unsigned int m_partitionsWidth = W;
    const unsigned int m_partitionsHeight = H;
    const unsigned int m_partitionsDepth = D;
    const unsigned int m_blockSize;
};

#include <ParticleSystem/neighbor_search/neighbor_map_impl.hpp>

#endif /* NeighborMap2D_hpp */

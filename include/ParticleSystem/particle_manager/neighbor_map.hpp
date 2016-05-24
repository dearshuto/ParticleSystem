//
//  neighbor_map.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef neighbor_map_hpp
#define neighbor_map_hpp

#include <cassert>
#include <iostream>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleManager;
    class NeighborMap;
}

/**
 * 近傍の情報の監視役
 */
class fj::NeighborMap
{
public:
    class NeighborInformation;
private:
    typedef std::vector<NeighborInformation> NeighborInformations;
public:
    NeighborMap() = default;
    ~NeighborMap() = default;
    
    
    /**
     * 衝突判定対象となる粒子を登録する
     */
    void registerParticle(const fj::ParticleID& particle);
    
    /**
     * 影響範囲に入った粒子と距離情報を追加する. 引数の順番に注意!
     * @param ID 注目粒子
     * @param neighborID 注目粒子の近傍に入ってきた粒子
     */
    void addNeighborInformation(const fj::ParticleID& particle, const fj::ParticleID& neighborParticle, const fj::ParticleManager& particleManager);
    
    /**
     * 影響範囲に入った粒子と距離情報を追加する. 引数の順番に注意!
     * @param ID 注目粒子
     * @param neighborID 注目粒子の近傍に入ってきた粒子
     */
    void addNeighborInformation(const fj::ParticleID& particle, const fj::ParticleID& neighborParticle, const fj::Scalar& distance, const fj::ParticleManager& particleManager);

    /**
     * マップ内の情報を初期化する. 登録されている登録されている粒子自体が消去されるわけではない.
     */
    void clear();
    
    const NeighborInformations& getAt(const fj::ParticleID& ID)const
    {
        assert(m_neighbors.find(ID) != std::end(m_neighbors));
        return std::cref( m_neighbors.at(ID) );
    }
    
private:
    std::unordered_map<fj::ParticleID, NeighborInformations> m_neighbors;
};

class fj::NeighborMap::NeighborInformation
{
public:
    NeighborInformation() = delete;
    ~NeighborInformation() = default;
    
    NeighborInformation(const fj::ParticleID& ID, const fj::Vector3& direction, const fj::Scalar& kSquaredDistance, const fj::Scalar& distance)
    : m_ID( ID.getData() )
    , m_direction(direction)
    , m_squaredDistance(kSquaredDistance)
    , m_distance(distance)
    {
        
    }
    
    const fj::ParticleID& getParticleID()const
    {
        return m_ID;
    }
    
    const fj::Vector3& getDirection()const
    {
        return m_direction;
    }
    
    const fj::Scalar& getSquaredDistance()const
    {
        return m_squaredDistance;
    }
    
    const fj::Scalar& getDistance()const
    {
        return m_distance;
    }
    
private:
    const fj::ParticleID m_ID;
    
    /**
     * このインスタンスが保持するIDをもつ粒子から向ってくる方向
     */
    const fj::Vector3 m_direction;
    
    const fj::Scalar m_squaredDistance;
    
    const fj::Scalar m_distance;
};

#endif /* neighbor_map_hpp */

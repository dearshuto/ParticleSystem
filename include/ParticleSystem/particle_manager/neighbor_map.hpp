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
#include <functional>
#include <unordered_map>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle_id.h>
#include <ParticleSystem/solver/solver.hpp>

namespace fj {
    class Particle;
    class ParticleID;
    class ParticleManager;
    class NeighborMap;
}

/**
 * 近傍の情報の管理役
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
    
    NeighborMap(const fj::NeighborMap& other) = delete;
    NeighborMap& operator=(const fj::NeighborMap& other) = delete;
    
    /**
     * 粒子の数だけマップ領域を確保する.
     */
    void allocateMemory(const fj::ParticleManager& particleManager);
    
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
    
    /**
     * 指定した粒子の近傍情報を取得する
     */
    const NeighborInformations& getAt(const fj::ParticleID& ID)const
    {
        assert(m_neighbors.find(ID) != std::end(m_neighbors));
        return std::cref( m_neighbors.at(ID) );
    }
    
    void freeMemoryAt(const fj::ParticleID& ID);
private:
    std::unordered_map<fj::ParticleID, NeighborInformations> m_neighbors;
};

/**
 * ある粒子に注目したときに, この粒子に影響を与える近傍粒子の情報.
 */
class fj::NeighborMap::NeighborInformation
{
public:
    NeighborInformation() = delete;
    ~NeighborInformation() = default;
    
    /**
     * @param targetParticleID 注目している粒子
     * @param ID 近傍粒子のID
     * @param direction 近傍粒子から注目している粒子に向かうベクトル
     */
    NeighborInformation(const fj::ParticleID& targetParticleID, const fj::ParticleID& ID, const fj::Vector3& direction, const fj::Scalar& kSquaredDistance, const fj::Scalar& distance)
    : m_targetParticleID( targetParticleID.getData() )
    , m_ID( ID.getData() )
    , m_direction(direction)
    , m_squaredDistance(kSquaredDistance)
    , m_distance(distance)
    {
        
    }
    
    NeighborInformation(const NeighborInformation& other) = default;
    NeighborInformation& operator=(const NeighborInformation& other) = delete;
    
    const fj::ParticleID& getTargetParticleID()const
    {
        return m_targetParticleID;
    }
    
    const fj::ParticleID& getParticleID()const
    {
        return m_ID;
    }
    
    /**
     * 近傍から自分へと向かうベクトル
     */
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
    
    /**
     * 注目する粒子のID
     */
    const fj::ParticleID m_targetParticleID;
    
    /**
     * 注目粒子の近傍粒子のID
     */
    const fj::ParticleID m_ID;
    
    /**
     * このインスタンスが保持するIDをもつ粒子から向ってくる方向
     */
    const fj::Vector3 m_direction;
    
    const fj::Scalar m_squaredDistance;
    
    const fj::Scalar m_distance;
};

#endif /* neighbor_map_hpp */

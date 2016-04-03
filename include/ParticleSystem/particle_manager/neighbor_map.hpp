//
//  neighbor_map.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/03.
//
//

#ifndef neighbor_map_hpp
#define neighbor_map_hpp

#include <functional>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <FUJIMath/type/scalar.h>
#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/particle/particle.hpp>
#include <ParticleSystem/particle/particle_id.h>

namespace fj {
    class Particle;
    class ParticleID;
    class NeighborMap;
}

/**
 * 近傍の情報の監視役
 */
class fj::NeighborMap
{
    class NeighborInformation;
public:
    typedef std::vector<NeighborInformation> NeighborInformations;
public:
    NeighborMap() = default;
    ~NeighborMap() = default;
    
    /**
     * 影響範囲に入った粒子の組合せと距離情報を追加する. 引数となるふたつのIDは順不同.
     */
    void addNeighborInformation(const fj::Particle& ID1, const fj::Particle& ID2);
    
    void clear();
    
    const NeighborInformations& getAt(const fj::ParticleID& ID)const
    {
        return std::cref(m_neighbors.at(ID));
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
    : m_ID(ID)
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

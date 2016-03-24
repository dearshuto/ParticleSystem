//
//  Header.h
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef Header_h
#define Header_h

#include <unordered_map>

namespace fj {
    class ParticleID;
}

/**
 * int型をラッパしたID
 * IDを利用した処理に任意のint型の数値を入れられないようにする
 */
class fj::ParticleID
{
public:
    ParticleID() = delete;
    ~ParticleID() = default;
    
    ParticleID(const ParticleID& other)
    : m_ID(other.getData())
    {
        
    }
    
    explicit ParticleID(const unsigned int num)
    : m_ID(num)
    {
        
    }
    
    ParticleID& operator=(const ParticleID& other) = delete;
    
    bool operator==(const ParticleID& other)const
    {
        if (this->getData() == other.getData()) {
            return true;
        }
        return false;
    }
    
    bool operator!=(const ParticleID& other)const
    {
        return !this->operator==(other);
    }
    
    unsigned int getData()const
    {
        return m_ID;
    }
    
private:
    const unsigned int m_ID;
};


namespace std {
    template<>
    class hash<fj::ParticleID>
    {
    public:
        size_t operator()(const fj::ParticleID& x) const{
            return hash<int>()(x.getData()) ^ hash<int>()(x.getData());
        }
    };
}


#endif /* Header_h */
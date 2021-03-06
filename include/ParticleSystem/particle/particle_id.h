//
//  Header.h
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef Header_h
#define Header_h

#include <functional>
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
    ParticleID()
    : m_ID(0)
    {
    }
    
    ~ParticleID() = default;
    
    explicit ParticleID(const ParticleID& other)
    : m_ID(other.getData())
    {
        
    }
    
    ParticleID(fj::ParticleID&& other) = default;
    
    explicit ParticleID(const unsigned int num)
    : m_ID(num)
    {
        
    }
    
    ParticleID& operator=(const ParticleID& other)
    {
        m_ID = other.getData();
        return *this;
    }

    
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
    
    bool operator<(const fj::ParticleID& other)const
    {
        return (this->getData() < other.getData());
    }
    
    unsigned int getData()const
    {
        return m_ID;
    }
    
private:
    unsigned int m_ID;
};


namespace std {
    template<>
    struct hash<fj::ParticleID>
    {
    public:
        size_t operator()(const fj::ParticleID& x) const{
            // IDをそのままハッシュ値として利用する
            return hash<int>()(x.getData());
        }
    };
}


#endif /* Header_h */

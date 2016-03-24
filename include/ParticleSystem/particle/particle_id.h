//
//  Header.h
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/03/24.
//
//

#ifndef Header_h
#define Header_h

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
    
    ParticleID(const ParticleID& other) = delete;
    
    ParticleID(const unsigned int num)
    : m_ID(num)
    {
        
    }
    
    ParticleID& operator=(const ParticleID& other) = delete;
    
    bool operator==(const ParticleID& other)
    {
        if (this->getData() == other.getData()) {
            return true;
        }
        return false;
    }
    
    unsigned int getData()const
    {
        return m_ID;
    }
    
private:
    const unsigned int m_ID;
};


#endif /* Header_h */

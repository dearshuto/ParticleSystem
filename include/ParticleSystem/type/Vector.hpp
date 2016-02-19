//
//  Vector.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#ifndef Vector_hpp
#define Vector_hpp

#include <functional>
#include <ParticleSystem/type/Scalar.h>

namespace fj {
    class Vector;
}

class fj::Vector
{
public:
    Vector()
    : Vector(0, 0, 0)
    {
        
    }
    
    virtual ~Vector() = default;
    
    Vector(const fj::Vector& other)
    : Vector(other.x(), other.y(), other.z())
    {
        
    }
    
    Vector(const fj::Scalar x, const fj::Scalar y, const fj::Scalar z)
    : m_x(x), m_y(y), m_z(z)
    {
    
    }
    
    fj::Vector& operator=(const fj::Vector& other)
    {
        this->x() = other.x();
        this->y() = other.y();
        this->z() = other.z();
        
        return std::ref(*this);
    }
    
    fj::Vector operator+(const fj::Vector& other)const
    {
        const fj::Scalar kX = this->x() + other.x();
        const fj::Scalar kY = this->y() + other.y();
        const fj::Scalar kZ = this->z() + other.z();
        
        return fj::Vector(kX, kY, kZ);
    }
    
    fj::Vector& operator+=(const fj::Vector& other)
    {
        this->x() += other.x();
        this->y() += other.y();
        this->z() += other.z();
        
        return std::ref(*this);
    }
    
    fj::Vector operator-(const fj::Vector& other)const
    {
        const fj::Scalar kX = this->x() - other.x();
        const fj::Scalar kY = this->y() - other.y();
        const fj::Scalar kZ = this->z() - other.z();
        
        return fj::Vector(kX, kY, kZ);
    }

    fj::Vector& operator-=(const fj::Vector& other)
    {
        this->x() -= other.x();
        this->y() -= other.y();
        this->z() -= other.z();
        
        return std::ref(*this);
    }
    
    fj::Vector operator/(const fj::Scalar num)const
    {
        const fj::Scalar kX = this->x() / num;
        const fj::Scalar kY = this->y() / num;
        const fj::Scalar kZ = this->z() / num;
        
        return fj::Vector(kX, kY, kZ);
    }
    
    fj::Vector operator*(const fj::Scalar num)const
    {
        const fj::Scalar kX = this->x() * num;
        const fj::Scalar kY = this->y() * num;
        const fj::Scalar kZ = this->z() * num;
        
        return fj::Vector(kX, kY, kZ);
    }
    
    
    fj::Scalar squaredNorm()const;
    
    fj::Scalar norm()const;
    
    fj::Vector to(const fj::Vector& other)const;
    
    fj::Vector from(const fj::Vector& other)const;
    
// getters & setters
public:
    fj::Scalar& x()
    {
        return m_x;
    }

    fj::Scalar x()const
    {
        return m_x;
    }
    
    fj::Scalar& y()
    {
        return m_y;
    }

    fj::Scalar y()const
    {
        return m_y;
    }
    
    fj::Scalar& z()
    {
        return m_z;
    }

    fj::Scalar z()const
    {
        return m_z;
    }

    
private:
    fj::Scalar m_x;
    fj::Scalar m_y;
    fj::Scalar m_z;
};

fj::Vector operator*(const fj::Scalar num, const fj::Vector& vector);

#endif /* Vector_hpp */

//
//  Vector.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <cmath>

#include <ParticleSystem/type/Scalar.h>
#include <ParticleSystem/type/Vector.hpp>

fj::Scalar fj::Vector::squaredNorm()const
{
    return std::pow(this->x(), 2) + std::pow(this->y(), 2) + std::pow(this->z(), 2);
}

fj::Scalar fj::Vector::norm()const
{
    return std::sqrt( this->squaredNorm() );
}

fj::Vector fj::Vector::to(const fj::Vector &other)const
{
    return other - (*this);
}

fj::Vector fj::Vector::from(const fj::Vector &other)const
{
    return (*this) - other;
}

fj::Vector operator*(const fj::Scalar num, const fj::Vector& vector)
{
    return vector * num;
}
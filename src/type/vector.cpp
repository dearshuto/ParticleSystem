//
//  Vector.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/02/19.
//
//

#include <cmath>
#include <functional>
#include <iostream>

#include <ParticleSystem/type/scalar.h>
#include <ParticleSystem/type/vector.hpp>

fj::Scalar fj::Vector::squaredNorm()const
{
    return std::pow(this->x(), 2) + std::pow(this->y(), 2) + std::pow(this->z(), 2);
}

fj::Scalar fj::Vector::norm()const
{
    return std::sqrt( this->squaredNorm() );
}

void fj::Vector::normalize()
{
    (*this) / this->norm();
}

fj::Vector fj::Vector::normalized()const
{
    fj::Vector ret( std::cref(*this) );
    ret.normalize();
    return ret;
}

fj::Vector fj::Vector::to(const fj::Vector &other)const
{
    return other - (*this);
}

fj::Vector fj::Vector::from(const fj::Vector &other)const
{
    return (*this) - other;
}

void fj::Vector::print()const
{
    std::cout << "(" << this->x() << ", " << this->y() << ", " << this->z() << std::endl;
}

fj::Vector operator*(const fj::Scalar num, const fj::Vector& vector)
{
    return vector * num;
}
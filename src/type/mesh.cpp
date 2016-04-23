//
//  mesh.cpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#include <FUJIMath/type/vector3.hpp>
#include <ParticleSystem/type/mesh.hpp>

void fj::Mesh::addVertex(const fj::Vector3 &position)
{
    m_vertices.push_back(position);
}

void fj::Mesh::addTriangle(unsigned int v1, unsigned int v2, unsigned int v3)
{
    m_triangleIndices.emplace_back(v1, v2, v3);
}

void fj::Mesh::clear()
{
    m_vertices.clear();
    m_triangleIndices.clear();
}
//
//  triangle_mesh.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/15.
//
//

#ifndef triangle_mesh_hpp
#define triangle_mesh_hpp

#include <array>
#include <tuple>
#include <vector>

#include <FUJIMath/type/vector3.hpp>

namespace fj {
    class Triangle;
    class TriangleMesh;
}

class fj::Triangle
{
public:
    Triangle() = default;
    ~Triangle() = default;
    
    std::array<fj::Vector3, 3> m_vertex;
    std::tuple<unsigned int, unsigned int, unsigned int> m_triangleIndex;
};

class fj::TriangleMesh
{
public:
    TriangleMesh() = default;
    ~TriangleMesh() = default;
    
    std::vector<fj::Triangle> m_triangle;
};



#endif /* triangle_mesh_hpp */

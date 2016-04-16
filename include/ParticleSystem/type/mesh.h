//
//  mesh.h
//  ParticleSystem
//
//  Created by Shuto Shikama on 2016/04/16.
//
//

#ifndef mesh_h
#define mesh_h

#include <tuple>
#include <vector>

#include <FUJIMath/type/vector3.hpp>

namespace fj {
    typedef std::vector< std::tuple<unsigned int, unsigned int, unsigned int> > TriangleIndices_t;
    typedef std::vector<fj::Vector3> Vertices_t;
    typedef std::pair<Vertices_t, TriangleIndices_t> Mesh_t;
}
#endif /* mesh_h */

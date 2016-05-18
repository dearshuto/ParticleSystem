//
//  mesh_solver.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/18.
//
//

#ifndef mesh_solver_hpp
#define mesh_solver_hpp

#include <ParticleSystem/solver/solver.hpp>
#include <ParticleSystem/type/mesh.hpp>

namespace fj {
    class MeshSolver;
}

class fj::MeshSolver
{
public:
    virtual~MeshSolver();
    
    virtual bool hasNext();
    virtual fj::Mesh next();
};

#endif /* mesh_solver_hpp */

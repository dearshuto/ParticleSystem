//
//  solver_manager.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/05/22.
//
//

#ifndef solver_manager_hpp
#define solver_manager_hpp

#include <functional>
#include <memory>
#include <vector>

namespace fj {
    class AdditionalSimulation;
    class Dynamics;
    class Mesh;
    class ParticleCollisionDispatcher;
    class Solver;
    class SurfaceConstruction;
    class SolverManager;
}

class fj::SolverManager
{
public:
    SolverManager() = default;
    ~SolverManager() = default;
    
    SolverManager(const fj::SolverManager& other) = delete;
    SolverManager& operator=(const fj::SolverManager& other) = delete;
    
    /**
     * 現在作成されている粒子の分のシミュレーションに必要なメモリを確保する.
     * この関数を呼ばなくてもシミュレーション内のメモリは自動的に確保されるように設計されているが、
     * マルチスレッドで処理をするときにはあらかじめメモリを割り当てておかないと競合がおきてしまう.
     */
    void allocateMomory(const fj::ParticleManager& particleManager);
    
    void allocateMomoryAt(const fj::ParticleID& ID);
    
    /**
     * IDで指定された粒子が削除されたときに呼ばれる関数
     * 削除された粒子分のシミュレーション用メモリを, メンバにもつSolverすべてから削除する
     */
    void freeSimulationMemory(const fj::ParticleID& ID);
    
    void addSolver(std::unique_ptr<fj::Dynamics> dynamics);
    void addSolver(std::unique_ptr<fj::ParticleCollisionDispatcher> collisionDispathcer);
    void addSolver(std::unique_ptr<fj::SurfaceConstruction> surfaceConstruction);
    void addSolver(std::unique_ptr<fj::AdditionalSimulation> additionalSimulation);
    
    std::vector<std::shared_ptr<fj::Solver>>::iterator begin()
    {
        return std::begin(m_solvers);
    }

    std::vector<std::shared_ptr<fj::Solver>>::iterator end()
    {
        return std::end(m_solvers);
    }

private:
    /**
     * 毎フレーム実行するスタックにSolverを保存していく. この関数の中でSplverの優先順序による並替えも行う.
     */
    void stackSolver(std::shared_ptr<fj::Solver> solver);
    
    void removeCurrentDynamics();
    void removeCurrentSurfaceConstruction();
    
public:
    const fj::Dynamics& getDynamics()const
    {
        return std::cref(*m_dynamics);
    }
    
    std::shared_ptr<fj::Dynamics>& getDynamicsPtr()
    {
        return std::ref(m_dynamics);
    }
    
    const fj::Mesh& getMesh(const unsigned int index)const;

    void allocateIsosurface(const fj::Scalar& level);
    
private:
    std::vector<std::shared_ptr<fj::Solver>>& getSolversPtr()
    {
        return std::ref(m_solvers);
    }
    
    std::shared_ptr<fj::SurfaceConstruction>& getSurfaceSolverPtr()
    {
        return std::ref(m_surfaceConstrucsion);
    }

private:
    
    /**
     * 登録されている全てのSolver. ここに格納されているSolverのexecute関数が毎フレーム順番に呼ばれる
     */
    std::vector<std::shared_ptr<fj::Solver>> m_solvers;
    
    /**
     * ひとつしか必要ないDynamicsの管理. m_solverの中に格納されると区別できなくなるので別個に保存しておく.
     */
    std::shared_ptr<fj::Dynamics> m_dynamics;
    
    std::shared_ptr<fj::SurfaceConstruction> m_surfaceConstrucsion;
};

#endif /* solver_manager_hpp */

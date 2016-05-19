//
//  surface_construction.h
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#ifndef surface_construction_h
#define surface_construction_h

#include <memory>

#include <FUJIMath/type/scalar.h>
#include <ParticleSystem/solver/bb_algorithm/bb_algorithm_decorator.hpp>

namespace fj {
    class Mesh;
    class SurfaceConstruction;
}

/**
 * 表面抽出
 */
class fj::SurfaceConstruction : public fj::BBAlgorithmDecorator
{
public:
    SurfaceConstruction() = delete;
    ~SurfaceConstruction() = default;
    
    SurfaceConstruction(std::unique_ptr<fj::BBAlgorithm> bb)
    : BBAlgorithmDecorator( std::move(bb) )
    {
        
    }
    
private:
    void executeBBAlgorithm(fj::ParticleSystem* particleSystem)override;

    
    /**
     * Levelを閾値として内部と外部を定義したメッシュを作成する
     */
    virtual fj::Mesh createMesh(const fj::Scalar& level)const = 0;
};

#endif /* surface_construction_h */

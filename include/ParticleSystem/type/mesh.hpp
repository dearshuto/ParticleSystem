//
//  mesh.hpp
//  ParticleSystem
//
//  Created by Shuto on 2016/04/21.
//
//

#ifndef mesh_hpp
#define mesh_hpp

#include <tuple>
#include <vector>

namespace fj {
    class Vector3;
    class Mesh;
}

/**
 * 三角メッシュ. インデックスは0始まり.
 */
class fj::Mesh
{
public:
    typedef std::vector< std::tuple<unsigned int, unsigned int, unsigned int> > TriangleIndices_t;
    typedef std::vector<fj::Vector3> Vertices_t;
public:
    Mesh() = default;
    ~Mesh() = default;
    
    /**
     * メッシュデータは膨大な容量になるので、コピーは禁止でムーブのみをサポートさせる
     */
    Mesh(const fj::Mesh& other) = delete;
    fj::Mesh& operator=(const fj::Mesh& other) = delete;
    
    Mesh(fj::Mesh&& other)
    {
        *this = std::move(other);
    }
    
    fj::Mesh& operator=(fj::Mesh&& other)
    {
        m_vertices = std::move(other.getVertices());
        m_triangleIndices = std::move(other.getTriangleIndices());
        return std::ref(*this);
    }
    
    /**
     * メッシュ上の頂点を追加する
     */
    void addVertex(const fj::Vector3& position);
    
    /**
     * メッシュに登録されている頂点を参照するインデックスを追加する. インデックスは0始まり.
     */
    void addTriangle(unsigned int v1, unsigned int v2, unsigned int v3);
    
    void clear();
    
public:
    const Vertices_t& getVertices()const
    {
        return m_vertices;
    }
    
    const TriangleIndices_t& getTriangleIndices()const
    {
        return m_triangleIndices;
    }
    
private:
    Vertices_t m_vertices;
    TriangleIndices_t m_triangleIndices;
};

#endif /* mesh_hpp */

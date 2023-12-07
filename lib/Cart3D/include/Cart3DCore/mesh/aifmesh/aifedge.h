#ifndef CART3D_MESH_AIF_EDGE_H
#define CART3D_MESH_AIF_EDGE_H

#include <Cart3DMeshDefine.h>
#include <Util/EigenUtil.h>
#include "aifmesh/aifvertex.h"

namespace Cart3D
{
    class AIFEdge;
    class AIFFace;
    class CART3D_MESH_CLASS AIFEdge
    {
        friend class AIFTopologyHelpers;
    public:
        using self = AIFEdge;
        using ptr = std::shared_ptr< self >;
        using ptr_edge = std::shared_ptr< self >;
        using vertex_type = AIFVertex;
        using face_type = AIFFace;
        using ptr_vertex = std::shared_ptr< vertex_type >;
        using ptr_face = std::shared_ptr< face_type >;
        union VertexContainerType {
            struct { ptr_vertex v0, v1; };
            struct { ptr_vertex vv[2]; };
            VertexContainerType() :v0(nullptr), v1(nullptr) {}
            ~VertexContainerType() {}
        };
        using EdgeContainerType = ct_vector< ptr_edge >;
        using FaceContainerType = ct_vector< ptr_face >;
    public:
        static ptr_edge new_edge();
        static ptr_edge new_edge(const self& other);
    public:
        int degree();
        int get_index() const;
        void set_index(std::size_t idx);
        void set_first_vertex(ptr_vertex V1);
        void set_second_vertex(ptr_vertex V2);
    public:
        bool operator()(const AIFEdge& e1, const AIFEdge& e2)const;
        bool operator<(const self& other) const;
        bool operator==(const self& other) const;
        bool operator!=(const self& other) const;
        bool operator<=(const self& other) const;
        bool operator>=(const self& other) const;
        bool operator>(const self& other) const;
    public:
        ptr_vertex get_first_vertex() const;
        ptr_vertex get_second_vertex() const;
    public:
        FaceContainerType::iterator ef_begin();
        FaceContainerType::iterator ef_end();
        FaceContainerType::const_iterator ef_cbegin()const;
        FaceContainerType::const_iterator ef_cend()const;
    private:
        int m_index;
        VertexContainerType m_ptr_vertices;
        FaceContainerType m_ptr_faces;
    private:
        AIFEdge();
        AIFEdge(const self& other);
    };
}

#endif
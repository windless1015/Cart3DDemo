#ifndef CART3D_MESH_AIF_FACE_H
#define CART3D_MESH_AIF_FACE_H

#include <Cart3DMeshDefine.h>
#include <Util/EigenUtil.h>
#include <aifmesh/aifcell.h>

namespace Cart3D
{
    class AIFVertex;
    class AIFEdge;
    class AIFFace;

    class CART3D_MESH_CLASS AIFFace
    {
        friend class AIFTopologyHelpers;
    public:
        using self = AIFFace;
        using ptr = std::shared_ptr< self >;
        using ptr_face = std::shared_ptr< self >;
        using vertex_type = AIFVertex;
        using edge_type = AIFEdge;
        using ptr_vertex = std::shared_ptr< vertex_type >;
        using ptr_edge = std::shared_ptr< edge_type >;
        using VertexContainerType = ct_vector< ptr_vertex >;
        using EdgeContainerType = ct_vector< ptr_edge >;
        using FaceContainerType = ct_vector< ptr_face >;
    private:
        AIFFace();
        AIFFace(const self& other);
    public:
        static ptr_face new_face();
        static ptr_face new_face(const self& other);
    public:
        int get_index() const;
        void set_index(int idx);
        int degree();
        void clear_vertex_incidency();
    public:
        bool operator<(const self& other) const;
        bool operator==(const self& other) const;
        bool operator!=(const self& other) const;
        bool operator<=(const self& other) const;
        bool operator>=(const self& other) const;
        bool operator>(const self& other) const;
    public:
        EdgeContainerType::iterator fe_begion();
        EdgeContainerType::iterator fe_end();
        EdgeContainerType::const_iterator fe_cbegion()const;
        EdgeContainerType::const_iterator fe_cend()const;
        VertexContainerType::iterator fv_begion();
        VertexContainerType::iterator fv_end();
        VertexContainerType::const_iterator fv_cbegion()const;
        VertexContainerType::const_iterator fv_cend()const;
    private:
        int m_index;
        EdgeContainerType m_ptr_edges;
        VertexContainerType m_ptr_vertices;
        bool m_is_pv_calc;
    };

}

#endif

#ifndef CART3D_MESH_AIF_VERTEX_H
#define CART3D_MESH_AIF_VERTEX_H

#include <Cart3DMeshDefine.h>
#include <Util/EigenUtil.h>
#include <aifmesh/aifcell.h>

namespace Cart3D
{
    class AIFEdge;
    class AIFFace;

    class CART3D_MESH_CLASS AIFVertex
    {
        friend class AIFTopologyHelpers;
    public:
        using ptr = std::shared_ptr<AIFVertex>;
        using ptr_vertex = std::shared_ptr<AIFVertex>;
        using edge_type = AIFEdge;
        using face_type = AIFFace;
        using ptr_edge = std::shared_ptr<edge_type>;
        using ptr_face = std::shared_ptr<face_type>;
        using VertexContainerType = ct_vector<ptr_vertex>;
        using EdgeContainerType = ct_vector<ptr_edge>;
        using FaceContainerType = ct_vector<ptr_face>;
    public:
        static const unsigned int m_d = 3;
        static ptr_vertex new_vertex();
        static ptr_vertex new_vertex(const AIFVertex& other);
    public:
        int get_index() const;
        void set_index(int idx);
        int degree();
    public:
        bool operator<(const AIFVertex& other) const;
        bool operator==(const AIFVertex& other) const;
        bool operator!=(const AIFVertex& other) const;
        bool operator<=(const AIFVertex& other) const;
        bool operator>=(const AIFVertex& other) const;
        bool operator>(const AIFVertex& other) const;
    public:
        VertexContainerType::const_iterator vv_cbegion()const;
        VertexContainerType::const_iterator vv_cend()const;
        EdgeContainerType::const_iterator ve_cbegion()const;
        EdgeContainerType::const_iterator ve_cend()const;
        FaceContainerType::const_iterator vf_cbegion()const;
        FaceContainerType::const_iterator vf_cend()const;
        VertexContainerType::iterator vv_begion();
        VertexContainerType::iterator vv_end();
        EdgeContainerType::iterator ve_begion();
        EdgeContainerType::iterator ve_end();
        FaceContainerType::iterator vf_begion();
        FaceContainerType::iterator vf_end();
    private:
        AIFVertex();
        AIFVertex(const AIFVertex& other);
    private:
        int m_index;
        VertexContainerType m_ptr_vertices;
        EdgeContainerType m_ptr_edges;
        FaceContainerType m_ptr_faces;  
    private:
        bool m_is_face_calc;
        bool m_is_vert_calc;
    };


}


#endif // !CART3D_MESH_AIFVERTEX_H

#ifndef CART3D_CORK_MESH_H
#define CART3D_CORK_MESH_H

#include <Cart3DParallelCorkDefine.h>
#include <csgmesh/CSGMesh.h>
#include <intersection/Intersection3D.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
    struct CorkVertex
    {
        cvector3d pos;     
		cvector3l agency;   
		unsigned short comp; 
        char op;
		CorkVertex();
    };

    struct CorkTri
    {
		bool degenerate;
        cvector3d nor;
		int proj;
		std::uint32_t ref;
		union {
			struct { std::uint32_t  oria, orib, oric; };
			struct { std::uint32_t  ori[3]; };
		};

        union {
            struct { std::uint32_t  a, b, c; };
            struct { std::uint32_t  abc[3]; };
        };
		unsigned short comp;
        char op;
		CorkTri();
    };

    class CorkMesh
    {
		friend class TopoMesh;
    public:
		CorkMesh(const CSGMesh& cmesh,
			ConvertVector3D& cvtool,
			unsigned short comp = 0);
		CorkMesh(const std::vector<cvector3d>& pts, 
			const std::vector<int>& tris,
			ConvertVector3D& cvtool,
			unsigned short comp = 0);
		CorkMesh(const std::vector<cvector3d>& pts,
			const std::vector<cvector3i>& tris,
			ConvertVector3D& cvtool,
			unsigned short comp = 0);
	public:
		//追加cork_mesh
		void append_cork_mesh(const CorkMesh& mesh);
	public:
		//快速合并重合点
		void merge_vertex();
		//标记三角形
		void mark_tris();
	private:
		static void to_vert(
			const std::vector<cvector3d>& pts,
			ct_vector<CorkVertex>& verts,
			const ConvertVector3D& cvt,
			unsigned short comp);
		static void to_tris(const std::vector<cvector3i>& input, 
			ct_vector<CorkTri>& tris, 
			unsigned short comp);
    protected:
		const ConvertVector3D& cvtool; //使用cvtool转化为算术一致性数
        ct_vector<CorkVertex> verts;
        ct_vector<CorkTri> tris;
    };

    class TopoMesh
    {
		friend class CorkMesh;
    public:  
        struct TopoVert
        {
            std::uint32_t ref;
            ct_vector<std::uint32_t> tris;
            ct_vector<std::uint32_t> edge;
			TopoVert() {
				tris.reserve(8);
				edge.reserve(8);
			}
        };
        struct TopoEdge{
			std::uint32_t ref;
            union {
                struct { std::uint32_t va, vb; };
                struct { std::uint64_t ab; };
            };
            ct_vector<std::uint32_t> tris;
			TopoEdge() {
				tris.reserve(2);
			}
        };
        struct TopoTri
        {
            std::uint32_t ref;
			ct_vector<std::uint32_t> edges;

			TopoTri() {
				edges.reserve(3);
			}
        };
	public:
		TopoMesh(CorkMesh& mesh);
	public:

	private:
		void create_topo_slow();
		void create_topo_fast();
    protected:
        CorkMesh& meshdata;
        ct_vector<TopoVert>  topo_verts;
        ct_vector<TopoEdge>  topo_edges;
        ct_vector<TopoTri>  topo_tris;
    };

	

}


#endif
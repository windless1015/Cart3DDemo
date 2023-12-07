#ifndef CART3D_CURVE_FWD_H
#define CART3D_CURVE_FWD_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <Util/BoostUtil.h>
namespace fcpw
{
	template<size_t DIM>
	class Scene;
}

namespace Cart3D
{
	struct CART3D_TOOLS_CLASS SurfPt
	{
		int vid;
		int eid;
		int fid;
		cvector3d coord;
		bool lock;
		SurfPt(int v, int e, int f, const cvector3d& c, bool lock = false);
		SurfPt();
		bool operator==(const SurfPt& rhs) const;
	};

	enum VertexType:unsigned char
	{
		FACE_POINT=0,    //面点  
		VERTEX_POINT=1,  //顶点
		EDGE_POINT=2,    //边点
		UNDEFINR_POINT=3,//未定义点
	};


	struct CART3D_TOOLS_CLASS GeodesicPt
	{
		cvector3d coord;
		int id;
		VertexType type;
		GeodesicPt();

		bool operator==(const GeodesicPt& node) const;
		bool operator!=(const GeodesicPt& node) const;
	};


	enum FaceVTypes
	{
		VTri,
		VEdge,
		VInner,
		VIntersection
	};
	struct CART3D_TOOLS_CLASS FaceVertex
	{
		int vid;
		int tid;
		FaceVTypes type;
		FaceVertex(int vidin, int tidin, FaceVTypes typein) : vid(vidin), tid(tidin), type(typein) {}
	};
	struct CART3D_TOOLS_CLASS InnerSegment
	{
		int fvIdx0;
		int fvIdx1;
		int surfPtIdx;
	};
	struct CART3D_TOOLS_CLASS FaceDivideInfo
	{
		int fid;
		int eids[3];
		ct_vector<int> edgeFVIdxs[3];
		ct_vector<FaceVertex> vids;
		ct_vector<InnerSegment> segments;
		ct_vector<int> dividedSP;
		OpenTriMesh& m_mesh;
		cvector3i ftid;
		cvector2d fuv[3];
		FaceDivideInfo(int f, OpenTriMesh& m_mesh);
		int add_vid(int vid, int eid);
		void add_segment(int idx0, int idx1, int sid);
		void add_segment_from_points(int eid1, int vid1, int eid2, int vid2, int sid);
		void add_divided_surface_point_seg(int surfPtIdx);
	};

}



#endif
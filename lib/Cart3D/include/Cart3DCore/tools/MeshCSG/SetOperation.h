#ifndef CART3D_MESH_BOOLEAN_EXACT_IMPL_H
#define CART3D_MESH_BOOLEAN_EXACT_IMPL_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <Util/TreeUtil.h>
#include <Util/BoostUtil.h>
#include <tbb/tbb.h>
namespace Cart3D
{
	class  Cart3DBvh;
	enum class BooleanType
	{
		UNION,DIFFER,INTERSECTION,DIFFER_OUTER
	};
	/*
	 * @brief 
	 * @see also: libigl,cgal,cork,meshlib
	 * @see paper:exact mesh booleans via efficient&robust local arrangements
	 * @see paper:simple and exact mesh booleans
	 * @param
	 */
	class CART3D_TOOLS_CLASS SetOperation
	{
	public:
		using LinePts = ct_vector<int>;
		struct BoolTriangle;
		struct BoolPointNode;
		struct BoolSegment;
		struct BoolFaceInfo
		{
			VH     avh;
			VH     bvh;
			VH     cvh;
			EH       aeh;
			EH       beh;
			EH       ceh;
			cvector3d n;
			BH       status;
		};
	public:
		SetOperation(OpenTriMesh& src, OpenTriMesh& dst);
		~SetOperation();
	public:
		bool run(BooleanType bt);
	private:
		static void create_bvh(OpenTriMesh& mesh, std::shared_ptr<Cart3DBvh>& pbvh);
	private:
		void add_property();
		void del_property();
		bool tritri_intersect(
			const FH& src,
			const FH& dst,
			ct_vector<BoolPointNode>&     curvepts,
			tree_map<BoolPointNode, int>&    nodemap,
			ct_vector<BoolSegment>&       segments,
			tree_map<BoolSegment, int>&      segmap,
			fast_map<FH, LinePts>&  srcline,
			fast_map<FH, LinePts>&  dstline,
			tree_map<BoolPointNode, BoolPointNode>& overlopmap,
			tbb::spin_mutex& mutex);
		void filter_node(
			ct_vector<BoolPointNode>&             node,
			tree_map<BoolPointNode, BoolPointNode>& overlopmap);
		bool src_seg_triangle(
			const BoolTriangle&              triangle,
			ct_vector<BoolPointNode>&      line,
			cfloat&                          error);
		bool dst_seg_triangle(
			const BoolTriangle&              triangle,
			ct_vector<BoolPointNode>&      line,
			cfloat&                          error);
		int pt_in_triangle(
			const cvector3d&                    seg0,
			const cvector3d&                    p,
			const BoolTriangle&              triangle,
			int&                             index);
		int pt_in_triangle(
			const cvector3d&                    seg0,
			const cvector3d&                    seg1,
			const cvector3d&                    p,
			const BoolTriangle&              triangle,
			int&                             index);
		cfloat seg_seg_dst(
			const cvector3d&                    a0,
			const cvector3d&                    a1,
			const cvector3d&                    b0,
			const cvector3d&                    b1);
		int src_seg_seg(
			const cvector3d&                    p0,
			const cvector3d&                    p1,
			const BoolTriangle&              triangle,
			ct_vector<BoolPointNode>&      line);
		int dst_seg_seg(
			const cvector3d&                    p0,
			const cvector3d&                    p1,
			const BoolTriangle&              triangle,
			ct_vector<BoolPointNode>&      line);
		bool pt_seg(
			const cvector3d&       p,
			const cvector3d&       q0,
			const cvector3d&       q1);
		//
		void poly_to_triangle(
			ct_vector<BoolPointNode>&               curvepts,
			const ct_vector<BoolSegment>&           segments,
			const fast_map<FH, LinePts>&      srcline,
			const fast_map<FH, LinePts>&      dstline,
			const fast_map<FH, BoolFaceInfo>& srcfhinfo,
			const fast_map<FH, BoolFaceInfo>& dstfhinfo,
			fast_map<FH, cvector3d>&             srcnor,
			fast_map<FH, cvector3d>&             dstnor);
		bool src_group_tri(
			ct_vector<BoolPointNode>&               curvepts,
			const ct_vector<BoolSegment>&           segments,
			const BoolFaceInfo&                       fhinfo,
			const LinePts&                            lineinfo,
			ct_vector<cvector3d>&                      polypts,
			ct_vector<int>&                         outerline,
			ct_vector<int>&                         innerline,
			ct_vector<int>&                         markerline,
			ct_vector<int>&                         innerlineid,
			ct_vector<BH>&                  newpointid);
		bool dst_group_tri(
			ct_vector<BoolPointNode>&               curvepts,
			const ct_vector<BoolSegment>&           segments,
			const BoolFaceInfo&                       fhinfo,
			const LinePts&                            lineinfo,
			ct_vector<cvector3d>&                      polypts,
			ct_vector<int>&                         outerline,
			ct_vector<int>&                         innerline,
			ct_vector<int>&                         markerline,
			ct_vector<int>&                         innerlineid,
			ct_vector<BH>&                  newpointid);
		void update_polyline(
			const ct_vector<ct_vector<int>>&      triedgeindex,
			ct_vector<int>&                         innerline,
			ct_vector<int>&                         innerid,
			ct_vector<int>&                         markline);
		bool src_deg_edge(
			const ct_vector<VH>& vhs,
			const ct_vector<EH>&   ehs,
			const BoolPointNode&             node0,
			const BoolPointNode&             node1,
			int&                             status);
		bool dst_deg_edge(
			const ct_vector<VH>& vhs,
			const ct_vector<EH>&   ehs,
			const BoolPointNode&             node0,
			const BoolPointNode&             node1,
			int&                             status);
		void use_triangle(
			const ct_vector<cvector3d>& pts,
			const ct_vector<int>&    outerline,
			const ct_vector<int>&    innerline,
			const cvector3d&              nor,
			ct_vector<int>&          triindex);
		bool zone_triangle(
			fast_map<FH, cvector3d>& srcmapnors,
			fast_map<FH, cvector3d>& dstmapnors);
		void pre_edge_line_src(fast_map<FH, cvector3d>& mapnors);
		void pre_edge_line_dst(fast_map<FH, cvector3d>& mapnors);
		void union_triangle();
		void intersect_triangle();
		void differ_triangle();
		void differ_triangle_outer();
		bool upper_trangle(
			const cvector3d& a,
			const cvector3d& nor,
			const cvector3d& p);
		bool lower_triangle(
			const cvector3d& a,
			const cvector3d& nor,
			const cvector3d& p);
		void adjust_line(
			OpenTriMesh& mesh,
			const ct_vector<EH>& line,
			ct_vector<ct_vector<HH>>& closedline,
			ct_vector<ct_vector<HH>>& openline);
	private:
		SetOperation(const SetOperation&) = delete;
		SetOperation &operator=(const SetOperation &) = delete;
		//
		inline int add_index() { return m_nodeclock++; }
	private:
		OpenMesh::VPropHandleT<cvector3d> m_srcvprop;
		OpenMesh::VPropHandleT<cvector3d> m_dstvprop;
		OpenMesh::VPropHandleT<BH> m_srcmapindex;
		OpenMesh::VPropHandleT<BH> m_dstmapindex;
		OpenMesh::FPropHandleT<BH> m_srcfprop;
		OpenMesh::FPropHandleT<BH> m_dstfprop;
		OpenMesh::FPropHandleT<BH> m_srcboolprop;
		OpenMesh::FPropHandleT<BH> m_dstboolprop;
		OpenMesh::EPropHandleT<BH> m_srccurve;
		OpenMesh::EPropHandleT<BH> m_dstcurve;
		OpenMesh::EPropHandleT<BH> m_srcmark;
		OpenMesh::EPropHandleT<BH> m_dstmark;
		OpenTriMesh&           m_src;
		OpenTriMesh&           m_dst;
		cfloat                 m_epsilon;    
		cfloat                 m_precision;  
		std::atomic<int>       m_nodeclock;
		fast_map<BH, VH>       m_map2src;
		fast_map<BH, VH>       m_map2dst;
		std::set<BoolSegment>       m_mergenode;
		std::shared_ptr<Cart3DBvh>  m_srcbvh;
		std::shared_ptr<Cart3DBvh>  m_dstbvh;
	};

}

#endif // MESH_BOOLEAN_EXACT_IMPL_H

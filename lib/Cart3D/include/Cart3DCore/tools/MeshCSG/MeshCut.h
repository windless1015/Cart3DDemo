#ifndef CART3D_MESH_CUT_H
#define CART3D_MESH_CUT_H

#include <Cart3DToolsDefine.h>
#include <MeshCSG/MeshCSGUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
	
	class CART3D_TOOLS_CLASS MeshCut
	{
	public:
		//平面切割器
		MeshCut(
			const CSGMesh& mesh,
			const Planer& plane);
		//球面切割器
		MeshCut(
			const CSGMesh& mesh,
			const cvector3d& global_cent);
		//线段切割器
		MeshCut(
			const CSGMesh& mesh,
			const Segmenter& seg);
	public:
		
	public: 
		bool realtime_extract_pos_open_mesh(cfloat level, CSGMesh& btm);
		bool realtime_extract_neg_open_mesh(cfloat level,CSGMesh& btm);
	private:
		bool pos_kore(cfloat level, CSGMesh& btm, ct_vector<int>& face,ct_vector<int>& vids);
		bool neg_kore(cfloat level, CSGMesh& btm, ct_vector<int>& face, ct_vector<int>& vids);
	private:
		MeshCut(const MeshCut& that) = delete;
		MeshCut& operator=(const MeshCut& that) = delete;
	private:
		void init_plane_field(
			const cvector3d& plane_ori,
			const cvector3d& plane_dir);
		void init_global_field(const cvector3d& plane_ori);
		void init_segment_field(
			const cvector3d& start,
			const cvector3d& end);
	private:
		const CSGMesh& m_mesh;
		ct_vector<cfloat> m_filed;
	private:
		cfloat        m_max_offset;  //最大偏移值
		cfloat        m_min_offset;  //最小偏移值
	private:

	};



}


#endif
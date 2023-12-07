#ifndef CART3D_TOOLS_MESHCIRCLE_CURVE_H
#define CART3D_TOOLS_MESHCIRCLE_CURVE_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	struct ConvexWeight
	{
		VH vh;
		cfloat curvature;
		bool operator<(const ConvexWeight& that)const {
			return curvature < that.curvature;
		}
		bool operator==(const ConvexWeight& that)const {
			return curvature == that.curvature;
		}
		bool operator!=(const ConvexWeight& that)const {
			return curvature != that.curvature;
		}
	};
	/*
	 * @class MeshCircleCurve 网格闭合曲线环，目前只是简单实现，还需要进一步优化
	 * @detail 
	 */
	class CART3D_TOOLS_API MeshCircleCurve
	{
		struct Cache;
	public:
		MeshCircleCurve(OpenTriMesh& mesh);
	public:
		//根据采样点，查找网格脊线
		bool extract_convex_loops(const std::vector<cvector3d>& seed, std::vector<VH>& loops)const;
		//根据采样点，查找网格槽线
		bool extract_concave_loops(const std::vector<cvector3d>& seed, std::vector<VH>& loops)const;

	private:
		cfloat spfh_convex(const VH& se,const VH& dt,std::vector<VH>& path)const;
		cfloat spfh_concave(const VH& se,const VH& dt,std::vector<VH>& path)const;
	private:
		OpenTriMesh& m_mesh;
		std::shared_ptr<Cache> m_cache;
	};


}



#endif
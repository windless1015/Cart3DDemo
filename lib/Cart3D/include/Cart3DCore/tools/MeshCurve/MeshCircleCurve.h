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
	 * @class MeshCircleCurve ����պ����߻���Ŀǰֻ�Ǽ�ʵ�֣�����Ҫ��һ���Ż�
	 * @detail 
	 */
	class CART3D_TOOLS_API MeshCircleCurve
	{
		struct Cache;
	public:
		MeshCircleCurve(OpenTriMesh& mesh);
	public:
		//���ݲ����㣬����������
		bool extract_convex_loops(const std::vector<cvector3d>& seed, std::vector<VH>& loops)const;
		//���ݲ����㣬�����������
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
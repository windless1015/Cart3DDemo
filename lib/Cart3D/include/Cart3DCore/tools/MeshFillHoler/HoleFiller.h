#ifndef CART3D_TOOLS_HOLEFILLER_H
#define CART3D_TOOLS_HOLEFILLER_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{

	/*
	 * @file  HoleFiller.h
	 * @brief 这里提供了两个类，简单补洞算法以及细节控制补洞算法
	 * @detail 补洞难点在于曲率信息恢复，简单补洞，仅仅时为了适应边界连续，这完全来自于开源算法
	 * @class SimpleHoleFiller 参考OpenFlipper实现
	 * @class OptimHoleFiller 完全自己提出一种补洞算法，该算法理论尚未完善....
	 */
	class CART3D_TOOLS_CLASS SimpleHoleFiller
	{
	public: 
		//对空洞进行三角化,通过二面角以及面积进行约束
		static bool fill_hole(OpenTriMesh& mesh, const HH& hh);
		static bool fill_hole(OpenTriMesh& mesh,const HH& hhs,
			std::vector<FH>& newfhs,std::vector<EH>& newedges);
	public:
		//耳切法填充三角形孔洞
		static bool fill_hole_earcut(OpenTriMesh& mesh, const HH& hh);
		static bool fill_hole_earcut(OpenTriMesh& mesh, const HH& hh,
			std::vector<FH>& newfhs, std::vector<EH>& newedges);
	public:
		//对孔洞进行细分、光顺,目前只支持小曲率
		static bool refine_and_fill_hole(OpenTriMesh& mesh, const HH& hh);
	};
	enum class OptimFillHoleStyle
	{
		MinArea, MaxAngleMinArea, MaxAngle
	};
	class CART3D_TOOLS_CLASS OptimHoleFiller
	{
	public:
		static bool sewUpLoopMaxAngle(OpenTriMesh& mesh,
			const std::vector<VH>& oppvhs,
			const std::vector<VH>& vhs, std::vector<int>& tris);
		static bool sewUpLoopMinArea(OpenTriMesh& mesh, const std::vector<VH>& vhs, std::vector<int>& tris);
	public:
		
		static bool auto_fill_hole(OpenTriMesh& mesh, bool refine, bool fair, OptimFillHoleStyle fhse= OptimFillHoleStyle::MaxAngleMinArea, int max_hole = 1024);

	};

}



#endif
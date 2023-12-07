#ifndef CART3D_TOOLS_LAPLACEDEFORMATION_H
#define CART3D_TOOLS_LAPLACEDEFORMATION_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	struct CacheDeform;
	class CART3D_TOOLS_CLASS LaplaceDeformer
	{
	public:
		LaplaceDeformer(OpenTriMesh& mesh);

	public:
		void reset();
		bool set_regions(
			const std::vector<VH>&handles,
			const std::vector<VH>&freedeform, bool RSI = true);
	public:
		bool transform(const cmatrix4d& mat);
		bool transform(const cmatrix4d& mat, std::vector<std::pair<VH, cvector3d>>& new_pos);
	protected:
		bool prepare_deform(bool RSI);
	protected:
		std::vector<VH> m_vHandle; //控制区域
		std::vector<VH> m_vBoundary; //边界固定区域
		std::vector<VH> m_vSupport; //变形区域
	protected:
		OpenTriMesh& m_mesh;
		std::shared_ptr<CacheDeform> m_vCache;
	};


}





#endif

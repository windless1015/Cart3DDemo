#ifndef CART3D_TOOLS_POISSONDEFORMATION_H
#define CART3D_TOOLS_POISSONDEFORMATION_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	//Todo...
	class CART3D_TOOLS_CLASS PoissonDeformation
	{
	public:
		struct CacheImpl;
	public:
		PoissonDeformation(OpenTriMesh& mesh);
	public:
		void reset();
		bool set_regions(
			const std::vector<VH>&handles,
			const std::vector<VH>&support);
	public:

	private:
		std::vector<VH> m_vHandle; //��������
		std::vector<VH> m_vBoundary; //�߽�̶�����
		std::vector<VH> m_vSupport; //��������
	protected:
		OpenTriMesh& m_mesh;
		std::shared_ptr<CacheImpl> m_vCache;
	};


}


#endif
#pragma once

#ifndef CART3D_TOOLS_MESHPATCH_H
#define CART3D_TOOLS_MESHPATCH_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"
#include <Util/BoostUtil.h>
namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshPatch
	{
	public:
		static bool mesh_parts(
			const OpenTriMesh& mesh,
			std::vector<int>& parts,
			int& max_parts);
		//通过并查集的方式
		static bool uf_mesh_parts(
			const OpenTriMesh& mesh,
			std::vector<int>& parts,
			int& max_parts);

		//获取子组件
		static bool sub_mesh(const OpenTriMesh& m_mesh,
			const ct_vector<int>&faces, OpenTriMesh& mesh);
		static bool get_max_patch(const OpenTriMesh& mesh, OpenTriMesh& submesh);
		static bool get_patch(const OpenTriMesh& mesh,const std::vector<int>& parts, int pt, OpenTriMesh& submesh);

	};


}


#endif

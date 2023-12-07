#pragma once
#ifndef CART3D_MESH_SELECTOR_H
#define CART3D_MESH_SELECTOR_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"


namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshSelector
	{
	public:

		static void selct_nn_vhs(
			const OpenTriMesh& mesh,
			const std::vector<VH>& seeds, int nn, std::vector<VH>& vhs,bool addseed);
		static void select_nn_face(
			const OpenTriMesh& mesh, const VH& source, int nn,
			std::vector<FH>& face);
		static void select_nn_face(
			const OpenTriMesh& mesh, const FH& source, int nn,
			std::vector<FH>& face);
	};


}




#endif
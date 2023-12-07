#ifndef CART3D_MESH_JOINER_H
#define CART3D_MESH_JOINER_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	enum class JoinerFlag
	{
		SOURCE,
		DEST,
		NEW
	};
	enum class JoinType {
		ANGLE,LENGTH
	};
	class CART3D_TOOLS_CLASS MeshJoiner
	{
	public:
		static bool join_mesh(
			const OpenTriMesh& src, const HH& hsrc,
			const OpenTriMesh& dst, const HH& hdst,
			OpenTriMesh& mesh, JoinType jt= JoinType::LENGTH);

		static bool join_mesh(
			const OpenTriMesh& src, const HH& hsrc,
			const OpenTriMesh& dst, const HH& hdst,
			OpenTriMesh& mesh, std::vector<FH>&newface, JoinType jt = JoinType::LENGTH);

		static bool smooth_join_mesh(
			const OpenTriMesh& src, const HH& hsrc,
			const OpenTriMesh& dst, const HH& hdst,
			OpenTriMesh& mesh, JoinType jt = JoinType::LENGTH);

		static bool min_dist_join_mesh(
			const OpenTriMesh& src, const HH& hsrc,
			const OpenTriMesh& dst, const HH& hdst,
			OpenTriMesh& mesh,std::vector<FH>&newface,
			OpenMesh::VPropHandleT<JoinerFlag>& vflag,OpenMesh::FPropHandleT<JoinerFlag>& fflag);

		static bool min_angle_join_mesh(const OpenTriMesh& src, const HH& hsrc,
			const OpenTriMesh& dst, const HH& hdst,
			OpenTriMesh& mesh, std::vector<FH>&newface,
			OpenMesh::VPropHandleT<JoinerFlag>& vflag, OpenMesh::FPropHandleT<JoinerFlag>& fflag);


		static void del_noise_mesh_boundary(OpenTriMesh& mesh);

	};

}


#endif
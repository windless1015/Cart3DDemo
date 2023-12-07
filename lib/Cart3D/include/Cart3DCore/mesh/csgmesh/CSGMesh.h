#ifndef CART3D_CSG_MESH_H
#define CART3D_CSG_MESH_H

#include <Cart3dMeshDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	struct CART3D_MESH_CLASS CSGMesh
	{
		std::vector<char> vflag;
		std::vector<cvector3d> pts;
		std::vector<cvector3i> tris;
	public:
		std::vector<int> get_plane_faces()const;
		cvector3d& get_vCoord(int i);
		const cvector3d& get_vCoord(int i)const;
		int add_vCoord(const cvector3d& pt);
		int add_vCoord(const cvector3d& pt, unsigned char flag);
		int add_faces(const cvector3i& face);
		void clear();
		cfloat max_x(int i);
		const cvector3i& get_face(int i)const;
		cvector3i& get_face(int i);
		int get_vn()const;
		int get_fn()const;
		void get_box(cvector3d& minp, cvector3d& maxp,bool update=true)const;
	public:
		void merge_duplicated(int min_quinter=5);
		void reverse_face_nor();
	public:
		bool load_mesh(const std::string& filename);
		bool write_mesh(const std::string& filename);
	};
	using BaseTriMesh = CSGMesh;
	CART3D_MESH_API bool to_basemesh(const OpenTriMesh& mesh, CSGMesh& btm);
	CART3D_MESH_API bool to_trimesh(const CSGMesh& mesh, OpenTriMesh& btm);
	CART3D_MESH_API bool append_mesh(CSGMesh& mesh, const CSGMesh& smesh);



}

#endif // !CART3D_CSG_MESH_H
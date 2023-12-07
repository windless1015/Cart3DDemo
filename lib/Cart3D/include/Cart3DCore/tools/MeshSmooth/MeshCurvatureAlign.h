#ifndef CART3D_MESH_CURVATURE_ALIGN_H
#define CART3D_MESH_CURVATURE_ALIGN_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshCurvatureAlign
	{
	public:
		MeshCurvatureAlign() : _midCurv(0.25), _maxRatio(5), _isUseCurv(true), _skip_low_curv(0.0) {}
	public:
		void run_sort(OpenTriMesh& mesh);
		void run_ex(OpenTriMesh& mesh);
		void set_is_use_curvature(bool f) { _isUseCurv = f; }
		bool get_is_use_curvature() const { return _isUseCurv; }
		void set_skip_low_curv(cfloat d) { _skip_low_curv = d; }
	protected:
		void compute_principal_curvature_direction(OpenTriMesh& mesh, VH vHandle,
			cmatrix3d& direction, cfloat& maxk, cfloat& mink);
		cfloat compute_face_area(OpenTriMesh& mesh, FH fHandle);
		void compute_halfedge_vec_changeby_curvature(OpenTriMesh& mesh, HH hHandle,
			OpenTriMesh::Normal& vec);
		void compute_face_normal_changeby_curvature(OpenTriMesh& mesh, HH hHandle,
			OpenTriMesh::Normal& normal);
		void update_property_for_flip(OpenTriMesh& mesh, EH eHandle);
		void get_affect_edge(OpenTriMesh& mesh, EH ehandle, std::vector<EH>& affectEdge);
		cfloat compute_flip_cost(OpenTriMesh& mesh, EH  ehandle);
		cfloat compute_cost_about_halfedge(OpenTriMesh& mesh, HH hHandle);
		bool judge_flip(OpenTriMesh& mesh, EH  ehandle);
	private:
		cfloat _midCurv;
		cfloat _maxRatio;
		bool _isUseCurv;
		OpenMesh::VPropHandleT<OpenTriMesh::Normal> VPropMaxVec;
		OpenMesh::VPropHandleT<cfloat> VPropRatio;
		OpenMesh::HPropHandleT<OpenTriMesh::Normal> HPropVec;
		OpenMesh::HPropHandleT<OpenTriMesh::Normal> HPropNormal;
		cfloat _skip_low_curv;
	};
}


#endif
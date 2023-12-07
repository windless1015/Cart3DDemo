#ifndef CART3D_MESHFIX_VCG_MESH_TOPOLOGY_H
#define CART3D_MESHFIX_VCG_MESH_TOPOLOGY_H

#include <Sys/CPUTimer.h>
#include <vcg/complex/complex.h>
#include <vcg/mesh/topology.h>

namespace Cart3D
{
	using namespace vcg;

	enum  TopoType {
		TopoType_FF = 1,
		TopoType_VF = 2,
		TopoType_EF = 4,
		TopoType_FE = 8,
		TopoType_EE = 16,
		TopoType_VE = 32
	};
	template <class vcgMesh>
	void update_topo(vcgMesh &in, const int &updateTpye=0xff)
	{
		CD_TIMER;
		bool hasFF = false, hasVF = false, hasEF = false, hasEE = false, hasVE = false, hasFE = false;

		if ((updateTpye & TopoType_FF) != 0)
			hasFF = true;
		if ((updateTpye & TopoType_VF) != 0)
			hasVF = true;
		if ((updateTpye & TopoType_EF) != 0)
			hasEF = true;
		if ((updateTpye & TopoType_FE) != 0)
			hasFE = true;
		if ((updateTpye & TopoType_EE) != 0)
			hasEE = true;
		if ((updateTpye & TopoType_VE) != 0)
			hasVE = true;

		if (vcg::tri::HasFFAdjacency(in) && hasFF)
			vcg::tri::UpdateTopology<vcgMesh>::FaceFace(in);
		if (vcg::tri::HasVFAdjacency(in) && hasVF)
			vcg::tri::UpdateTopology<vcgMesh>::VertexFace(in);

		if (vcg::tri::HasEVAdjacency(in) || vcg::tri::HasVEAdjacency(in) ||
			vcg::tri::HasFEAdjacency(in) || vcg::tri::HasEFAdjacency(in))
			if (hasEF || hasEE || hasVE || hasFE)
				vcg::tri::UpdateTopology<vcgMesh>::AllocateEdge(in);

		if (tri::HasEEAdjacency(in) && hasEE)
			tri::UpdateTopology<vcgMesh>::EdgeEdge(in);

		if (vcg::tri::HasVEAdjacency(in) && hasVE)
			vcg::tri::UpdateTopology<vcgMesh>::VertexEdge(in);
	}

	template<class vcgMesh>
	void clear_deleted_faces(vcgMesh &in)
	{
		CD_TIMER;
		if (vcg::tri::HasPerFaceFlags(in))
		{
			int begin = 0;
			int end = in.face.size() - 1;
			for (; begin <= end;)
			{
				for (; begin <= end && !in.face[begin].IsD(); ++begin);
				for (; begin <= end && in.face[end].IsD(); --end);
				if (end > begin)
				{
					std::swap(in.face[begin], in.face[end]);
					++begin;
					--end;
				}
			}
			in.face.resize(end + 1);
			in.fn = end + 1;
		}
	}

	template<class vcgMesh>
	void clearFaceV(vcgMesh &in)
	{
		CD_TIMER;
		for (typename vcgMesh::FaceIterator fi = in.face.begin(); fi != in.face.end(); ++fi)
		{
			(*fi).ClearV();
		}
	}

	template<class vcgMesh>
	void clearFaceD(vcgMesh &in)
	{
		CD_TIMER;
		for (typename vcgMesh::FaceIterator fi = in.face.begin(); fi != in.face.end(); ++fi)
		{
			(*fi).ClearD();
		}
	}


	template<class vcgMesh>
	void clearVertV(vcgMesh &in)
	{
		CD_TIMER;
		for (typename vcgMesh::VertexIterator vi = in.vert.begin(); vi != in.vert.end(); ++vi)
		{
			(*vi).ClearV();
		}
	}


	template<class vcgMesh>
	void getBox(
		const vcgMesh    &in,
		Eigen::Vector3f& boxMin,
		Eigen::Vector3f& boxMax
	)
	{
		CD_TIMER;
		boxMin.x() = boxMin.y() = boxMin.z() = FLT_MAX;
		boxMax.x() = boxMax.y() = boxMax.z() = -FLT_MAX;
		for (int i = 0; i < in.vert.size(); i++)
		{
			if (boxMin.x() > in.vert[i].cP().x())
				boxMin.x() = in.vert[i].cP().x();
			if (boxMin.y() > in.vert[i].cP().y())
				boxMin.y() = in.vert[i].cP().y();
			if (boxMin.z() > in.vert[i].cP().z())
				boxMin.z() = in.vert[i].cP().z();

			if (boxMax.x() < in.vert[i].cP().x())
				boxMax.x() = in.vert[i].cP().x();
			if (boxMax.y() < in.vert[i].cP().y())
				boxMax.y() = in.vert[i].cP().y();
			if (boxMax.z() < in.vert[i].cP().z())
				boxMax.z() = in.vert[i].cP().z();
		}
	}

	template<class vcgMesh>
	int find_shells_vcg(
		vcgMesh                       &vcgmesh,
		std::vector<std::vector<int>> &shells,
		bool                           needUpdateTopo = true
	)
	{
		CD_TIMER;
		typedef  vcgMesh	                 VcgMeshCell;
		typedef  typename vcgMesh::FaceType	 VcgFaceCell;
		shells.clear();
		if (needUpdateTopo)
			update_topo(vcgmesh, TopoType_FF);
		clearFaceV(vcgmesh);
		auto FindAllFacesInOneShell = [&](VcgFaceCell& f, std::vector<int> &si, int size) {
			si.clear();
			f.SetV();
			std::vector<VcgFaceCell*> fv;
			fv.push_back(&f);
			for (size_t i = 0; i < fv.size(); ++i) {
				si.push_back(vcg::tri::Index(vcgmesh, fv[i]));
				for (int j = 0; j < 3; ++j) {
					if (!fv[i]->cFFp(j)->IsD() && !fv[i]->cFFp(j)->IsV() 
						&& !vcg::face::IsBadEdge<VcgFaceCell>(*fv[i], j)) {
						fv.push_back(fv[i]->cFFp(j));
						fv[i]->cFFp(j)->SetV();
					}
				}
			}
		};
		int size = vcgmesh.face.size();
		for (typename VcgMeshCell::FaceIterator fi = vcgmesh.face.begin(); fi != vcgmesh.face.end(); ++fi)
		{
			if (!(*fi).IsD() && !(*fi).IsV())
			{
				std::vector<int> si;
				FindAllFacesInOneShell(*fi, si, size);
				shells.push_back(si);
			}
		}
		return shells.size();
	}
	template<class vcgMesh>
	int find_components_vcg(
		vcgMesh                       &vcgmesh,
		std::vector<std::vector<int>> &components,
		bool                          needUpdateTopo = true
	)
	{
		CD_TIMER;
		typedef  vcgMesh	                 VcgMeshCell;
		typedef  typename vcgMesh::FaceType	 VcgFaceCell;
		components.clear();
		vcg::tri::RequireFFAdjacency(vcgmesh);
		if (needUpdateTopo)
			update_topo(vcgmesh, TopoType_FF);
		clearFaceV(vcgmesh);
		auto FindAllFacesInOneComponent = [&](VcgFaceCell& f, std::vector<int> &si, int size) {
			si.clear();
			f.SetV();
			std::vector<VcgFaceCell*> fv;
			fv.push_back(&f);
			for (size_t i = 0; i < fv.size(); ++i) {
				si.push_back(vcg::tri::Index(vcgmesh, fv[i]));
				for (int j = 0; j < 3; ++j) {
					if (!fv[i]->cFFp(j)->IsD() && !fv[i]->cFFp(j)->IsV()) {
						fv.push_back(fv[i]->cFFp(j));
						fv[i]->cFFp(j)->SetV();
					}
				}
			}
		};

		int size = vcgmesh.face.size();
		for (typename VcgMeshCell::FaceIterator fi = vcgmesh.face.begin(); fi != vcgmesh.face.end(); ++fi)
		{
			if (!(*fi).IsD() && !(*fi).IsV())
			{
				std::vector<int> ci;
				FindAllFacesInOneComponent(*fi, ci, size);
				components.push_back(ci);
			}
		}
		return components.size();
	}
}
#endif 



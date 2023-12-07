#ifndef CART3D_AUTO_GEN_BUCKET_SHELL_H
#define CART3D_AUTO_GEN_BUCKET_SHELL_H

#include <Util/OpenMeshUtil.h>
#include <CoordSystem/CoordSystem.h>
#include <csgmesh/CSGMesh.h>
namespace Cart3D
{

	class AutoGenBucketShell
	{
	public:
		AutoGenBucketShell(OpenTriMesh& buckets, CoordSystem& sys);
	public:
		void set_axial_angle(cfloat ang);
		void set_xylength(cfloat xlen = 5, cfloat ylen = 5);
		void set_deep(cfloat deep = 2);
		void set_zdeep(cfloat deep = 0.05);
		void set_shell(cfloat shell = 0.2);
		void set_xlen(cfloat xl = 5);
		void set_ylen(cfloat yl = 5);
		void set_zlen(cfloat zl = 2);

	public:
		void run(OpenTriMesh& shell);
	public:
		void gen_base(const cvector3d& dir, std::vector<cvector3d>& tribox,std::vector<int>& triIndex);
		void gen_undercut(
			const cvector3d& p0, const cvector3d&p1, const cvector3d&p2, const cvector3d&p3,
			const cvector3d& dir, std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void gen_undercut(const cvector3d& dir, std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void remove_hole(OpenTriMesh& mesh);
		void gen_zplane(const cvector3d& cdir, std::vector<cvector3d>& tribox, std::vector<int>& triIndex);

		void gen_cut(const cvector3d& dir, const std::vector<cvector3d>& loops, CSGMesh& plane, CSGMesh& cly);

		cvector3d gen_yplane(std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
	protected:
		OpenTriMesh& m_buckets; //Õ–≤€
		CoordSystem  m_sys;
	protected:
		cfloat m_axial_angle; //÷·«„Ω«
		cfloat m_xlength,m_ylength; //ø«≥§∂»
		cfloat m_deep; //z÷·∫Ò∂»
		cfloat m_shell; //shell∫Ò∂»
		cfloat m_zdeep; //z÷·º‰œ∂
	};



}



#endif
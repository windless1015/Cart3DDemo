#ifndef CART3D_AUTO_FGEN_BUCKET_SHELL_H
#define CART3D_AUTO_FGEN_BUCKET_SHELL_H

#include <Util/OpenMeshUtil.h>
#include <csgmesh/CSGMesh.h>
#include <CoordSystem/CoordSystem.h>
namespace Cart3D
{
	class AutoGen0BucketShell
	{
	public:
		AutoGen0BucketShell(OpenTriMesh& buckets, CoordSystem& sys);
		virtual ~AutoGen0BucketShell(){}
	public:
		void set_xlen(cfloat xl = 7);
		void set_ylen(cfloat yl = 5);
		void set_zlen(cfloat zl = 2);
		void set_shell(cfloat zl = 0.08);
		void set_offset(cfloat zl = 0.5);
	public:
		void gen_base(std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void gen_undercut(
			const cvector3d& dir, std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
		void gen_xplane(std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void gen_ysurf(const CSGMesh& btm,const cvector3d& dir, CSGMesh& ysurf);
		void gen_yplane(cvector3d dir, std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
		void gen_zplane(cvector3d dir, std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void gen_zplane(cvector3d dir,const std::vector<cvector3d>& plane,
			std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
	protected:
		OpenTriMesh& m_fbuckets; //ÍÐ²Û
		CoordSystem  m_sys;
	protected:
		cfloat m_xlen;
		cfloat m_ylen;
		cfloat m_zoffset;
		cfloat m_shell;
		cfloat m_offset;
	};






}


#endif
#ifndef CART3D_AUTO_2GEN_BUCKET_SHELL_H
#define CART3D_AUTO_2GEN_BUCKET_SHELL_H

#include <Util/OpenMeshUtil.h>
#include <csgmesh/CSGMesh.h>
#include <CoordSystem/CoordSystem.h>
namespace Cart3D
{
	class AutoGen2BucketShell
	{
	public:
		AutoGen2BucketShell(OpenTriMesh& buckets, CoordSystem& sys);
		virtual ~AutoGen2BucketShell() {}
	public:
		void set_debug_path(std::string str);
	public:
		void set_xlen(cfloat xl = 7);
		void set_ylen(cfloat yl = 5);
		void set_zlen(cfloat zl = 2);
		void set_shell(cfloat zl = 0.08);
		void set_offset(cfloat zl = 0.5);
		
	public:
		void gen_base(std::vector<cvector3d>& tribox, std::vector<int>& triIndex);
		void gen_undercut(const cvector3d& dir, std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
		void gen_yplane(std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
		bool gen_zcsg(cvector3d dir, std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
		void gen_zplane(cvector3d dir, std::vector<cvector3d>& triUndercut, std::vector<int>& triIndex);
	protected:
		OpenTriMesh& m_fbuckets; //ÍÐ²Û
		CoordSystem  m_sys;
	protected:
		cfloat m_xlen;
		cfloat m_ylen;
		cfloat m_zoffset;
		cfloat m_shell;
		cfloat m_offset;
	private:
		std::string m_debug_path;
	};





}


#endif
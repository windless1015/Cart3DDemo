#ifndef CART3D_DENTAL_GUMSGENERATION_H
#define CART3D_DENTAL_GUMSGENERATION_H

#include <map>
#include <dentalmesh/SurfaceMesh.h>

namespace Cart3D
{
	class GumsInfo;

	enum class VertexType
	{
		Labial, //唇侧
		Buccal, //舌测
		Molar   //磨牙区域
	};
	
    class GumsGeneration
    {
	public:
		GumsGeneration(
			std::shared_ptr<pmp::SurfaceMesh>& ginval,
			std::map<int, std::shared_ptr<pmp::SurfaceMesh>>& toothes);
		void set_debug_info(bool debug, std::string debugpath);
	public:
		void set_gums_height(float h);
		void set_plane_dir(const pmp::Point&dir);
		bool generation_gums(
			std::vector<pmp::Point>&pts,
			std::vector<int>& tris,
			std::vector<int>& loopid,
			std::vector<VertexType>& looptype,
			std::vector<pmp::Point>& hloops,
			std::vector<pmp::Point>& dloops);
		bool generation_gums_rt(const std::map<int, pmp::mat4>& mat,
			std::vector<pmp::Point>& pts, std::vector<int>& tris,
			std::vector<int>& loopid,
			std::vector<VertexType>& looptype,
			std::vector<pmp::Point>& hloops,
			std::vector<pmp::Point>& dloops);
	private:
		void optim_mesh(
			std::vector<pmp::Point>& pts,
			std::vector<int>& tris,
			std::vector<int>& idus, std::vector<int>& idue,
			std::vector<int>& idvs, std::vector<int>& idve);
	private:
		bool generation_boundarys(std::vector<int>& utype,
			std::vector<pmp::Point>& centlines,
			std::vector<pmp::Point>& hus, std::vector<pmp::Point>& hue,
			std::vector<pmp::Point>& hvs, std::vector<pmp::Point>& hve,
			std::vector<pmp::Point>& dus, std::vector<pmp::Point>& due,
			std::vector<pmp::Point>& dvs, std::vector<pmp::Point>& dve)const;
		bool generation_body(
			std::vector<pmp::Point>& centlines,
			std::vector<pmp::Point>& hus, std::vector<pmp::Point>& hue,
			std::vector<pmp::Point>& hvs, std::vector<pmp::Point>& hve,
			std::vector<pmp::Point>& dus, std::vector<pmp::Point>& due,
			std::vector<pmp::Point>& dvs, std::vector<pmp::Point>& dve,
			const std::vector<int>& vsid, const std::vector<int>& veid,
			const std::vector<int>& uid,
			std::vector<int>& loopid,
			std::vector<VertexType>& looptype,
			std::vector<pmp::Point>& hloops,
			std::vector<pmp::Point>& dloops,
			std::vector<pmp::Point>&pts, 
			std::vector<int>& tris, 
			std::vector<int>& idus, std::vector<int>& idue, 
			std::vector<int>& idvs, std::vector<int>& idve,
			std::vector<std::vector<int>>& idmap)const;

		
		
	private:
		void extract_loops_and_map_table(int nhus, 
			std::vector<int> &cvhs, 
			std::vector<pmp::Point> & pts,
			std::vector<pmp::Point> &dcents, 
			std::vector<int> &idus, 
			std::vector<int> &idve, 
			int nhvs, std::vector<pmp::Point> &dloops,
			std::vector<pmp::Point> & dve,
			std::vector<pmp::Point> &hloops,
			std::vector<pmp::Point> & hve,
			std::vector<pmp::Point> & centlines,
			std::vector<int> &idue, 
			std::vector<pmp::Point> & due, 
			std::vector<pmp::Point> & hue,
			std::vector<int> &idvs,
			std::vector<pmp::Point> & dvs,
			std::vector<pmp::Point> & hvs,
			const std::vector<int>& vsid, const std::vector<int>& veid,
			const std::vector<int>& uid, 
			std::vector<int>& loopid,
			std::vector<VertexType>& looptype,
			std::vector<float>& ss_weights)const;


	private:
		//样条插值
		static void quadratic(
			const pmp::Point& A,
			const pmp::Point& B,
			const pmp::Point& C,
			const std::vector<pmp::Scalar>& weights,
			std::vector<pmp::Point>& curve);
		//双线性插值
		static void generation_quad_surface(
			int udim, int vdim,
			std::vector<pmp::Point>& x);
	private:
		std::shared_ptr<GumsInfo> m_gums_info; 
	
	private:
		//牙龈相关参数，注意这里参数不要轻易动
		int nteeth;
		int udim, vdim, wdim;
		pmp::Scalar height;
		pmp::Point dirp;
		bool is_upper_jaw;
    };

}



#endif
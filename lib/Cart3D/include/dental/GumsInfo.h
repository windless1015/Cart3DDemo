#ifndef CART3D_DENTAL_GUMSINFO_H
#define CART3D_DENTAL_GUMSINFO_H

#include <dentalmesh/SurfaceMesh.h>
#include <map>

namespace Cart3D
{

    class GumsInfo
    {
    public:
        struct Cache;
    public:
        GumsInfo(std::shared_ptr<pmp::SurfaceMesh> gum,
            std::map<int, std::shared_ptr<pmp::SurfaceMesh>>& toothes);

    public:
		void set_debug(bool debug, std::string degpath);
    public:
        //����ֻ��Ҫ����һ��
        bool pre_solve_gums_lines();
		//�������ƽ��
		void fit_gums_plane();
		void fit_gums_plane(const pmp::Point& dir);
        //���ɳ�ʼ������������ֽ��
        void rt_cache(const pmp::Point& dir);
        void rt_cache(const pmp::Point& dir,const std::map<int,pmp::mat4>&rts);
        bool generation_gums_lines();
	public:
		//�⻬�Լ�����������
		bool sample_gums_pts(
			std::vector<int>& utype,
			std::vector<pmp::Point>& us,
			std::vector<pmp::Point>& ue,
			std::vector<pmp::Point>& vs,
			std::vector<pmp::Point>& ve);

    public:
        //���������߶�
        void set_gums_height(float h); 
		void set_sample_dims(int udim, int vdim,int hdim);
        //���㹭���ߣ�ע������ֻ��Ҫ����һ��
        bool compute_male_lines(
			const std::vector<int>& utype,
			const std::vector<pmp::Point>& hus,
			const std::vector<pmp::Point>& hue,
            std::vector<pmp::Point>& centlines,
            std::vector<pmp::Point>& us,
            std::vector<pmp::Point>& ue,
            std::vector<pmp::Point>& vs,
            std::vector<pmp::Point>& ve,bool is_upper);

        
    public:
		std::pair<pmp::Point, pmp::Point> get_plane()const;

    private:
        //��ȡ���ݱ߽���
        bool extract_boundary();
       
        //�Ż��ֽ��
        void optim_split_point();

    private:
        std::shared_ptr<pmp::SurfaceMesh> m_gum_mesh; //�������
        std::map<int, std::shared_ptr<pmp::SurfaceMesh>> m_teet_mesh; //��������
    private:
        static std::pair<pmp::Point, pmp::Point>
            best_plane_from_points(const std::vector<pmp::Point>& c);
        std::shared_ptr<Cache> m_ori_cache;
        std::shared_ptr<Cache> m_rt_cache;
		bool is_debug;
		std::string debug_path;
		//Todo...
		bool debug_circle(int r = 255, int g = 0, int b = 0);
		void wrte_pts(std::string filename, 
			const std::vector<pmp::Point>& pts,
			int r = 255, int g = 0, int b = 0);
    };


}




#endif
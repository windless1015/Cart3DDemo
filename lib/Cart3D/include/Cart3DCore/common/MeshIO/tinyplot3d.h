#ifndef CART3D_TINY_PLOT3D_H
#define CART3D_TINY_PLOT3D_H


#include <Cart3DCommonDefine.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{

	class CART3D_COMMON_CLASS Plot3dBlk
	{
	public:
		Plot3dBlk(int udim, int vdim, int wdim,
			const std::vector<cvector3d>&pts);
		Plot3dBlk(int udim, int vdim, int wdim,
			const std::vector<cfloat>&pts_x,
			const std::vector<cfloat>&pts_y,
			const std::vector<cfloat>&pts_z);
		Plot3dBlk(int udim, int vdim, int wdim);
	public:
		static cvector3i ijk(const int &imax, const int &jmax, const int &kmax, const int &index);
		static int idx(const int &i, const int &j, const int &k, const int &imax, const int &jmax);
	public:
		//input cell coordinates, get face coordinates
		static int calc_upper_face_u(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int calc_lower_face_u(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int calc_upper_face_v(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int calc_lower_face_v(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int calc_upper_face_w(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int calc_lower_face_w(const int &, const int &, const int &, const int &, const int &, int = 1);
		//input cell coordinates get neighbor cell coordinates
		static int get_neighbor_upper_i(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_neighbor_lower_i(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_neighbor_upper_j(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_neighbor_lower_j(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_neighbor_upper_k(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_neighbor_lower_k(const int &, const int &, const int &, const int &, const int &, int = 1);
		//input face coordinates, get cell coordinates
		static int get_cell_from_face_upper_i(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_cell_from_face_lower_i(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_cell_from_face_upper_j(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_cell_from_face_lower_j(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_cell_from_face_upper_k(const int &, const int &, const int &, const int &, const int &, int = 1);
		static int get_cell_from_face_lower_k(const int &, const int &, const int &, const int &, const int &, int = 1);
	public:
		int num_u() const;
		int num_v() const;
		int num_w() const;
		int num_nodes() const;
		int num_cells() const;
		cfloat xloc(const int &a)const;
		cfloat yloc(const int &a)const;
		cfloat zloc(const int &a)const;
	public:
		void clean_resize(const int &i, const int &j, const int &k);
	public:
		const std::vector<cfloat> volume() const;
		const std::vector<cvector3d > centroid() const;
		const std::vector<cvector3d > face_area_u() const;
		const std::vector<cvector3d > face_area_v() const;
		const std::vector<cvector3d > face_area_w() const;
		const std::vector<cvector3d > face_center_u() const;
		const std::vector<cvector3d > face_center_v() const;
		const std::vector<cvector3d > face_center_w() const;
	public:
		void split(const std::string&, const int&, Plot3dBlk&, Plot3dBlk&) const;
		void join(const Plot3dBlk&, const std::string&);
	private:
		std::vector<cfloat> x;      //std::vector of x-coordinates
		std::vector<cfloat> y;      //std::vector of y-coordinates
		std::vector<cfloat> z;      //std::vector of z-coordinates
		union {
			struct {
				int numi;                   //number of points in i-direction
				int numj;                   //number of points in j-direction
				int numk;                   //number of points in k-direction
			};
			struct {
				int numu;                   //number of points in i-direction
				int numv;                   //number of points in j-direction
				int numw;                   //number of points in k-direction
			};
		};

	};

	struct CART3D_COMMON_CLASS IOPlot3D
	{
		static std::vector<Plot3dBlk> read_p3d_grid_binary(const std::string&, const cfloat&, cfloat&);
		static std::vector<Plot3dBlk> read_p3d_grid_ascii(const std::string&, const cfloat&, cfloat&);
		static void write_p3d_grid(const std::vector<Plot3dBlk>&, const std::string&, const cfloat&);
	};
}




#endif
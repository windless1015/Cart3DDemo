#ifndef CART3DALGORITHM_UTIL_H
#define CART3DALGORITHM_UTIL_H

#include <Cart3DCommonDefine.h>
#include <Eigen/Eigen>

namespace Cart3D
{
	using sbyte = unsigned char;
	using cfloat32 = float;
	using cfloat64 = double;
	using cfloat = cfloat64;
	template<class T,int udim,int vdim>
	using cmatrixt = Eigen::Matrix<T, udim, vdim>;
	template<int udim, int vdim>
	using cmatrixf32 = cmatrixt<cfloat32,udim,vdim>;
	template<int udim, int vdim>
	using cmatrixf64 = cmatrixt<cfloat64,udim,vdim>;


	template<int udim, int vdim>
	using cmatrix = cmatrixt<cfloat, udim, vdim>;



	using cmatrix4d =  cmatrix<4, 4>;
	using cmatrix3d =  cmatrix<3, 3>;
	using cmatrix2d =  cmatrix<2, 2>;
	using cquaternion = Eigen::Quaternion<cfloat>;


	using cmatrix_t =  Eigen::Matrix<cfloat, Eigen::Dynamic,Eigen::Dynamic>;

	template<class T,int size>
	using cvectort = Eigen::Matrix<T,size,1>;
	template<int dim>
	using cvectorf32 = cvectort<cfloat32,dim>;
	template<int dim>
	using cvectorf64 = cvectort<cfloat64,dim>;

	template<int dim>
	using cvector = cvectort<cfloat, dim>;
	using cvector4d = cvector<4>;
	using cvector3d = cvector<3>;
	using cvector2d = cvector<2>;

	using cvector4f = cvectort<float,4>;
	using cvector3f = cvectort<float,3>;
	using cvector2f = cvectort<float,2>;

	using cvector_t = Eigen::Matrix<cfloat, Eigen::Dynamic, 1>;

	using cvector2i = cvectort<int, 2>;
	using cvector2l = cvectort<std::int64_t, 2>;
	using cvector3i = cvectort<int, 3>;
	using cvector3l = cvectort<std::int64_t, 3>;
	using cvector4i = cvectort<int, 4>;
	using cvector4l = cvectort<std::int64_t, 4>;
	using cvetor3uc= Eigen::Matrix<unsigned char, 3,1>;
	using cvetor4uc= Eigen::Matrix<unsigned char, 4,1>;


	CART3D_COMMON_API bool operator==(const cvector3d& p0, const cvector3d& p1);
	CART3D_COMMON_API bool operator!=(const cvector3d& p0, const cvector3d& p1);
	CART3D_COMMON_API bool operator<(const cvector3d& p0, const cvector3d& p1);
	CART3D_COMMON_API bool operator==(const cvector3l& p0, const cvector3l& p1);
	CART3D_COMMON_API bool operator!=(const cvector3l& pt, const cvector3l& pq);
	CART3D_COMMON_API bool operator<(const cvector3l& pt, const cvector3l& pq);


	struct CART3D_COMMON_CLASS HashFunc {
		size_t operator()(const cvector3d& k) const;
	};
	struct CART3D_COMMON_CLASS EqualsFunc {
		bool operator()(const cvector3d& lhs, const cvector3d& rhs) const;
	};

	struct CART3D_COMMON_CLASS CmpVec {
		CmpVec(const cvector3d& pt);

		bool operator<(const CmpVec& p) const;
		bool operator==(const CmpVec& p) const;
		bool operator!=(const CmpVec& p) const;

		static void set_eps(cfloat eps);
		static cfloat m_eps;
		cvector3d m_pt;
	};

	CART3D_COMMON_API cfloat cross(const cvector2d& a, const cvector2d& b);

	template<class T>
	inline T gclamp(T a, T fm, T fx) {
		if (a < fm)return fm;
		if (a > fx)return fx;
		return a;
	}
	template<class T>
	inline T gmin(T a, T b, T c) {
		if (a > b) a = b;
		if (a > c) a = c;
		return a;
	}
	template<class T>
	inline T gmax(T a, T b, T c) {
		if (a < b) a = b;
		if (a < c) a = c;
		return a;
	}
	template<class T>
	inline T gmin(T a, T b) {
		if (a > b) a = b;
		return a;
	}
	template<class T>
	inline T gmax(T a, T b) {
		if (a < b) a = b;
		return a;
	}

	template <typename T>
	inline T sqr(T x)  { return x * x; }

	template <typename T>
	inline int sgn(T x)  { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

	CART3D_COMMON_API cvector3d rt_point(const cmatrix4d& rt, const cvector3d& pt);
	CART3D_COMMON_API cvector3d rt_dir(const cmatrix4d& rt, const cvector3d& pt);
	CART3D_COMMON_API bool equal_scalar(cfloat a, cfloat b, cfloat eps = 1e-6);
	CART3D_COMMON_API unsigned xorshift_rnd(unsigned n = ~0u);
	CART3D_COMMON_API cfloat uniform_rnd();
	CART3D_COMMON_API double uniform_rnd(double rd);
	CART3D_COMMON_API float uniform_rnd(float rd);
	CART3D_COMMON_API int uniform_rnd(int rd);
	CART3D_COMMON_API char uniform_rnd(char rd);
	CART3D_COMMON_API unsigned char uniform_rnd(unsigned char rd);
	CART3D_COMMON_API unsigned uniform_rnd(unsigned rd);
	CART3D_COMMON_API short uniform_rnd(short rd);
	CART3D_COMMON_API long long uniform_rnd(long long rd);
	CART3D_COMMON_API cvetor3uc hsl_to_rgb(int sid);
}


#endif

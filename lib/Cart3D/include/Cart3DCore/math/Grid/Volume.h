#ifndef CART3D_MATH_VOLUME_H
#define CART3D_MATH_VOLUME_H

#include <memory>
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS Volume
	{
	public:
		Volume(unsigned int udim=0, unsigned int vdim=0, unsigned int wdim=0);
		virtual ~Volume();
	public:
		virtual const cvector3d& operator()(unsigned int u, unsigned int v, unsigned int w) const = 0;
		virtual cvector3d operator()(unsigned int u, unsigned int v, unsigned int w) = 0;
	public:
		unsigned int udim() const;
		unsigned int vdim() const;
		unsigned int wdim() const;
		unsigned int size() const;
		unsigned int idx(unsigned int i, unsigned int j, unsigned int k)const;
	protected:
		unsigned int udim_, vdim_, wdim_;
	};



	class CART3D_MATH_CLASS UniformVolume:public Volume
	{
	public:
		UniformVolume(const cvector3d& minp, const cvector3d& scale,
			unsigned int udim = 0, unsigned int vdim = 0, unsigned int wdim = 0);
	public:
		const cvector3d& operator()(unsigned int u, unsigned int v, unsigned int w) const override;
		cvector3d operator()(unsigned int u, unsigned int v, unsigned int w)override;
	protected:
		cvector3d minp_;
		cvector3d scale_;
	};

	class CART3D_MATH_CLASS PtsVolume :public Volume
	{
	public:
		PtsVolume(const std::vector<cvector3d>& pts,
			unsigned int udim = 0, unsigned int vdim = 0, unsigned int wdim = 0);
	public:
		const cvector3d& operator()(unsigned int u, unsigned int v, unsigned int w) const override;
		cvector3d operator()(unsigned int u, unsigned int v, unsigned int w)override;
	protected:
		const std::vector<cvector3d>& pts_;
	};



	
	//²Î¿¼OpenVDB ÊµÏÖ
	class CART3D_MATH_CLASS PolygonPool
	{
	public:
		enum {
			POLYFLAG_EXTERIOR = 0x1,
			POLYFLAG_FRACTURE_SEAM = 0x2,
			POLYFLAG_SUBDIVIDED = 0x4
		};
		PolygonPool();
		PolygonPool(const size_t numQuads, const size_t numTriangles);
	public:
		void copy(const PolygonPool& rhs);
		void resetQuads(size_t size);
		void clearQuads();
		void resetTriangles(size_t size);
		void clearTriangles();
		const size_t& numQuads() const;
		cvector4i& quad(size_t n);
		const cvector4i& quad(size_t n) const;
		const size_t& numTriangles() const;
		cvector3i& triangle(size_t n);
		const cvector3i& triangle(size_t n) const;
		char& quadFlags(size_t n);
		const char& quadFlags(size_t n) const;
		char& triangleFlags(size_t n);
		const char& triangleFlags(size_t n) const;
		bool trimQuads(const size_t n, bool reallocate = false);
		bool trimTrinagles(const size_t n, bool reallocate = false);
	private:
		void operator=(const PolygonPool&) {}
		size_t mNumQuads, mNumTriangles;
		std::unique_ptr<cvector4i[]> mQuads;
		std::unique_ptr<cvector3i[]> mTriangles;
		std::unique_ptr<char[]> mQuadFlags, mTriangleFlags;
	};
}


#endif
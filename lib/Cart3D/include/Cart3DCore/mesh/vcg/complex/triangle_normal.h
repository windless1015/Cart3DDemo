#ifndef __VCGLIB_TRIANGLE_NORMAL
#define __VCGLIB_TRIANGLE_NORMAL
namespace vcg {
namespace tri {
	template <class FaceType>
	inline typename FaceType::CoordType TriangleNormal(FaceType const & f)
	{
		typename FaceType::CoordType v0 = f.cV(1)->cP() - f.cV(0)->cP();
		typename FaceType::CoordType v1 = f.cV(2)->cP() - f.cV(0)->cP();
		auto v = v0.cross(v1);
		v.normalize();
		return v;
	}
}
}

#endif
#pragma once
#ifndef CART3D_SIMILAR_GEODESIC_H
#define CART3D_SIMILAR_GEODESIC_H
#include <Cart3DToolsDefine.h>
#include "GeodesicUtil.h"
namespace Cart3D
{
	class CART3D_TOOLS_CLASS SimilarGeodesic
	{
	public:
		struct Window
		{
			cfloat dist;
			VH srcid;
			VH previd;
		};

		static void GeidesicDistance(
			const OpenTriMesh & m,
			const std::vector<VH> & sources,
			std::vector<Window>& dist);
	public:

		static cfloat GeodesicPath(const OpenTriMesh& m,
			const int se,
			const int dt,
			std::vector<cvector3d>& path,
			std::vector<int>& ids);

		
		static cfloat fast_path(const OpenTriMesh& m,
			const int se,
			const int dt,
			std::vector<cvector3d>& path,
			std::vector<int>& ids);

		static cfloat fast_path(const GeodesicUtil& m,
			const int se,
			const int dt,
			std::vector<int>& ids);
	};
}

#endif // !CART3D_SIMILAR_GEODESIC_H

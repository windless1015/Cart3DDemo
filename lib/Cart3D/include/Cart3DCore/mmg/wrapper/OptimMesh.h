#pragma once

#ifndef FAST_MESH_H
#define FAST_MESH_H

#include <Util/EigenUtil.h>

namespace Cart3D
{
	struct OptimMesh
	{
	public:
		std::vector<cvector3d> pts;
		std::vector<cvector3i> tris;
	public:
		void generation_edges();
		std::vector<std::pair<int, int>> edges; //Éú³ÉÍø¸ñ
	public:
		void clear();
		void remove_degradation(double minlen = 0.0001);
	public:
		void ortho_mesh();
		void inv_ortho_mesh(const cvector3d&cent, double scale);
		bool has_ortho = false;
		double scale = 1;
		cvector3d cent{ 0,0,0 };
	public:


	};
}
#endif // !FAST_MESH_H

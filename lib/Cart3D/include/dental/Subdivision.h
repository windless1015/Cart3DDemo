// Copyright 2011-2022 the Polygon Mesh Processing Library developers.
// Distributed under a MIT-style license, see LICENSE.txt for details.

#pragma once

#include "dentalmesh/SurfaceMesh.h"

namespace pmp {
	class  TriMesh
	{
	public:
		struct  Face {
			int v[3];
			bool valid;
			Face() :valid(false) {}
			Face(const int& v0, const int& v1, const int& v2) :valid(true)
			{
				v[0] = v0; v[1] = v1; v[2] = v2;
			}
			Face(const int* v_) :valid(true)
			{
				std::memcpy(&v[0], v_, sizeof(int) * 3);
			}
			int& operator[] (int i) { return v[i]; }
			const int& operator[] (int i) const { return v[i]; }
			operator const int* () const { return &(v[0]); }
			operator const int* () { return &(v[0]); }
			operator int* () { return &(v[0]); }
			int indexof(int v_) const {
				return (v[0] == v_) ? 0 : (v[1] == v_) ? 1 : (v[2] == v_) ? 2 : -1;
			}

		};
	
	public:
		void need_neighbors();
		void need_across_edge();
		void need_adjacentfaces();
	public:
		std::vector<pmp::Point>                pVertex;
		std::vector<Face>                      pFace;
		std::vector<Face>                across_edge;
		std::vector<std::vector<int>>  adjacentfaces;
		std::vector< std::vector<int> > neighbors;
	};

	enum  SubdivType {
		SUBDIV_PLANAR,
		SUBDIV_LOOP,
		SUBDIV_LOOP_ORIG,
		SUBDIV_LOOP_NEW,
		SUBDIV_BUTTERFLY,
		SUBDIV_BUTTERFLY_MODIFIED
	};

	extern void SubdivMesh(
		std::vector<pmp::Point>& pts,
		std::vector<int>& tris,
		int numsub, SubdivType type = SUBDIV_LOOP);

} // namespace pmp

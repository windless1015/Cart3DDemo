#pragma once

#include "prelude.h"
#include "iterPool.h"
#include "rawmesh.h"
#include <vector>
#include "empty3d.h"

#define INVALID_ID uint(-1)
#include <mimalloc/include/mimalloc.h>
#include "topofwd.h"

struct TopoVert {
	uint                    ref;        // index to actual data
	void*                   data;       // algorithm specific handle

	cork_vector<Tptr> tris;  // triangles this vertex is incident on
	cork_vector<Eptr> edges;  // triangles this vertex is incident on
	TopoVert() {
		tris.reserve(8);			edges.reserve(8);
	}
};

struct TopoTri {
	uint                    ref;        // index to actual data
	void*                   data;       // algorithm specific handle

	Vptr                    verts[3];   // vertices of this triangle
	Eptr                    edges[3];   // edges of this triangle
	Vec3d                   m_normal;   
	bool                    degenerate; 

	TopoTri()
	{
		m_normal = Vec3d(0, 0, 0);
		degenerate = false;
		for (int i = 0; i < 3;i++)
		{
			edges[i] = nullptr;
			verts[i] = nullptr;
		}
	};
};

struct TopoEdge {
	void*                   data;       // algorithm specific handle
	Vptr                    verts[2];   // endpoint vertices
	cork_vector<Tptr>tris;
	~TopoEdge() {
		tris.reserve(2);
	}
};



struct CorkMesh::TopoCache {
	IterPool<TopoVert>    verts;
	IterPool<TopoEdge>    edges;
	IterPool<TopoTri>     tris;
	CorkMesh *mesh;
	TopoCache(CorkMesh *owner,bool needEdge = true);
	virtual ~TopoCache() {

	}

	// until commit() is called, the Mesh::verts and Mesh::tris
	// arrays will still contain garbage entries
	void commit();


	inline Vptr newVert()
	{
		uint        ref = (uint)mesh->verts.size();
		mesh->verts.push_back(CorkVertex());
		Vptr        v = verts.alloc(); // cache.verts
		v->ref = ref;
		return v;
	}

	inline Eptr newEdge()
	{
		Eptr        e = edges.alloc(); // cache.edges
		return e;
	}

	inline Tptr newTri()
	{
		uint        ref = (uint)mesh->tris.size();
		mesh->tris.push_back(Tri());
		Tptr        t = tris.alloc(); // cache.tris
		t->ref = ref;
		return t;
	}

	//// helpers to release bits and pieces
	//inline void freeVert(Vptr);
	//inline void freeEdge(Eptr);
	//inline void freeTri(Tptr);
	inline void freeVert(Vptr v)
	{
		verts.free(v);
	}

	inline void freeEdge(Eptr e)
	{
		edges.free(e);
	}

	inline void freeTri(Tptr t)
	{
		tris.free(t);
	}

	//// helper to delete geometry in a structured way
	//inline void deleteTri(Tptr);

	//// helper to flip triangle orientation
	//inline void flipTri(Tptr);
	inline void deleteTri(Tptr tri)
	{
		// first, unhook the triangle from its faces
		for (uint k = 0; k < 3; k++) {
			Vptr            v = tri->verts[k];
			if (v != nullptr)
			{
				if (v->tris.size() == 0)
				{
					freeVert(v);
					tri->verts[k] = nullptr;
				}
				else
					erase(v->tris,tri);
			}
			
			
			Eptr            e = tri->edges[k];
			if (e != nullptr)
			{
				if (e->tris.size() == 0)
					tri->edges[k] = nullptr;
				else
					erase(e->tris,tri);
			}			
		}
		// now, let's check for any edges which no longer border triangles
		for (uint k = 0; k < 3; k++) {
			Eptr            e = tri->edges[k];
			if (e ==nullptr)
				continue;
			if (e->tris.size() == 0) {
				// delete edge
				// unhook from vertices
				Vptr        v0 = e->verts[0];
				erase(v0->edges,e);
				Vptr        v1 = e->verts[1];
				erase(v1->edges,e);
				freeEdge(e);
			}
		}
		// now, let's check for any vertices which no longer border triangles
		/*	for (uint k = 0; k < 3; k++) {
				Vptr            v = tri->verts[k];
				if (v==nullptr)
				continue;
				if (v->tris.size() == 0) {
				freeVert(v);
				}
				}*/
		// finally, release the triangle
		freeTri(tri);
	}

	inline void flipTri(Tptr t)
	{
		std::swap(t->verts[0], t->verts[1]);
		std::swap(t->edges[0], t->edges[1]);
		std::swap(mesh->tris[t->ref].v[0], mesh->tris[t->ref].v[1]);
	}

private:
	void init(bool needEdges);

	// support structure for cache construction
	struct TopoEdgePrototype
	{
		uint vid;
		cork_vector<Tptr> tris;
		TopoEdgePrototype() {}
		TopoEdgePrototype(uint v) : vid(v) { tris.reserve(2); }
	};

	inline TopoEdgePrototype& getTopoEdgePrototype(
		uint a, uint b,
		std::vector< cork_vector<TopoEdgePrototype>> &prototypes
		)
	{
		uint N = (uint)prototypes[a].size();
		for (uint i = 0; i < N; i++) {
			if (prototypes[a][i].vid == b)
				return prototypes[a][i];
		}
		prototypes[a].push_back(TopoEdgePrototype(b));
		return prototypes[a][N];
	}
};


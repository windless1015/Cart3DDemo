#pragma once
#include "intersection.h"
#include "topofwd.h"
// should deal with via pointers
#include <vector>
#include <tbb/tbb.h>
class CorkMesh::TriangleProblem
{
public:
	TriangleProblem() {}
	~TriangleProblem() {}

	void init(IsctProblem *iprob, Tptr t);

private: // may actually not add edge, but instead just hook up endpoint
	void addEdge(IsctProblem *iprob, IVptr iv, Tptr tri_key);
	void addEdge(IsctProblem *iprob, OVptr ov, Tptr tri_key);

	void addBoundaryHelper(Eptr edge, IVptr iv);

public:

	IVptr addInteriorEndpoint(IsctProblem *iprob, Eptr edge, GluePt glue, const Vec3d &coord);
	IVptr addEdgeInteriorEndpoint(IsctProblem *iprob, Eptr edge, GluePt
		glue, int oeindex, const Vec3d &coord);
	IVptr addVertInteriorEndpoint(IsctProblem *iprob, Vptr Vert, GluePt glue, const Vec3d &coord);
	IVptr addEdgeVertInteriorEndpoint(IsctProblem *iprob, Eptr edge, GluePt
		glue, int ovindex, int oeindex, const Vec3d &coord);

	void edgeTri_coplane_addEdge(IsctProblem *iprob, IVptr iv1, IVptr iv2, Tptr tri_key, Eptr edge_key);
	void edgeTri_coplane_addEdge(IsctProblem *iprob, IVptr iv1, OVptr ov2, Tptr tri_key, Eptr edge_key);
	void edgeTri_coplane_addEdge(IsctProblem *iprob, OVptr ov1, IVptr iv2, Tptr tri_key, Eptr edge_key);
	void edgeTri_coplane_addEdge(IsctProblem *iprob, OVptr iv1, OVptr ov2, Tptr tri_key, Eptr edge_key);

	bool getIvptr(const Vec3d &coord, IVptr &iv);
	bool getOvptr(const Vec3d &coord, OVptr &ov);

	// specify the other triangle cutting this one, the edge cut,
	// and the resulting point of intersection
	void repairBoundary(IVptr iv, Eptr edge);
	void addBoundaryEndpoint(IsctProblem *iprob, Tptr tri_key, Eptr edge, IVptr iv);
	void addEdgeBoundaryEndpoint(IsctProblem *iprob, Eptr edge, IVptr &iv);

	void addEdgeEdge(IsctProblem *iprob, IVptr iv, Tptr tri_key);
	void addEdgeEdge(IsctProblem *iprob, OVptr iv, Tptr tri_key);

	void addVertiexEdge(IsctProblem *iprob, Eptr edge, GluePt glue, IVptr iv);
	void addVertiexEdge(IsctProblem *iprob, Eptr edge, GluePt glue, OVptr iv);

	IVptr addBoundaryEndpoint(IsctProblem *iprob, Tptr tri_key, Eptr edge, const Vec3d &coord, GluePt glue);
	// Should only happen for manually inserted split points on
	// edges, not for points computed via intersection...
	IVptr addBoundaryPointAlone(IsctProblem *iprob, Eptr edge, const Vec3d &coord, GluePt glue);
	void addInteriorPoint(IsctProblem *iprob, const Vec3d &coord, Tptr t0, Tptr t1, GluePt glue);
	// run after we've accumulated all the elements
	void consolidate(IsctProblem *iprob);
	bool subdivide(CorkMesh::IsctProblem *iprob);
	//bool subdivide(CorkMesh::IsctProblem *iprob,tbb::spin_mutex& mutex);

private:
	void subdivideEdge(IsctProblem *iprob, GEptr ge, std::vector<GEptr> &edges);

public: // data
	cork_vector<IVptr>      iverts;
	cork_vector<IEptr>      iedges;
	// original triangle elements
	OVptr                   overts[3];
	OEptr                   oedges[3];

	cork_vector<GTptr>      gtris;

	Tptr                    the_tri;

	bool                    ifgood;


};


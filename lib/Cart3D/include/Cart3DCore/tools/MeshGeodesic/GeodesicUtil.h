#pragma once
#ifndef CART3D_GEODEISC_UTIL_H
#define CART3D_GEODEISC_UTIL_H

#include <Cart3DToolsDefine.h>
#include "Util/TreeUtil.h"
#include "Util/OpenMeshUtil.h"
namespace Cart3D
{
	class CART3D_TOOLS_CLASS GeodesicUtil
	{
		friend class ExactGeodesic;
		friend class SmoothGeodesic;
		friend class FastGeodesic;
		friend class SimilarGeodesic;
		friend class ICHGeodesicDistance;
	public:
		GeodesicUtil(OpenTriMesh& Tri_mesh);
		~GeodesicUtil();
	public:
		void InImprovedGeodesicBase(OpenTriMesh& Tri_mesh);
		struct GeoEdge
		{
			int indexOfLeftVert;
			int indexOfRightVert;
			int indexOfOppositeVert;
			int indexOfLeftEdge;
			int indexOfRightEdge;
			int indexOfReverseEdge;
			int indexOfFrontFace;
			cfloat mlength;
			cfloat xOfPlanarCoordOfOppositeVert;
			cfloat yOfPlanarCoordOfOppositeVert;
			GeoEdge() :
				indexOfOppositeVert(-1),
				indexOfLeftEdge(-1),
				indexOfRightEdge(-1)
			{
			}
		};
		struct GeoFace
		{
			int verts[3];
			GeoFace() = default;
			GeoFace(int x, int y, int z)
			{
				verts[0] = x;
				verts[1] = y;
				verts[2] = z;
			}
			int& operator[](int index)
			{
				return verts[index];
			}
			int operator[](int index) const
			{
				return verts[index];
			}
		};
		struct GeoVertex
		{
			int vid;
			std::vector<int> vvs;
		};
		void InitParam(std::vector<cvector3d>& vertpoints, std::vector<GeoFace>& faceindex);
		void Preprocess();
		int GetSubindexToVert(int root, int neigh) const;
		inline int GetNumOfVerts()  const { return (int)m_Verts.size(); };
		inline int GetNumOfFaces() const { return (int)m_Faces.size(); };
		inline const cvector3d& Vert(int vertIndex) const { return m_Verts[vertIndex]; };
		inline const GeoFace& Face(int faceIndex) const { return m_Faces[faceIndex]; };
		inline const GeoEdge& Edge(int edgeIndex) const { return m_Edges[edgeIndex]; };
		inline const std::vector<std::pair<int, cfloat> >& Neigh(int root) const { return m_NeighsAndAngles[root]; };
		int IncidentVertex(int edgeIndex) const;
		cfloat ProportionOnEdgeByImage(int edgeIndex, cfloat x, cfloat y) const;
		cfloat ProportionOnEdgeByImageAndPropOnLeftEdge(int edgeIndex, cfloat x, cfloat y, cfloat proportion) const;
		cfloat ProportionOnEdgeByImageAndPropOnRightEdge(int edgeIndex, cfloat x, cfloat y, cfloat proportion) const;
		cfloat ProportionOnLeftEdgeByImage(int edgeIndex, cfloat x, cfloat y, cfloat proportion) const;
		cfloat ProportionOnRightEdgeByImage(int edgeIndex, cfloat x, cfloat y, cfloat proportion) const;
		cfloat ProportionOnEdgeByImage(int edgeIndex, cfloat x1, cfloat y1, cfloat x2, cfloat y2) const;
		void GetPointByRotatingAround(int edgeIndex, cfloat leftLen, cfloat rightLen, cfloat& xNew, cfloat& yNew) const;
		void GetPointByRotatingAroundLeftChildEdge(int edgeIndex, cfloat x, cfloat y, cfloat& xNew, cfloat& yNew) const;
		void GetPointByRotatingAroundRightChildEdge(int edgeIndex, cfloat leftLen, cfloat rightLen, cfloat& xNew, cfloat& yNew) const;
		cfloat DistanceToIncidentAngle(int edgeIndex, cfloat x, cfloat y) const;
		int GetNumOfEdges() const;
		int GetNumOfValidDirectedEdges() const;
		int GetNumOfTotalUndirectedEdges() const;
		int GetNumOfGenera() const;
		int GetNumOfIsolated() const;
		int GetNumOfComponents() const;
		int GetNumOfHoles() const;
		bool IsConvexVert(int index) const;
		bool IsClosedModel() const;
		bool IsExtremeEdge(int edgeIndex) const;
		bool IsStartEdge(int edgeIndex) const;
		cvector3d ComputeShiftPoint(int indexOfVert) const;
		inline cvector3d ComputeShiftPoint(int indexOfVert, cfloat epsilon) const;
		static cvector3d CombinePointAndNormalTo(const cvector3d& pt, const cvector3d& normal);
		static cvector3d CombineTwoNormalsTo(const cvector3d& pt1, cfloat coef1, const cvector3d& pt2, cfloat coef2);
		void CreateEdgesFromVertsAndFaces();
		void CollectAndArrangeNeighs();
		void ComputeAnglesAroundVerts();
		void ComputePlanarCoordsOfIncidentVertForEdges();
		bool fLocked;
		std::vector<cvector3d>     m_Verts;
		std::vector<GeoFace>   m_Faces;
		std::vector<GeoEdge>   m_Edges;
		std::vector<std::vector<int>>   m_vv;
		int m_nHoles;
		int m_nIsolatedVerts;
		std::vector<std::vector<std::pair<int, cfloat> > > m_NeighsAndAngles;
		std::vector<bool>  m_FlagsForCheckingConvexVerts;
	};
}



#endif
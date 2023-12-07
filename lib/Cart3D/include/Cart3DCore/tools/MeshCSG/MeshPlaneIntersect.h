#pragma once
#include <Cart3DToolsDefine.h>
#include <MeshCSG/MeshCSGUtil.h>
#include <csgmesh/CSGMesh.h>
namespace Cart3D
{
	class MeshPlaneIntersection;
	struct CART3D_TOOLS_CLASS MPINode
	{
		std::shared_ptr<MeshPlaneIntersection> tool;
	};

	class CART3D_TOOLS_CLASS MeshPlaneIntersection {
	public:
		typedef std::pair<int, int> Edge;
		typedef std::vector<Edge> EdgePath;
		struct FreeEdgePath {
			Edge StartEdge, EndEdge;
			std::vector<int> vertices;
			bool isUsed = false;
		};
	public:
		MeshPlaneIntersection(
			const std::vector<cvector3d>& vertices,
			const std::vector<cvector3i>& faces);

		static std::shared_ptr<MPINode> create(const CSGMesh& mesh);

		std::vector<Path3D> Intersect(const Planer& plane) const;
		std::vector<Path3D> Clip(const Planer& plane) const;
	private:
		const std::vector<cvector3d>& vertices;
		const std::vector<cvector3i>& faces;
		static std::vector<Path3D> _Execute(const MeshPlaneIntersection& mesh, const Planer& plane,
			const bool isClip);
		static std::vector<EdgePath> EdgePaths(const std::vector<cvector3i>& faces,
			const std::vector<cfloat>& vertexOffsets);
		static std::vector<Path3D> ConstructGeometricPaths(const MeshPlaneIntersection& mesh,
			const std::vector<EdgePath>& edgePaths,
			const std::vector<cfloat>& vertexOffsets);
		static const std::vector<cfloat> VertexOffsets(const std::vector<cvector3d>& vertices,
			const Planer& plane);
		static cfloat VertexOffset(const cvector3d& vertex, const Planer& plane);
		typedef std::map<Edge, int> CrossingFaceMap;
		static CrossingFaceMap CrossingFaces(const std::vector<cvector3i>& faces,
			const std::vector<cfloat>& vertexOffsets);
		static void AlignEdge(Edge& edge);
		static EdgePath GetEdgePath(CrossingFaceMap& crossingFaces);
		static bool GetNextPoint(CrossingFaceMap::const_iterator& currentFace,
			CrossingFaceMap& crossingFaces);
		static bool InsertConnectingEdgePath(const std::vector<EdgePath>& edgePaths,
			std::vector<bool>& usedPaths, EdgePath& currentChain);
		static void ChainEdgePaths(std::vector<EdgePath>& edgePaths);
		static std::vector<Edge> FreeEdges(const std::vector<cvector3i>& faces,
			const std::vector<cfloat>& vertexOffsets);
		static std::vector<EdgePath> FreeEdgePaths(const std::vector<Edge>& freeEdges,
			const std::vector<cfloat> vertexOffsets);
		static bool ExtendFreeEdgePath(FreeEdgePath& path, const std::vector<Edge>& freeEdges,
			std::vector<bool>& usedFreeEdges, const std::vector<cfloat> vertexOffsets);
	};

}
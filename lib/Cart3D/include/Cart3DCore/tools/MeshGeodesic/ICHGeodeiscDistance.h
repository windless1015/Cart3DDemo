#ifndef CART3D_ICHGEODESIC_DISTANCE_H
#define CART3D_ICHGEODESIC_DISTANCE_H

#include <Cart3DToolsDefine.h>
#include <queue>
#include "GeodesicUtil.h"
namespace Cart3D
{
	class CART3D_TOOLS_CLASS ICHGeodesicDistance
	{
	public:
		struct CART3D_TOOLS_CLASS InfoAtVertex
		{
			bool fParentIsPseudoSource;
			char birthTime;
			int indexOfParent; 
			int indexOfRootVertOfParent;
			int level;
			cfloat disUptodate;
			cfloat entryProp;
			InfoAtVertex()
			{
				birthTime = -1;
				disUptodate = FLT_MAX;
			}
		};
		struct CART3D_TOOLS_CLASS QuoteInfoAtVertex
		{
			char birthTime;
			int indexOfVert;
			cfloat disUptodate;
			bool operator<(const QuoteInfoAtVertex& another) const
			{
				if (disUptodate == another.disUptodate)
					return indexOfVert > another.indexOfVert;
				return disUptodate > another.disUptodate;
			}

			
			QuoteInfoAtVertex() {}
			QuoteInfoAtVertex(char birthTime, int indexOfVert, cfloat disUptodate)
			{
				this->birthTime = birthTime;
				this->indexOfVert = indexOfVert;
				this->disUptodate = disUptodate;
			}
		};
		struct CART3D_TOOLS_CLASS InfoAtAngle
		{
			char birthTime;
			cfloat disUptodate;
			cfloat entryProp;
			InfoAtAngle()
			{
				birthTime = -1;
				disUptodate = FLT_MAX;
			}
		};
		struct CART3D_TOOLS_CLASS Window
		{
			bool fIsOnLeftSubtree;
			bool fParentIsPseudoSource;
			bool fDirectParentEdgeOnLeft; 
			bool fDirectParenIsPseudoSource; 
			char birthTimeOfParent;
			int indexOfParent;
			int indexOfRoot;
			int indexOfCurEdge;
			int level;
			cfloat disToRoot;
			cfloat proportions[2];
			cfloat entryPropOfParent;
			cfloat leftLen;
			cfloat rightLen;
			cfloat xUponUnfolding;
			cfloat yUponUnfolding;
		};
		struct CART3D_TOOLS_CLASS QuoteWindow
		{
			Window* pWindow;
			cfloat disUptodate;
			bool operator<(const QuoteWindow& another) const
			{
				if (disUptodate == another.disUptodate)
					return pWindow > another.pWindow;
				return disUptodate > another.disUptodate;
			}
		};
	public:
		ICHGeodesicDistance(const GeodesicUtil& inputModel);
		~ICHGeodesicDistance();
	public:
		void GeodesicDistance(const OpenTriMesh& mesh,
			const std::vector<int>& src,std::vector<cfloat>& distance);
	private:
		bool UpdateTreeDepthBackWithChoice(
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>&  angleinfo);
		cfloat GetMinDisOfWindow(const Window& w) const;
		bool CheckValidityOfWindow(
			std::vector<InfoAtVertex>& vinfo,
			Window& w);
		void BuildSequenceTree(
			std::vector<int>& dstneibor,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>&  angleinfo);
		void AddIntoQueueOfWindows(
			std::set<QuoteWindow>& winque, QuoteWindow& quoteW);
		void AddIntoQueueOfPseudoSources(
			std::set<QuoteInfoAtVertex>& pseudoque,
			const QuoteInfoAtVertex& quoteOfPseudoSource);
		void BackTrace(
			const OpenTriMesh& mesh,
			std::vector<InfoAtVertex>& vinfo,
			int indexOfSourceVert,
			int indexOfDesVert,
			std::vector<cvector3d> &OutResults,
			std::vector<int> &OutIndex,
			std::vector<bool> &OutIndexType);
		void ComputeChildrenOfSource(
			const std::vector<int>& source,
			std::vector<int>& cache,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque);
		void ComputeChildrenOfPseudoSourceFromPseudoSource(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void ComputeChildrenOfPseudoSourceFromWindow(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void ComputeChildrenOfWindow(
			QuoteWindow&               quoteParentWindow,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>&  angleinfo,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque);
		void ComputeChildrenOfPseudoSource(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void CreateIntervalChildOfPseudoSource(
			int source,
			int subIndexOfIncidentEdge,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque);
		void FillVertChildOfPseudoSource(
			int source,
			int subIndexOfVert,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteInfoAtVertex>& pseudoque);
		void ComputeLeftTrimmedChildWithParent(
			const Window& w,
			cfloat disToAngle,
			std::vector<InfoAtAngle>&  angleinfo,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque);
		void ComputeRightTrimmedChildWithParent(
			const Window& w,
			cfloat disToAngle,
			std::vector<InfoAtAngle>&  angleinfo,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque);

		void ComputeTheOnlyLeftChild(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyLeftTrimmedChild(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyRightChild(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyRightTrimmedChild(
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
	private:
		const GeodesicUtil&     m_Model;
		bool IsTooNarrowWindow(const Window& w) const
		{
			const cfloat LENGTH_EPSILON_CONTROL = 1e-6F;
			return w.proportions[1] - w.proportions[0] < LENGTH_EPSILON_CONTROL;
		}
	};
}


#endif // 

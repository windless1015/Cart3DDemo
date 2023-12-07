#pragma once
#ifndef CART3D_FAST_GEODEISC_H
#define CART3D_FAST_GEODEISC_H
#include "GeodesicUtil.h"
#include <queue>
namespace Cart3D
{
	class CART3D_TOOLS_CLASS FastGeodesic
	{
	public:
		FastGeodesic(const GeodesicUtil& inputModel);
		~FastGeodesic();
	public:
		void GeodesicPath(const OpenTriMesh& mesh,
			std::vector<cvector3d>& OutResults,
			std::vector<int>& OutIndex,
			std::vector<bool>& OutIndexType,
			int indexOfSourceVert, int indexOfDesVert,int smooth_iter=3);
	private:
		struct CART3D_TOOLS_CLASS InfoAtVertex
		{
			bool fParentIsPseudoSource;
			char birthTime;
			int indexOfParent;
			int indexOfRootVertOfParent;
			bool geodesic_pass;
			bool has_call_geodesic;
			int level;
			cfloat disUptodate;
			cfloat entryProp;
			InfoAtVertex()
			{
				birthTime = -1;
				disUptodate = DBL_MAX;
				geodesic_pass = false;
				has_call_geodesic = false;
			}
		};
		struct CART3D_TOOLS_CLASS QuoteInfoAtVertex
		{
			char birthTime;
			int indexOfVert;
			cfloat disUptodate;
			bool operator<(const QuoteInfoAtVertex& another) const
			{
				if (disUptodate != another.disUptodate)
					return disUptodate > another.disUptodate;
				else
					return indexOfVert > another.indexOfVert;
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
				disUptodate = 1e38;
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
			std::shared_ptr<Window> pWindow;
			cfloat disUptodate;
			bool operator<(const QuoteWindow& another) const
			{
				if (disUptodate != another.disUptodate)
					return disUptodate >  another.disUptodate;
				else
					return pWindow->indexOfCurEdge > another.pWindow->indexOfCurEdge;
			}
		};
		bool UpdateTreeDepthBackWithChoice(
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo);
		cfloat GetMinDisOfWindow(const Window& w) const;
		bool CheckValidityOfWindow(
			std::vector<InfoAtVertex>& vinfo,
			Window& w);
		void BuildSequenceTree(
			int source,
			std::vector<int>& dstneibor,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo);
		void AddIntoQueueOfWindows(
			std::priority_queue<QuoteWindow>& winque, QuoteWindow& quoteW);
		void AddIntoQueueOfPseudoSources(
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			const QuoteInfoAtVertex& quoteOfPseudoSource);
		void BackTrace(
			const OpenTriMesh& mesh,
			std::vector<InfoAtVertex>& vinfo,
			int indexOfSourceVert,
			int indexOfDesVert,
			std::vector<cvector3d>& OutResults,
			std::vector<int>& OutIndex,
			std::vector<bool>& OutIndexType);
		void ComputeChildrenOfSource(
			int source,
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque);
		void ComputeChildrenOfPseudoSourceFromPseudoSource(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void ComputeChildrenOfPseudoSourceFromWindow(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void ComputeChildrenOfWindow(
			QuoteWindow& quoteParentWindow,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque);
		void ComputeChildrenOfPseudoSource(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque,
			int indexOfParentVertex);
		void CreateIntervalChildOfPseudoSource(
			int source,
			int subIndexOfIncidentEdge,
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque);
		void FillVertChildOfPseudoSource(
			int source,
			int subIndexOfVert,
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteInfoAtVertex>& pseudoque);
		void ComputeLeftTrimmedChildWithParent(
			const Window& w,
			cfloat disToAngle,
			std::vector<InfoAtAngle>& angleinfo,
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque);
		void ComputeRightTrimmedChildWithParent(
			const Window& w,
			cfloat disToAngle,
			std::vector<InfoAtAngle>& angleinfo,
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque);
		void ComputeTheOnlyLeftChild(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyLeftTrimmedChild(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyRightChild(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		void ComputeTheOnlyRightTrimmedChild(
			std::vector<InfoAtVertex>& vinfo,
			std::priority_queue<QuoteWindow>& winque,
			const Window& w, cfloat disToAngle);
		bool IsGeodesicPass(const std::vector<InfoAtVertex>& vinfo,const GeodesicUtil::GeoEdge& pass);
	private:
		const GeodesicUtil& m_Model;
		bool IsTooNarrowWindow(const Window& w) const
		{
			const cfloat LENGTH_EPSILON_CONTROL = std::numeric_limits<cfloat>::epsilon();
			return w.proportions[1] - w.proportions[0] < LENGTH_EPSILON_CONTROL;
		}
	};

}

#endif
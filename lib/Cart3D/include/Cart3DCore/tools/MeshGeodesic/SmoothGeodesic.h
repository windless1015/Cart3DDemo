#pragma once
#ifndef CART3D_SMOOTH_GEODEISC_H
#define CART3D_SMOOTH_GEODEISC_H
#include "GeodesicUtil.h"
namespace Cart3D
{
	class CART3D_TOOLS_CLASS SmoothGeodesic
	{
	public:
		SmoothGeodesic(const GeodesicUtil& inputModel);
		~SmoothGeodesic();
	public:
		void GeodesicPath(const OpenTriMesh& mesh,
			std::vector<cvector3d>& OutResults,
			std::vector<int>& OutIndex,
			std::vector<bool>& OutIndexType,
			int indexOfSourceVert, int indexOfDesVert,int smooth_iter=3);

	private:
		struct InfoAtVertex
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
		struct QuoteInfoAtVertex
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
			QuoteInfoAtVertex() = default;
			QuoteInfoAtVertex(char birthTime, int indexOfVert, cfloat disUptodate)
			{
				this->birthTime = birthTime;
				this->indexOfVert = indexOfVert;
				this->disUptodate = disUptodate;
			}
		};
		struct  InfoAtAngle
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
		struct  Window
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
					return disUptodate > another.disUptodate;
				else
					return pWindow->indexOfCurEdge > another.pWindow->indexOfCurEdge;
			}
		};
		bool UpdateTreeDepthBackWithChoice(
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo);
		cfloat GetMinDisOfWindow(const Window& w) const;
		bool CheckValidityOfWindow(
			std::vector<InfoAtVertex>& vinfo,
			Window& w);
		void BuildSequenceTree(
			int source,
			std::vector<int>& dstneibor,
			std::set<QuoteWindow>& winque,
			std::set<QuoteInfoAtVertex>& pseudoque,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo);
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
			std::vector<cvector3d>& OutResults,
			std::vector<int>& OutIndex,
			std::vector<bool>& OutIndexType);
		void ComputeChildrenOfSource(
			int source,
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
			QuoteWindow& quoteParentWindow,
			std::vector<InfoAtVertex>& vinfo,
			std::vector<InfoAtAngle>& angleinfo,
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
			std::vector<InfoAtAngle>& angleinfo,
			std::vector<InfoAtVertex>& vinfo,
			std::set<QuoteWindow>& winque);
		void ComputeRightTrimmedChildWithParent(
			const Window& w,
			cfloat disToAngle,
			std::vector<InfoAtAngle>& angleinfo,
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
		bool IsGeodesicPass(const std::vector<InfoAtVertex>& vinfo,const GeodesicUtil::GeoEdge& pass);
	private:
		const GeodesicUtil& m_Model;
		bool IsTooNarrowWindow(const Window& w) const
		{
			const cfloat LENGTH_EPSILON_CONTROL = 1e-6;
			return w.proportions[1] - w.proportions[0] < LENGTH_EPSILON_CONTROL;
		}
	};

}

#endif
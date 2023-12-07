#include "boolean.h"
#define REAL double
typedef REAL *vertex;

namespace CorkMap
{
	struct oriTri
	{
		oriTri(){}
		oriTri(const int &a, const int &b, const int &c){ v[0] = a; v[1] = b; v[2] = c; }

		int v[3];
		int otherVert;
		Vec3d n;
		bool operator == (const oriTri &ori)const
		{
			if (v[0] == ori.v[0] && v[1] == ori.v[1] && v[2] == ori.v[2]) return true;
			if (v[0] == ori.v[0] && v[1] == ori.v[2] && v[2] == ori.v[1]) return true;

			if (v[0] == ori.v[1] && v[1] == ori.v[0] && v[2] == ori.v[2]) return true;
			if (v[0] == ori.v[1] && v[1] == ori.v[2] && v[2] == ori.v[0]) return true;

			if (v[0] == ori.v[2] && v[1] == ori.v[0] && v[2] == ori.v[1]) return true;
			if (v[0] == ori.v[2] && v[1] == ori.v[1] && v[2] == ori.v[0]) return true;
			return false;
		}
	};
}

class CorkMesh::CorkMeshToolFunc
{
public:
	//基本函数
	static byte getBoolCode(const int &tid, const CorkMesh* mesh);
	static bool triHasVert(uint v, Tri t);
	static int findOpp(int tid, const CorkMesh* mesh,const int &startVid, const int &endVid,bool &reliable);
	//调用triangle里面的判断函数来判断点和面片的位置
	static REAL         corkOrient3D(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	static Orientation  corkOrient3DEnum(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	static Orientation  coplanarOrient3D(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	//边上的面片进行排序
	static bool orderFaceAroundEdge(const std::vector<int> &adjFaces,
		std::vector<int> &order,const int &startVid,const int &endVid,const CorkMesh* mesh);
	static bool loopOriOrder(const CorkMesh* mesh, const std::vector<CorkMap::oriTri> &vecOriTri, const int &ps, const int &pd, std::vector<int> &order);
	//freeCut特定的函数
	static void findShells(std::vector< std::vector<int> > &shells, const CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);
	static bool findHoles(const std::vector< std::vector<int> > &shells, CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);
	static bool isPlaneNoramlDir(const Vec3d &planeNormal, const std::vector<uint> &component, uint &best_tid, const Vec3d &planePnt, const CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);

	//判断是否是相交边
	static void judgeEdgeIsIsctComplex(CorkMesh* mesh, EGraphEntry<BoolProblem::BoolEdata>& entry, const int &startVid, const int &endVid);
	/*
	  同一个part的两个面片的原始相同，直接拿原始面片为mainTid
	  判断来自另一个part上的两个面片（其原始面片不相同）上不属于相交边的另一个点
	  是否和mainTid的位置关系是 “一上一下”，如果是的话，返回true，不是的话返回
	  false，表示可疑继续判断
	*/
	static bool judgeIsIsctByTwoTrisInMainTri(
		const int&tid0, const int&tid1, const int &mainTid, const CorkMesh* mesh,const int &startVid,const int &endVid,
		REAL &a1, REAL& a2, bool &reliable);
	/*
	  判断两个面片原始三角形是否是相交关系
	  主要判断一个三角形上的三个点和当前三角形的位置关系
	  tid0为基准三角形，取tid1的三个点进行判断
	*/
	static bool judgeIsIsctByTwoTri(const int&tid0, const int&tid1, const CorkMesh* mesh);

	//查找共面三角形，并且判断共面三角形之间的法向是否相同，赋值共面三角形不同的标签
	static void findDoubleFaces(CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache, std::vector<std::vector<int>>& doubleFaces);
};

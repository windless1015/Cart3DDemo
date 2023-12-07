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
	//��������
	static byte getBoolCode(const int &tid, const CorkMesh* mesh);
	static bool triHasVert(uint v, Tri t);
	static int findOpp(int tid, const CorkMesh* mesh,const int &startVid, const int &endVid,bool &reliable);
	//����triangle������жϺ������жϵ����Ƭ��λ��
	static REAL         corkOrient3D(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	static Orientation  corkOrient3DEnum(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	static Orientation  coplanarOrient3D(const int &a, const int &b, const int &c, const int &d, const CorkMesh* mesh);
	//���ϵ���Ƭ��������
	static bool orderFaceAroundEdge(const std::vector<int> &adjFaces,
		std::vector<int> &order,const int &startVid,const int &endVid,const CorkMesh* mesh);
	static bool loopOriOrder(const CorkMesh* mesh, const std::vector<CorkMap::oriTri> &vecOriTri, const int &ps, const int &pd, std::vector<int> &order);
	//freeCut�ض��ĺ���
	static void findShells(std::vector< std::vector<int> > &shells, const CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);
	static bool findHoles(const std::vector< std::vector<int> > &shells, CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);
	static bool isPlaneNoramlDir(const Vec3d &planeNormal, const std::vector<uint> &component, uint &best_tid, const Vec3d &planePnt, const CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache);

	//�ж��Ƿ����ཻ��
	static void judgeEdgeIsIsctComplex(CorkMesh* mesh, EGraphEntry<BoolProblem::BoolEdata>& entry, const int &startVid, const int &endVid);
	/*
	  ͬһ��part��������Ƭ��ԭʼ��ͬ��ֱ����ԭʼ��ƬΪmainTid
	  �ж�������һ��part�ϵ�������Ƭ����ԭʼ��Ƭ����ͬ���ϲ������ཻ�ߵ���һ����
	  �Ƿ��mainTid��λ�ù�ϵ�� ��һ��һ�¡�������ǵĻ�������true�����ǵĻ�����
	  false����ʾ���ɼ����ж�
	*/
	static bool judgeIsIsctByTwoTrisInMainTri(
		const int&tid0, const int&tid1, const int &mainTid, const CorkMesh* mesh,const int &startVid,const int &endVid,
		REAL &a1, REAL& a2, bool &reliable);
	/*
	  �ж�������Ƭԭʼ�������Ƿ����ཻ��ϵ
	  ��Ҫ�ж�һ���������ϵ�������͵�ǰ�����ε�λ�ù�ϵ
	  tid0Ϊ��׼�����Σ�ȡtid1������������ж�
	*/
	static bool judgeIsIsctByTwoTri(const int&tid0, const int&tid1, const CorkMesh* mesh);

	//���ҹ��������Σ������жϹ���������֮��ķ����Ƿ���ͬ����ֵ���������β�ͬ�ı�ǩ
	static void findDoubleFaces(CorkMesh* mesh, EGraphCache<BoolProblem::BoolEdata>& ecache, std::vector<std::vector<int>>& doubleFaces);
};

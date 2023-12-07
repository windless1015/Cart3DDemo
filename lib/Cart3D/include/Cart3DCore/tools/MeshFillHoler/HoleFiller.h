#ifndef CART3D_TOOLS_HOLEFILLER_H
#define CART3D_TOOLS_HOLEFILLER_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{

	/*
	 * @file  HoleFiller.h
	 * @brief �����ṩ�������࣬�򵥲����㷨�Լ�ϸ�ڿ��Ʋ����㷨
	 * @detail �����ѵ�����������Ϣ�ָ����򵥲���������ʱΪ����Ӧ�߽�����������ȫ�����ڿ�Դ�㷨
	 * @class SimpleHoleFiller �ο�OpenFlipperʵ��
	 * @class OptimHoleFiller ��ȫ�Լ����һ�ֲ����㷨�����㷨������δ����....
	 */
	class CART3D_TOOLS_CLASS SimpleHoleFiller
	{
	public: 
		//�Կն��������ǻ�,ͨ��������Լ��������Լ��
		static bool fill_hole(OpenTriMesh& mesh, const HH& hh);
		static bool fill_hole(OpenTriMesh& mesh,const HH& hhs,
			std::vector<FH>& newfhs,std::vector<EH>& newedges);
	public:
		//���з���������ο׶�
		static bool fill_hole_earcut(OpenTriMesh& mesh, const HH& hh);
		static bool fill_hole_earcut(OpenTriMesh& mesh, const HH& hh,
			std::vector<FH>& newfhs, std::vector<EH>& newedges);
	public:
		//�Կ׶�����ϸ�֡���˳,Ŀǰֻ֧��С����
		static bool refine_and_fill_hole(OpenTriMesh& mesh, const HH& hh);
	};
	enum class OptimFillHoleStyle
	{
		MinArea, MaxAngleMinArea, MaxAngle
	};
	class CART3D_TOOLS_CLASS OptimHoleFiller
	{
	public:
		static bool sewUpLoopMaxAngle(OpenTriMesh& mesh,
			const std::vector<VH>& oppvhs,
			const std::vector<VH>& vhs, std::vector<int>& tris);
		static bool sewUpLoopMinArea(OpenTriMesh& mesh, const std::vector<VH>& vhs, std::vector<int>& tris);
	public:
		
		static bool auto_fill_hole(OpenTriMesh& mesh, bool refine, bool fair, OptimFillHoleStyle fhse= OptimFillHoleStyle::MaxAngleMinArea, int max_hole = 1024);

	};

}



#endif
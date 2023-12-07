#pragma once


#include <Util/EigenUtil.h>
using namespace Cart3D;

#ifndef uint
typedef unsigned int uint;
#endif

#ifndef byte
typedef unsigned char byte;
#endif


enum Orientation {
	POSITIVE = 0,
	NEGATIVE = 1,
	COPLANAR = 2,
	COLLINEAR = 3
};

//id0 第1个面片，cached
//id1 第2个面片，input
//pts，一些列的交点
//attr0  -1交于中心 0-2是顶点3-5是边（3对应0边）  三角形中0顶点点对应的那条边为是0边   交点pts在三角形0中的位置
//attr1  -1交于中心 0-2是顶点3-5是边                                                   交点pts在三角形1中的位置
struct isctInfo
{
	int id0;
	int id1;
	std::vector<cvector3d>  pts;
	std::vector<int>     attr0;
	std::vector<int>     attr1;
};

enum CommonIsctClassify {
	NOISCT,
	ISCT_COMMON,
	ISCT_COPLANAR,
	ISCT_TETRAHEDRON,
	ISCT_IN_TRI_EDGE,
	ISCT_IN_TRI_VERT,
	ISCT_IN_EDGE_VERT,
	ISCT_IN_TRI_VERT_AND_EDGE_VERT,
	ISCT_IN_TRI_EDGE_AND_EDGE_VERT,
	TWO_EDGE_IN_EDGE0_VERT,
	TWO_EDGE_IN_EDGE1_VERT,
	TWO_EDGE_IN_BOTH_EDGE_VERT
};




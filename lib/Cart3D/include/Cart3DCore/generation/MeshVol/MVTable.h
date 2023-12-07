#ifndef CART3D_GEN_MVTTABLE_H
#define CART3D_GEN_MVTTABLE_H


#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{

	enum {
		SIGNS = 0xFF, EDGES = 0xE00, INSIDE = 0x100,
		XEDGE = 0x200, YEDGE = 0x400, ZEDGE = 0x800, SEAM = 0x1000
	};

	struct MVTable
	{
		const bool sAdaptable[256];
		const unsigned char sAmbiguousFace[256];
		const unsigned char sEdgeGroupTable[256][13];

		const int edgeTable[256];
		const int triTable[256][2][17];
		const int polyTable[8][16];
		MVTable();
	};


}


#endif
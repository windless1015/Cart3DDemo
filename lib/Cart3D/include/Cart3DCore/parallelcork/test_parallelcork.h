#ifndef CART3D_PARAPPEL_CORK_test_H
#define CART3D_PARAPPEL_CORK_test_H

#include <Cart3DParallelCorkDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D {

	struct CART3D_PARALLEL_CORK_CLASS TestParallelCork
	{
		static int test_unionfind();
		static int test_quant();
		static int test_empty3d();
		static int test_topo();
	};
}


#endif
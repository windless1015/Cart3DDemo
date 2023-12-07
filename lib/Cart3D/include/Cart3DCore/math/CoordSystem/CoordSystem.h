#ifndef CART3D_MATH_COORDSYSTEM_H
#define CART3D_MATH_COORDSYSTEM_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{

	struct CART3D_MATH_CLASS CoordSystem
	{
		int id;

		union {
			struct {
				cvector3d ori;
				cvector3d x;
				cvector3d y;
				cvector3d z;
			};
			struct {
				cvector3d origin;
				cvector3d udir;
				cvector3d vdir;
				cvector3d wdir;
			};

			struct {
				cvector3d xyz;
				cvector3d xdir;
				cvector3d ydir;
				cvector3d zdir;
			};
		};
		

		//标准坐标系
		CoordSystem();
		CoordSystem(const CoordSystem&sys);
	};
}



#endif
#ifndef CART3D_PREDICATES_H
#define CART3D_PREDICATES_H
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	struct CART3D_MATH_API StartPredicate
	{
		StartPredicate();
		~StartPredicate();
	};
	CART3D_MATH_API cfloat orient2d(const cfloat *pa,
			const cfloat *pb,
			const cfloat *pc);
	CART3D_MATH_API cfloat orient2dfast(const cfloat *pa, 
		const cfloat *pb, 
		const cfloat *pc);
	CART3D_MATH_API cfloat orient2_5d(
		cfloat* pa,
		cfloat* pb, 
		cfloat* pc, 
		cfloat* pd,
		cfloat aheight, cfloat bheight, cfloat cheight, cfloat dheight);
	CART3D_MATH_API cfloat orient3d(const cfloat *pa,
			const cfloat *pb,
			const cfloat *pc,
			const cfloat *pd);
	CART3D_MATH_API cfloat orient3dfast(
		const cfloat *pa, const cfloat *pb,
		const cfloat *pc, const cfloat *pd);

	CART3D_MATH_API cfloat incircle(const cfloat *pa,
			const cfloat *pb,
			const cfloat *pc,
			const cfloat *pd);
	CART3D_MATH_API cfloat incirclefast(const cfloat *pa,
		const cfloat *pb,
		const cfloat *pc,
		const cfloat *pd);
	CART3D_MATH_API cfloat insphere(const cfloat *pa,
			const cfloat *pb,
			const cfloat *pc,
			const cfloat *pd,
			const cfloat *pe);
	CART3D_MATH_API cfloat inspherefast(const cfloat *pa,
		const cfloat *pb,
		const cfloat *pc,
		const cfloat *pd,
		const cfloat *pe);



}

#endif

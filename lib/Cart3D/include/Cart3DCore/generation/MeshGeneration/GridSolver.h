#ifndef CART3D_GENERATON_GRIDSOLVER_H
#define CART3D_GENERATON_GRIDSOLVER_H
#include "Cart3DGenerationDefine.h"
#include <Util/EigenUtil.h>

namespace Cart3D
{
	
	class CART3D_GENERATION_CLASS GridSolver
	{
	public:
		GridSolver();
		GridSolver(unsigned int udim, unsigned int vdim, unsigned int wdim, 
			cvector3d default_value = cvector3d(0,0,0));
		~GridSolver();
	public:
		void resize(unsigned int udim, unsigned int vdim, unsigned int wdim, cvector3d val = cvector3d(0,0,0));
		void clear();
		const cvector3d& operator()(unsigned int u, unsigned int v, unsigned int w) const;
		cvector3d &operator()(unsigned int u, unsigned int v, unsigned int w);

		cvector3d operator[](unsigned int idx) const;
		cvector3d &operator[](unsigned int idx);
		const cvector3d* data();
	public:
		unsigned int udim() const;
		unsigned int vdim() const;
		unsigned int wdim() const;
		unsigned int size() const;
		unsigned int idx(unsigned int i, unsigned int j, unsigned int k)const;
	private:
		unsigned int udim_, vdim_, wdim_;
		std::vector<cvector3d> data_;
	};


}

#endif
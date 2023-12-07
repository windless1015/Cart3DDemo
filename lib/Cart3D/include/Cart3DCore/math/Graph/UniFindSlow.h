#pragma once
#ifndef CART3D_MATH_UNIONFIND_HPP
#define CART3D_MATH_UNIONFIND_HPP


#include <Cart3dMathDefine.h>
#include <Util/BoostUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS UnionFindSlow {
	public:
		UnionFindSlow(int N);
		int find(int i);
		int find(int i, int& ic);
		int unionIds(int i, int j);
		ct_vector<int> dump();
	private:
		ct_vector<int> ids;
		ct_vector<int> rank;
	};
}

#endif
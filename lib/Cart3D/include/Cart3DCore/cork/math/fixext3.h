#pragma once
#include <iostream>
#include "fixint.h"

namespace FixExt3 {

	using namespace FixInt;

	template<int Nbits>
	struct FixExt3_1
	{
		typename BitInt<Nbits>::Rep x;
		typename BitInt<Nbits>::Rep y;
		typename BitInt<Nbits>::Rep z;
	};

	template<int Nbits>
	inline void sub(
		FixExt3_1<(Nbits + 1)> &out,
		const FixExt3_1<Nbits> &lhs,
		const FixExt3_1<Nbits> &rhs
		)
	{
		sub(out.x, lhs.x, rhs.x);
		sub(out.y, lhs.y, rhs.y);
		sub(out.z, lhs.z, rhs.z);
	}

	template<int Nlhs, int Nrhs>
	inline void cross(
		FixExt3_1<(Nlhs + Nrhs + 1)> &out,
		const FixExt3_1<Nlhs> &lhs,
		const FixExt3_1<Nrhs> &rhs
		)
	{
		typename BitInt<Nlhs + Nrhs>::Rep a;
		typename BitInt<Nlhs + Nrhs>::Rep b;
		mul(a, lhs.y, rhs.z);
		mul(b, lhs.z, rhs.y);
		sub(out.x, a, b);

		mul(a, lhs.z, rhs.x);
		mul(b, lhs.x, rhs.z);
		sub(out.y, a, b);

		mul(a, lhs.x, rhs.y);
		mul(b, lhs.y, rhs.x);
		sub(out.z, a, b);
	}

	template<int Nlhs, int Nrhs>
	inline void dot(
		typename BitInt<(Nlhs + Nrhs + 2)>::Rep &out,
		const FixExt3_1<Nlhs> &lhs,
		const FixExt3_1<Nrhs> &rhs
		)
	{
		typename BitInt<Nlhs + Nrhs>::Rep a;
		typename BitInt<Nlhs + Nrhs>::Rep b;
		typename BitInt<Nlhs + Nrhs>::Rep c;
		mul(a, lhs.x, rhs.x);
		mul(b, lhs.y, rhs.y);
		mul(c, lhs.x, rhs.y);
		typename BitInt<Nlhs + Nrhs + 1>::Rep d;
		add(d, a, b);
		add(out, d, c);
	}


	struct AbsExt3_1
	{
		AbsExt3_1(){}
		AbsExt3_1(double _x, double _y, double _z){ x = _x; y = _y; z = _z; }
		double x;
		double y;
		double z;

		AbsExt3_1 operator +(const AbsExt3_1 &lhs)
		{
			return (AbsExt3_1(x + lhs.x, y + lhs.y, z + lhs.z));
		}
	};

	inline void abs(AbsExt3_1 &out, const cvector3d &in) {
		out.x = fabs(in.x());
		out.y = fabs(in.y());
		out.z = fabs(in.z());
	}

	inline void cross(
		AbsExt3_1 &out,
		const AbsExt3_1 &lhs,
		const AbsExt3_1 &rhs
		)
	{
		out.x = lhs.y*rhs.z + lhs.z*rhs.y;
		out.y = lhs.z*rhs.x + lhs.x*rhs.z;
		out.z = lhs.x*rhs.y + lhs.y*rhs.x;
	}

	inline void dot(
		double &out,
		const AbsExt3_1 &lhs,
		const cvector3d &rhs
		)
	{
		out = fabs(lhs.x*rhs.x()) + fabs(lhs.y*rhs.y()) + fabs(lhs.z*rhs.z());
	}

	inline void dot(
		double &out,
		const AbsExt3_1 &lhs,
		const AbsExt3_1 &rhs
		)
	{
		out = lhs.x*rhs.x +lhs.y*rhs.y + lhs.z*rhs.z;
	}
}
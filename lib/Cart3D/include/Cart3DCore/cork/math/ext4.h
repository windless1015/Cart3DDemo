
#pragma once

#include <inttypes.h>

namespace Ext4 {
	struct Ext4_1 
	{
		union {
			struct {
				double v[4];
			};	
			struct {
				double e0;
				double e1;
				double e2;
				double e3;
			};
		};
	};
	struct Ext4_2
	{
		union {
			struct {
				double v[6];
			};
			struct {
				double e01;
				double e02;
				double e03;
				double e12;
				double e13;
				double e23;
			};
		};
	};
	struct Ext4_3
	{
		union {
			struct {
				double v[4];
			};
			struct {
				double e012;
				double e013;
				double e023;
				double e123;
			};
		};
	};
	inline void neg(Ext4_1 &out, const Ext4_1 &in) {
		for (int i = 0; i < 4; i++)
			out.v[i] = -in.v[i];
	}
	inline void neg(Ext4_2 &out, const Ext4_2 &in) {
		for (int i = 0; i < 6; i++)
			out.v[i] = -in.v[i];
	}
	inline void neg(Ext4_3 &out, const Ext4_3 &in) {
		for (int i = 0; i < 4; i++)
			out.v[i] = -in.v[i];
	}
	inline void dual(Ext4_1 &out, const Ext4_3 &in) {
		out.e0 = in.e123;
		out.e1 = -in.e023;
		out.e2 = in.e013;
		out.e3 = -in.e012;
	}
	inline void dual(Ext4_2 &out, const Ext4_2 &in) {
		out.e01 = in.e23;
		out.e02 = -in.e13;
		out.e03 = in.e12;
		out.e12 = in.e03;
		out.e13 = -in.e02;
		out.e23 = in.e01;
	}
	inline void dual(Ext4_3 &out, const Ext4_1 &in) {
		out.e012 = in.e3;
		out.e013 = -in.e2;
		out.e023 = in.e1;
		out.e123 = -in.e0;
	}
	inline void revdual(Ext4_1 &out, const Ext4_3 &in) {
		out.e0 = -in.e123;
		out.e1 = in.e023;
		out.e2 = -in.e013;
		out.e3 = in.e012;
	}
	inline void revdual(Ext4_2 &out, const Ext4_2 &in) {
		out.e01 = in.e23;
		out.e02 = -in.e13;
		out.e03 = in.e12;
		out.e12 = in.e03;
		out.e13 = -in.e02;
		out.e23 = in.e01;
	}
	inline void revdual(Ext4_3 &out, const Ext4_1 &in) {
		out.e012 = -in.e3;
		out.e013 = in.e2;
		out.e023 = -in.e1;
		out.e123 = in.e0;
	}
	inline void join(Ext4_2 &out, const Ext4_1 &lhs, const Ext4_1 &rhs) {
		out.e01 = (lhs.e0 * rhs.e1) - (rhs.e0 * lhs.e1);
		out.e02 = (lhs.e0 * rhs.e2) - (rhs.e0 * lhs.e2);
		out.e03 = (lhs.e0 * rhs.e3) - (rhs.e0 * lhs.e3);
		out.e12 = (lhs.e1 * rhs.e2) - (rhs.e1 * lhs.e2);
		out.e13 = (lhs.e1 * rhs.e3) - (rhs.e1 * lhs.e3);
		out.e23 = (lhs.e2 * rhs.e3) - (rhs.e2 * lhs.e3);
	}
	inline void join(Ext4_3 &out, const Ext4_2 &lhs, const Ext4_1 &rhs) {
		out.e012 = (lhs.e01 * rhs.e2) - (lhs.e02 * rhs.e1) + (lhs.e12 *rhs.e0);
		out.e013 = (lhs.e01 * rhs.e3) - (lhs.e03 * rhs.e1) + (lhs.e13 *rhs.e0);
		out.e023 = (lhs.e02 * rhs.e3) - (lhs.e03 * rhs.e2) + (lhs.e23 *rhs.e0);
		out.e123 = (lhs.e12 * rhs.e3) - (lhs.e13 * rhs.e2) + (lhs.e23 *rhs.e1);
	}
	inline void join(Ext4_3 &out, const Ext4_1 &lhs, const Ext4_2 &rhs) {
		join(out, rhs, lhs);
	}
	inline void crossing(double  &out, const Ext4_2 &lhs, const Ext4_2 &rhs) {
		out = -lhs.e03 * rhs.e12 + lhs.e13 * rhs.e02 - lhs.e23 * rhs.e01
			- lhs.e12 * rhs.e03 + lhs.e02 * rhs.e13 - lhs.e01 * rhs.e23;
	}
	inline void meet(Ext4_2 &out, const Ext4_3 &lhs, const Ext4_3 &rhs) {
		Ext4_2 out_dual;
		Ext4_1 lhs_dual;
		Ext4_1 rhs_dual;
		dual(lhs_dual, lhs);
		dual(rhs_dual, rhs);
		join(out_dual, lhs_dual, rhs_dual);
		revdual(out, out_dual);
	}
	inline void meet(Ext4_1 &out, const Ext4_2 &lhs, const Ext4_3 &rhs) {
		Ext4_3 out_dual;
		Ext4_2 lhs_dual;
		Ext4_1 rhs_dual;
		dual(lhs_dual, lhs);
		dual(rhs_dual, rhs);
		join(out_dual, lhs_dual, rhs_dual);
		revdual(out, out_dual);
	}
	inline void meet(Ext4_1 &out, const Ext4_3 &lhs, const Ext4_2 &rhs) {
		Ext4_3 out_dual;
		Ext4_1 lhs_dual;
		Ext4_2 rhs_dual;
		dual(lhs_dual, lhs);
		dual(rhs_dual, rhs);
		join(out_dual, lhs_dual, rhs_dual);
		revdual(out, out_dual);
	}
	inline double inner(const Ext4_1 &lhs, const Ext4_1 &rhs) {
		double acc = 0.0;
		for (int i = 0; i < 4; i++)
			acc += lhs.v[i] * rhs.v[i];
		return acc;
	}
	inline double inner(const Ext4_2 &lhs, const Ext4_2 &rhs) {
		double acc = 0.0;
		for (int i = 0; i < 6; i++)
			acc += lhs.v[i] * rhs.v[i];
		return acc;
	}
	inline double inner(const Ext4_3 &lhs, const Ext4_3 &rhs) {
		double acc = 0.0;
		for (int i = 0; i < 4; i++)
			acc += lhs.v[i] * rhs.v[i];
		return acc;
	}
}


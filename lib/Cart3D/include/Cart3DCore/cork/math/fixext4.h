
#pragma once

/*
 *
 *  FixExt4
 *
 *      Support for performing exterior calculus in R4
 *
 */

//#include <iostream>
//using std::cout;
//using std::endl;
#include <iostream>


#include "fixint.h"

namespace FixExt4 {

using namespace FixInt;

// types for k-vectors in R4:
//      Ext4_k

template<int Nbits>
struct FixExt4_1 {
    typename BitInt<Nbits>::Rep e0;
    typename BitInt<Nbits>::Rep e1;
    typename BitInt<Nbits>::Rep e2;
    typename BitInt<Nbits>::Rep e3;
};

template<int Nbits>
struct FixExt4_2 {
    typename BitInt<Nbits>::Rep e01;
    typename BitInt<Nbits>::Rep e02;
    typename BitInt<Nbits>::Rep e03;
    typename BitInt<Nbits>::Rep e12;
    typename BitInt<Nbits>::Rep e13;
    typename BitInt<Nbits>::Rep e23;
};

template<int Nbits>
struct FixExt4_3 {
    typename BitInt<Nbits>::Rep e012;
    typename BitInt<Nbits>::Rep e013;
    typename BitInt<Nbits>::Rep e023;
    typename BitInt<Nbits>::Rep e123;
};


// ********************************
// Output Routines
template<int N>
std::ostream& operator<<(std::ostream &out, const FixExt4_1<N> &ext)
{
    return out << '[' << toString(ext.e0)
               << ',' << toString(ext.e1)
               << ',' << toString(ext.e2)
               << ',' << toString(ext.e3) << ']';
}
template<int N>
std::ostream& operator<<(std::ostream &out, const FixExt4_2<N> &ext)
{
    return out << '[' << toString(ext.e01)
               << ',' << toString(ext.e02)
               << ',' << toString(ext.e03)
               << ',' << toString(ext.e12)
               << ',' << toString(ext.e13)
               << ',' << toString(ext.e23) << ']';
}
template<int N>
std::ostream& operator<<(std::ostream &out, const FixExt4_3<N> &ext)
{
    return out << '[' << toString(ext.e012)
               << ',' << toString(ext.e013)
               << ',' << toString(ext.e023)
               << ',' << toString(ext.e123) << ']';
}


// ********************************
// A neg takes a k-vector and returns its negation
// neg(X,Y) is safe for X=Y
template<int N> inline
void neg(FixExt4_1<N> &out, const FixExt4_1<N> &in)
{
    neg(out.e0, in.e0);
    neg(out.e1, in.e1);
    neg(out.e2, in.e2);
    neg(out.e3, in.e3);
}
template<int N> inline
void neg(FixExt4_2<N> &out, const FixExt4_2<N> &in)
{
    neg(out.e01, in.e01);
    neg(out.e02, in.e02);
    neg(out.e03, in.e03);
    neg(out.e12, in.e12);
    neg(out.e13, in.e13);
    neg(out.e23, in.e23);
}
template<int N> inline
void neg(FixExt4_3<N> &out, const FixExt4_3<N> &in)
{
    neg(out.e012, in.e012);
    neg(out.e013, in.e013);
    neg(out.e023, in.e023);
    neg(out.e123, in.e123);
}


// ********************************
// A dual operation takes a k-vector and returns a (4-k)-vector
// A reverse dual operation inverts the dual operation
// dual(X,Y) is not safe for X=Y (same with revdual)
template<int N> inline
void dual(FixExt4_1<N> &out, const FixExt4_3<N> &in)
{
    out.e0 =  in.e123;
    neg(out.e1, in.e023);
    out.e2 =  in.e013;
    neg(out.e3, in.e012);
}
template<int N> inline
void dual(FixExt4_2<N> &out, const FixExt4_2<N> &in)
{
    out.e01 =  in.e23;
    neg(out.e02, in.e13);
    out.e03 =  in.e12;
    out.e12 =  in.e03;
    neg(out.e13, in.e02);
    out.e23 =  in.e01;
}
template<int N> inline
void dual(FixExt4_3<N> &out, const FixExt4_1<N> &in)
{
    out.e012 =  in.e3;
    neg(out.e013, in.e2);
    out.e023 =  in.e1;
    neg(out.e123, in.e0);
}
template<int N> inline
void revdual(FixExt4_1<N> &out, const FixExt4_3<N> &in)
{
    neg(out.e0, in.e123);
    out.e1 =  in.e023;
    neg(out.e2, in.e013);
    out.e3 =  in.e012;
}
template<int N> inline
void revdual(FixExt4_2<N> &out, const FixExt4_2<N> &in)
{
    out.e01 =  in.e23;
    neg(out.e02, in.e13);
    out.e03 =  in.e12;
    out.e12 =  in.e03;
    neg(out.e13, in.e02);
    out.e23 =  in.e01;
}
template<int N> inline
void revdual(FixExt4_3<N> &out, const FixExt4_1<N> &in)
{
    neg(out.e012, in.e3);
    out.e013 =  in.e2;
    neg(out.e023, in.e1);
    out.e123 =  in.e0;
}


// ********************************
// A join takes a j-vector and a k-vector and returns a (j+k)-vector
template<int Nlhs, int Nrhs> inline
void join(FixExt4_2<(Nlhs + Nrhs + 1)> &out,
          const FixExt4_1<Nlhs> &lhs,
          const FixExt4_1<Nrhs> &rhs)
{
    typename BitInt<(Nlhs + Nrhs)>::Rep a;
    typename BitInt<(Nlhs + Nrhs)>::Rep b;
    mul(a, lhs.e0, rhs.e1); mul(b, rhs.e0, lhs.e1);
    //cout << "a/b limbs: " << BITS_TO_LIMBS(Nlhs+Nrhs) << endl;
    //cout << "out bits: " << BITS_TO_LIMBS(Nlhs+Nrhs+1) << endl;
    //cout << "a,b: " << toString(a) << ',' << toString(b) << endl;
        sub(out.e01, a, b);
    mul(a, lhs.e0, rhs.e2); mul(b, rhs.e0, lhs.e2);
        sub(out.e02, a, b);
    mul(a, lhs.e0, rhs.e3); mul(b, rhs.e0, lhs.e3);
        sub(out.e03, a, b);
    mul(a, lhs.e1, rhs.e2); mul(b, rhs.e1, lhs.e2);
        sub(out.e12, a, b);
    mul(a, lhs.e1, rhs.e3); mul(b, rhs.e1, lhs.e3);
        sub(out.e13, a, b);
    mul(a, lhs.e2, rhs.e3); mul(b, rhs.e2, lhs.e3);
        sub(out.e23, a, b);
}
template<int Nlhs, int Nrhs> inline
void join(FixExt4_3<(Nlhs + Nrhs + 2)> &out,
          const FixExt4_2<Nlhs> &lhs,
          const FixExt4_1<Nrhs> &rhs)
{
    typename BitInt<(Nlhs + Nrhs)>::Rep a;
    typename BitInt<(Nlhs + Nrhs)>::Rep b;
    typename BitInt<(Nlhs + Nrhs)>::Rep c;
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep x;
    //cout << "Nlhs: " << Nlhs << "  Nrhs: " << Nrhs << endl;
    mul(a, lhs.e01, rhs.e2); mul(b, lhs.e02, rhs.e1); mul(c, lhs.e12, rhs.e0);
    //cout << "a,b,c: " << toString(a) << ','
    //                  << toString(b) << ',' << toString(c) << endl;
        sub(x, a, b);   add(out.e012, x, c);
    mul(a, lhs.e01, rhs.e3); mul(b, lhs.e03, rhs.e1); mul(c, lhs.e13, rhs.e0);
    //cout << "a,b,c: " << toString(a) << ','
    //                  << toString(b) << ',' << toString(c) << endl;
        sub(x, a, b);   add(out.e013, x, c);
    mul(a, lhs.e02, rhs.e3); mul(b, lhs.e03, rhs.e2); mul(c, lhs.e23, rhs.e0);
    //cout << "a,b,c: " << toString(a) << ','
    //                  << toString(b) << ',' << toString(c) << endl;
        sub(x, a, b);   add(out.e023, x, c);
    mul(a, lhs.e12, rhs.e3); mul(b, lhs.e13, rhs.e2); mul(c, lhs.e23, rhs.e1);
    //cout << "a,b,c: " << toString(a) << ','
    //                  << toString(b) << ',' << toString(c) << endl;
        sub(x, a, b);   add(out.e123, x, c);
}
template<int Nlhs, int Nrhs> inline
void join(FixExt4_3<(Nlhs + Nrhs + 2)> &out,
          const FixExt4_1<Nlhs> &lhs,
          const FixExt4_2<Nrhs> &rhs)
{
    join(out, rhs, lhs);
    // no negation since swapping the arguments requires two
    // swaps of 1-vectors
}

//template<int Nlhs, int Nrhs> inline
//void meet(FixExt4_1<(Nlhs + Nrhs + 2)> &out,
//const FixExt4_2<Nlhs> &lhs,
//const FixExt4_2<Nrhs> &rhs)
//{
//	typename BitInt<(Nlhs + Nrhs)>::Rep a;
//	typename BitInt<(Nlhs + Nrhs)>::Rep b;
//	typename BitInt<(Nlhs + Nrhs)>::Rep c;
//	typename BitInt<(Nlhs + Nrhs + 1)>::Rep x;
//
//	mul(a, lhs.e03, rhs.e12); mul(b, lhs.e13, rhs.e02); mul(c, lhs.e23, rhs.e01);
//	sub(x, a, b); add(out.e3, x, c);
//
//	mul(a, lhs.e02, rhs.e01); mul(b, lhs.e01, rhs.e02);
//	sub(out.e0, b, a);
//
//	mul(a, lhs.e01, rhs.e12); mul(b, lhs.e12, rhs.e01);
//	sub(out.e1, a, b);
//
//	mul(a, lhs.e12, rhs.e02); mul(b, lhs.e02, rhs.e12);
//	sub(out.e2, b, a);
//}
// ********************************
// A meet takes a j-vector and a k-vector and returns a (j+k-4)-vector
template<int Nlhs, int Nrhs> inline
void meet(FixExt4_2<(Nlhs + Nrhs + 1)> &out,
          const FixExt4_3<Nlhs> &lhs,
          const FixExt4_3<Nrhs> &rhs)
{
    FixExt4_2<(Nlhs + Nrhs + 1)> out_dual;
    FixExt4_1<Nlhs> lhs_dual;
    FixExt4_1<Nrhs> rhs_dual;
    dual(lhs_dual, lhs);
    dual(rhs_dual, rhs);
    join(out_dual, lhs_dual, rhs_dual);
    revdual(out, out_dual);
}
template<int Nlhs, int Nrhs> inline
void meet(FixExt4_1<(Nlhs + Nrhs + 2)> &out,
          const FixExt4_2<Nlhs> &lhs,
          const FixExt4_3<Nrhs> &rhs)
{
    FixExt4_3<(Nlhs + Nrhs + 2)> out_dual;
    FixExt4_2<Nlhs> lhs_dual;
    FixExt4_1<Nrhs> rhs_dual;
    dual(lhs_dual, lhs);
    dual(rhs_dual, rhs);
    join(out_dual, lhs_dual, rhs_dual);
    revdual(out, out_dual);
}
template<int Nlhs, int Nrhs> inline
void meet(FixExt4_1<(Nlhs + Nrhs + 2)> &out,
          const FixExt4_3<Nlhs> &lhs,
          const FixExt4_2<Nrhs> &rhs)
{
    FixExt4_3<(Nlhs + Nrhs + 2)> out_dual;
    FixExt4_1<Nlhs> lhs_dual;
    FixExt4_2<Nrhs> rhs_dual;
    dual(lhs_dual, lhs);
    dual(rhs_dual, rhs);
    join(out_dual, lhs_dual, rhs_dual);
    revdual(out, out_dual);
}


// ********************************
// An inner product takes two k-vectors and produces a single number
template<int Nlhs, int Nrhs> inline
void inner(typename BitInt<(Nlhs + Nrhs + 2)>::Rep &out,
           const FixExt4_1<Nlhs> &lhs,
           const FixExt4_1<Nrhs> &rhs)
{
    typename BitInt<(Nlhs + Nrhs)>::Rep p0;      mul(p0, lhs.e0, rhs.e0);
    typename BitInt<(Nlhs + Nrhs)>::Rep p1;      mul(p1, lhs.e1, rhs.e1);
    typename BitInt<(Nlhs + Nrhs)>::Rep p2;      mul(p2, lhs.e2, rhs.e2);
    typename BitInt<(Nlhs + Nrhs)>::Rep p3;      mul(p3, lhs.e3, rhs.e3);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep a;   add(a, p0, p1);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep b;   add(b, p2, p3);
    add(out, a, b);
}
template<int Nlhs, int Nrhs> inline
void inner(typename BitInt<(Nlhs + Nrhs + 3)>::Rep &out,
           const FixExt4_2<Nlhs> &lhs,
           const FixExt4_2<Nrhs> &rhs)
{
    typename BitInt<(Nlhs + Nrhs)>::Rep p0;      mul(p0, lhs.e01, rhs.e01);
    typename BitInt<(Nlhs + Nrhs)>::Rep p1;      mul(p1, lhs.e02, rhs.e02);
    typename BitInt<(Nlhs + Nrhs)>::Rep p2;      mul(p2, lhs.e03, rhs.e03);
    typename BitInt<(Nlhs + Nrhs)>::Rep p3;      mul(p3, lhs.e12, rhs.e12);
    typename BitInt<(Nlhs + Nrhs)>::Rep p4;      mul(p4, lhs.e13, rhs.e13);
    typename BitInt<(Nlhs + Nrhs)>::Rep p5;      mul(p5, lhs.e23, rhs.e23);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep a;   add(a, p0, p1);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep b;   add(b, p2, p3);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep c;   add(c, p4, p5);
    typename BitInt<(Nlhs + Nrhs + 2)>::Rep x;   add(x, a, b);
    add(out, x, c);
}
template<int Nlhs, int Nrhs> inline
void inner(typename BitInt<(Nlhs + Nrhs + 2)>::Rep &out,
           const FixExt4_3<Nlhs> &lhs,
           const FixExt4_3<Nrhs> &rhs)
{
    typename BitInt<(Nlhs + Nrhs)>::Rep p0;      mul(p0, lhs.e012, rhs.e012);
    typename BitInt<(Nlhs + Nrhs)>::Rep p1;      mul(p1, lhs.e013, rhs.e013);
    typename BitInt<(Nlhs + Nrhs)>::Rep p2;      mul(p2, lhs.e023, rhs.e023);
    typename BitInt<(Nlhs + Nrhs)>::Rep p3;      mul(p3, lhs.e123, rhs.e123);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep a;   add(a, p0, p1);
    typename BitInt<(Nlhs + Nrhs + 1)>::Rep b;   add(b, p2, p3);
    add(out, a, b);
}


template<int Nlhs, int Nrhs> inline
void crossproduct(FixExt4_1<(Nlhs + Nrhs + 1)> &out,
const FixExt4_2<Nlhs> &lhs,
const FixExt4_2<Nrhs> &rhs)
{
	typename BitInt<(Nlhs + Nrhs)>::Rep p0;      mul(p0, lhs.e13, rhs.e23);
	typename BitInt<(Nlhs + Nrhs)>::Rep p1;      mul(p1, lhs.e23, rhs.e13);
	sub(out.e0, p0, p1);

	typename BitInt<(Nlhs + Nrhs)>::Rep p2;      mul(p2, lhs.e23, rhs.e03);
	typename BitInt<(Nlhs + Nrhs)>::Rep p3;      mul(p3, lhs.e03, rhs.e23);
	sub(out.e1, p2, p3);

	typename BitInt<(Nlhs + Nrhs)>::Rep p4;      mul(p4, lhs.e03, rhs.e13);
	typename BitInt<(Nlhs + Nrhs)>::Rep p5;      mul(p5, lhs.e13, rhs.e03);
	sub(out.e2, p4, p5);
}

template<int Nlhs, int Nrhs> inline
void offset(FixExt4_1<(Nrhs + 1)> &out,
const FixExt4_1<Nlhs> &lhs,
const FixExt4_1<Nrhs> &rhs)
{
	add(out.e0, lhs.e0, rhs.e0);
	add(out.e1, lhs.e1, rhs.e1);
	add(out.e2, lhs.e2, rhs.e2);
}


template<int Nlhs, int Nrhs> inline
void crossing(typename BitInt<(Nlhs + Nrhs + 3)>::Rep &out,
				const FixExt4_2<Nlhs> &lhs,
				const FixExt4_2<Nrhs> &rhs)
{

	typename BitInt<(Nlhs + Nrhs)>::Rep p0;     mul(p0, lhs.e03, rhs.e12);
	typename BitInt<(Nlhs + Nrhs)>::Rep p1;     mul(p1, lhs.e13, rhs.e02);
	typename BitInt<(Nlhs + Nrhs)>::Rep p2;     mul(p2, lhs.e23, rhs.e01);
	typename BitInt<(Nlhs + Nrhs)>::Rep p3;     mul(p3, lhs.e12, rhs.e03);
	typename BitInt<(Nlhs + Nrhs)>::Rep p4;     mul(p4, lhs.e02, rhs.e13);
	typename BitInt<(Nlhs + Nrhs)>::Rep p5;     mul(p5, lhs.e01, rhs.e23);

	typename BitInt<(Nlhs + Nrhs) + 1>::Rep a1;
	typename BitInt<(Nlhs + Nrhs) + 1>::Rep a2;
	typename BitInt<(Nlhs + Nrhs) + 1>::Rep a3;
	typename BitInt<(Nlhs + Nrhs) + 2>::Rep a4;

	add(a1, p1, p4);
	add(a2, p0, p2);
	add(a3, p3, p5);
	sub(a4, a1, a2);
	sub(out, a4, a3);

	//out = -lhs.e03 * rhs.e12 + lhs.e13 * rhs.e02 - lhs.e23 * rhs.e01
	//	- lhs.e12 * rhs.e03 + lhs.e02 * rhs.e13 - lhs.e01 * rhs.e23;

}

} // end namespace FixExt4


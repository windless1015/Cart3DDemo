#pragma once
#ifndef CART3D_ALGO_MAT_SOLVER_H
#define CART3D_ALGO_MAT_SOLVER_H

#include <iostream>
#include <algorithm>
namespace Cart3D {
	
	template<class T>
	static T clamp(const T& x,const T& b,const T& c)
	{
		T val = x;
		if (val < b)val = b;
		if (val > c)val = c;
		return val;
	}

	template <class T, int N>
	static inline bool ludcmp(T(&A)[N][N], int ind[N])
	{
		using namespace ::std;
		T pivot[N];

		for (int i = 0; i < N; i++) {
			T big = 0;
			for (int j = 0; j < N; j++) {
				T tmp = abs(A[i][j]);
				if (tmp > big)
					big = tmp;
			}
			if (big == 0)
				return false;
			pivot[i] = 1 / big;
		}
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < j; i++) {
				T sum = A[i][j];
				for (int k = 0; k < i; k++)
					sum -= A[i][k] * A[k][j];
				A[i][j] = sum;
			}
			T big = 0;
			int imax = j;
			for (int i = j; i < N; i++) {
				T sum = A[i][j];
				for (int k = 0; k < j; k++)
					sum -= A[i][k] * A[k][j];
				A[i][j] = sum;
				T tmp = pivot[i] * abs(sum);
				if (tmp > big) {
					big = tmp;
					imax = i;
				}
			}
			if (imax != j) {
				for (int k = 0; k < N; k++)
					swap(A[imax][k], A[j][k]);
				pivot[imax] = pivot[j];
			}
			ind[j] = imax;
			if (A[j][j] == 0)
				return false;
			if (j != N - 1) {
				T tmp = 1 / A[j][j];
				for (int i = j + 1; i < N; i++)
					A[i][j] *= tmp;
			}
		}
		return true;
	}



	template <class T, int N>
	static inline void lubksb(const T(&A)[N][N], const int ind[N], T b[N])
	{
		for (int i = 0; i < N; i++) {
			int ip = ind[i];
			T sum = b[ip];
			b[ip] = b[i];
			for (int j = 0; j < i; j++)
				sum -= A[i][j] * b[j];
			b[i] = sum;
		}
		for (int i = N - 1; i >= 0; i--) {
			T sum = b[i];
			for (int j = i + 1; j < N; j++)
				sum -= A[i][j] * b[j];
			b[i] = sum / A[i][i];
		}
	}


	template <class T, int N>
	static inline void lubksb(const T(&A)[N][N],
		const int ind[N],
		const T b[N],
		T x[N])
	{
		if (&x[0] != &b[0]) {
			for (int i = 0; i < N; i++)
				x[i] = b[i];
		}
		lubksb(A, ind, x);
	}


	template <class T, int N>
	static inline bool ldltdc(T(&A)[N][N], T rdiag[N])
	{
		if (N < 1) {
			return false;
		}
		else if (N <= 3) {
			T d0 = A[0][0];
			rdiag[0] = 1 / d0;
			if (N == 1)
				return (d0 != 0);
			A[1][0] = A[0][1];
			T l10 = rdiag[0] * A[1][0];
			T d1 = A[1][1] - l10 * A[1][0];
			rdiag[1] = 1 / d1;
			if (N == 2)
				return (d0 != 0 && d1 != 0);
			T d2 = A[2][2] - rdiag[0] * sqr(A[2][0]) - rdiag[1] * sqr(A[2][1]);
			rdiag[2] = 1 / d2;
			A[2][0] = A[0][2];
			A[2][1] = A[1][2] - l10 * A[2][0];
			return (d0 != 0 && d1 != 0 && d2 != 0);
		}

		T v[N - 1];
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < i; k++)
				v[k] = A[i][k] * rdiag[k];
			for (int j = i; j < N; j++) {
				T sum = A[i][j];
				for (int k = 0; k < i; k++)
					sum -= v[k] * A[j][k];
				if (i == j) {
					if (unlikely(sum == 0))
						return false;
					rdiag[i] = 1 / sum;
				}
				else {
					A[j][i] = sum;
				}
			}
		}

		return true;
	}


	template <class T, int N>
	static inline void ldltsl(const T(&A)[N][N],
		const T rdiag[N],
		const T b[N],
		T x[N])
	{
		for (int i = 0; i < N; i++) {
			T sum = b[i];
			for (int k = 0; k < i; k++)
				sum -= A[i][k] * x[k];
			x[i] = sum * rdiag[i];
		}
		for (int i = N - 1; i >= 0; i--) {
			T sum = 0;
			for (int k = i + 1; k < N; k++)
				sum += A[k][i] * x[k];
			x[i] -= sum * rdiag[i];
		}
	}



	template <class T, int N>
	static inline void ldltsl(const T(&A)[N][N], const T rdiag[N], T b[N])
	{
		ldltsl(A, rdiag, b, b);
	}


	template <class T, int N>
	static inline void eigdc(T(&A)[N][N], T d[N])
	{
		using namespace ::std;
		T e[N];

		// Householder
		for (int j = 0; j < N; j++) {
			d[j] = A[N - 1][j];
			e[j] = 0;
		}
		for (int i = N - 1; i > 0; i--) {
			T scale = 0;
			for (int k = 0; k < i; k++)
				scale += abs(d[k]);
			if (scale == 0) {
				e[i] = d[i - 1];
				for (int j = 0; j < i; j++) {
					d[j] = A[i - 1][j];
					A[i][j] = A[j][i] = 0;
				}
				d[i] = 0;
			}
			else {
				T h(0);
				T invscale = 1 / scale;
				for (int k = 0; k < i; k++) {
					d[k] *= invscale;
					h += sqr(d[k]);
				}
				T f = d[i - 1];
				T g = (f > 0) ? -sqrt(h) : sqrt(h);
				e[i] = scale * g;
				h -= f * g;
				d[i - 1] = f - g;
				for (int j = 0; j < i; j++)
					e[j] = 0;
				for (int j = 0; j < i; j++) {
					f = d[j];
					A[j][i] = f;
					g = e[j] + f * A[j][j];
					for (int k = j + 1; k < i; k++) {
						g += A[k][j] * d[k];
						e[k] += A[k][j] * f;
					}
					e[j] = g;
				}
				f = 0;
				T invh = 1 / h;
				for (int j = 0; j < i; j++) {
					e[j] *= invh;
					f += e[j] * d[j];
				}
				T hh = f / (h + h);
				for (int j = 0; j < i; j++)
					e[j] -= hh * d[j];
				for (int j = 0; j < i; j++) {
					f = d[j];
					g = e[j];
					for (int k = j; k < i; k++)
						A[k][j] -= f * e[k] + g * d[k];
					d[j] = A[i - 1][j];
					A[i][j] = 0;
				}
				d[i] = h;
			}
		}

		for (int i = 0; i < N - 1; i++) {
			A[N - 1][i] = A[i][i];
			A[i][i] = 1;
			T h = d[i + 1];
			if (h != 0) {
				T invh = 1 / h;
				for (int k = 0; k <= i; k++)
					d[k] = A[k][i + 1] * invh;
				for (int j = 0; j <= i; j++) {
					T g = 0;
					for (int k = 0; k <= i; k++)
						g += A[k][i + 1] * A[k][j];
					for (int k = 0; k <= i; k++)
						A[k][j] -= g * d[k];
				}
			}
			for (int k = 0; k <= i; k++)
				A[k][i + 1] = 0;
		}
		for (int j = 0; j < N; j++) {
			d[j] = A[N - 1][j];
			A[N - 1][j] = 0;
		}
		A[N - 1][N - 1] = 1;
		for (int i = 1; i < N; i++)
			e[i - 1] = e[i];
		e[N - 1] = 0;
		T f = 0, tmp = 0;
		const T eps = numeric_limits<T>::epsilon();
		for (int l = 0; l < N; l++) {
			tmp = max(tmp, abs(d[l]) + abs(e[l]));
			int m = l;
			while (m < N) {
				if (abs(e[m]) <= eps * tmp)
					break;
				m++;
			}
			if (m > l) {
				do {
					T g = d[l];
					T p = (d[l + 1] - g) / (e[l] + e[l]);
					T r = hypot(p, T(1));
					if (p < 0)
						r = -r;
					d[l] = e[l] / (p + r);
					d[l + 1] = e[l] * (p + r);
					T dl1 = d[l + 1];
					T h = g - d[l];
					for (int i = l + 2; i < N; i++)
						d[i] -= h;
					f += h;
					p = d[m];
					T c = 1, c2 = 1, c3 = 1;
					T el1 = e[l + 1], s = 0, s2 = 0;
					for (int i = m - 1; i >= l; i--) {
						c3 = c2;
						c2 = c;
						s2 = s;
						g = c * e[i];
						h = c * p;
						r = hypot(p, e[i]);
						e[i + 1] = s * r;
						s = e[i] / r;
						c = p / r;
						p = c * d[i] - s * g;
						d[i + 1] = h + s * (c * g + s * d[i]);
						for (int k = 0; k < N; k++) {
							h = A[k][i + 1];
							A[k][i + 1] = s * A[k][i] + c * h;
							A[k][i] = c * A[k][i] - s * h;
						}
					}
					p = -s * s2 * c3 * el1 * e[l] / dl1;
					e[l] = s * p;
					d[l] = c * p;
				} while (abs(e[l]) > eps * tmp);
			}
			d[l] += f;
			e[l] = 0;
		}

		for (int i = 0; i < N - 1; i++) {
			int k = i;
			T p = d[i];
			for (int j = i + 1; j < N; j++) {
				if (d[j] < p) {
					k = j;
					p = d[j];
				}
			}
			if (k == i)
				continue;
			d[k] = d[i];
			d[i] = p;
			for (int j = 0; j < N; j++)
				swap(A[j][i], A[j][k]);
		}
	}


	template <class T, int N>
	static inline void eigmult(const T(&A)[N][N],
		const T d[N],
		const T b[N],
		T x[N])
	{
		T e[N];
		for (int i = 0; i < N; i++) {
			T sum = 0;
			for (int j = 0; j < N; j++)
				sum += A[j][i] * b[j];
			e[i] = sum * d[i];
		}
		for (int i = 0; i < N; i++) {
			T sum = 0;
			for (int j = 0; j < N; j++)
				sum += A[i][j] * e[j];
			x[i] = sum;
		}
	}

	template <class T, int N>
	static inline void eigmult(const T(&A)[N][N], const T d[N], T b[N])
	{
		eigmult<T, N>(A, d, b, b);
	}

}
#endif

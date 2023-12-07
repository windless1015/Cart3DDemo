// +-------------------------------------------------------------------------
// | ext4.h
// |
// | Author: Gilbert Bernstein
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Gilbert Bernstein 2013
// |    See the included COPYRIGHT file for further details.
// |
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------
#pragma once

#include <Util/EigenUtil.h>
#include <math/ext4_base.hpp>

/*

   ExteriorCalculusR4

	   Support for performing exterior calculus in R4

   The subscripts in the different classes refer to elements in vectors or matrices.
	   The 'k-value' indicates the dimension of the class, i.e. Ext4_1 is one dimensional so it is a vector.
	   Ext4_2 is two dimensional so it is a matrix.  Ext4_3 is three dimensional and is a vector of matrices.
	   Ext4_2 and Ext4_3 are upper diagonal

	 Ext4_1 ->  [ e0   e1   e2   e3 ]

				 -                   -
				 | e01  e02  e03     |
	  Ext4_2 ->  |      e12  e13     |
				 |           e23     |
				 |                   |
				 -                   -

				-                                     -
				| -               - -               - |
				| |               | |               | |
	  Ext4_3 -> | |      e12  e13 | |               | |
				| |           e23 | |           e23 | |
				| -               - -               - |
				-                                     -

	The join() operation is simply the wedge product of the two items.  The wedge product takes two operands and returns
	an item with a k-value which is the sum of the two k values of the operands.  Thus :

		Ext4_1 ^ Ext4_1 -> Ext4_2
		Ext4_1 ^ Ext4_2 -> Ext4_3
		Ext4_2 ^ Ext4_1 -> Ext4_3

	The wedge product of an Ext4_3 with an Ext4_1 or Ext4_2 would result in a k-value >= the order 4, so these
   operations are not allowed.  I don't think they make physical sense.

 */

namespace Cart3D
{
	class Ext4_2;
	class Ext4_3;
	class AbsExt4_1;
	class AbsExt4_2;
	class AbsExt4_3;

	class Ext4_1 : public Ext4_1Base
	{
	public:
		Ext4_1(const Ext4_1& ext_to_copy) : Ext4_1Base(ext_to_copy) {}
		Ext4_1(Ext4_1&& ext_to_move) : Ext4_1Base(ext_to_move) {}
		explicit Ext4_1(const cvector3d& vector)
			: Ext4_1Base(vector[0], vector[1], vector[2], 1)
		{
		}
		const Ext4_1& operator=(const cvector3d& vector)
		{
			e0_ = vector[0];
			e1_ = vector[1];
			e2_ = vector[2];
			e3_ = 1;
			return *this;
		}
		operator cvector3d() const
		{
			cvector3d vec(e0_, e1_, e2_);
			vec /= e3_;
			return vec;
		}
		Ext4_1& operator=(const Ext4_1& ext_to_copy) = default;
		Ext4_1& operator=(Ext4_1&& ext_to_move) = default;
		const Ext4_1& negate()
		{
			e0_ = -e0_;
			e1_ = -e1_;
			e2_ = -e2_;
			e3_ = -e3_;

			return *this;
		}
		Ext4_1 negative() const { return Ext4_1(-e0_, -e1_, -e2_, -e3_); }
		//  A dual operation takes a k-vector and returns a (4-k)-vector
		//      A reverse dual operation inverts the dual operation
		//      dual(X,Y) is not safe for X=Y (same with revdual)
		Ext4_3 dual() const;
		Ext4_3 reverse_dual() const;
		//  Join takes a j-vector and a k-vector and returns a (j+k) vector
		//      Join is the wedge product.
		Ext4_3 join(const Ext4_2& rhs) const;
		Ext4_2 join(const Ext4_1& rhs) const;
	private:
		Ext4_1(cfloat e0, cfloat e1, cfloat e2, cfloat e3) : Ext4_1Base(e0, e1, e2, e3) {};
		friend class Ext4_2;
		friend class Ext4_3;
		friend class AbsExt4_1;
	};

	class Ext4_2 : public Ext4_2Base
	{
	public:
		Ext4_2(const Ext4_2& ext_to_copy) : Ext4_2Base(ext_to_copy) {}
		Ext4_2(Ext4_2&& ext_to_move) : Ext4_2Base(ext_to_move) {}
		Ext4_2& operator=(const Ext4_2& ext_to_copy) = default;
		Ext4_2& operator=(Ext4_2&& ext_to_move) = default;
		//  Negation
		Ext4_2& negate()
		{
			e01_ = -e01_;
			e02_ = -e02_;
			e03_ = -e03_;
			e12_ = -e12_;
			e13_ = -e13_;
			e23_ = -e23_;
			return *this;
		}
		Ext4_2 negative() const { return Ext4_2(-e01_, -e02_, -e03_, -e12_, -e13_, -e23_); }
		//  Dual and Reverse Dual
		Ext4_2 dual() const { return Ext4_2(e23_, -e13_, e12_, e03_, -e02_, e01_); }
		Ext4_2 reverse_dual() const { return Ext4_2(e23_, -e13_, e12_, e03_, -e02_, e01_); }
		//  Join
		Ext4_3 join(const Ext4_1& rhs) const;
		//  Meet
		Ext4_1 meet(const Ext4_3& rhs) const;
	private:
		Ext4_2() = default;
		Ext4_2(cfloat e01, cfloat e02, cfloat e03, cfloat e12, cfloat e13, cfloat e23)
			: Ext4_2Base(e01, e02, e03, e12, e13, e23)
		{
		}
		friend class Ext4_1;
		friend class AbsExt4_2;
	};

	class Ext4_3 : public Ext4_3Base
	{
	public:
		Ext4_3() = default;
		Ext4_3(const Ext4_3& ext_to_copy) : Ext4_3Base(ext_to_copy) {}
		Ext4_3(Ext4_3&& ext_to_move) : Ext4_3Base(ext_to_move) {}
		Ext4_3& operator=(const Ext4_3& ext_to_copy) = default;
		Ext4_3& operator=(Ext4_3&& ext_to_move) = default;
		//  Negation
		Ext4_3& negate()
		{
			e012_ = -e012_;
			e013_ = -e013_;
			e023_ = -e023_;
			e123_ = -e123_;
			return *this;
		}
		Ext4_3 negative() const { return Ext4_3(-e012_, -e013_, -e023_, -e123_); }
		//  Dual and reverse dual
		Ext4_1 dual() const { return Ext4_1(e123_, -e023_, e013_, -e012_); };
		Ext4_1 reverse_dual() const { return Ext4_1(-e123_, e023_, -e013_, e012_); }
		// A meet takes a j-vector and a k-vector and returns a (j+k-4)-vector
		Ext4_2 meet(const Ext4_3& rhs) const { return dual().join(rhs.dual()).reverse_dual(); }
		Ext4_1 meet(const Ext4_2& rhs) const { return dual().join(rhs.dual()).reverse_dual(); }
	private:
		Ext4_3(cfloat e012, cfloat e013, cfloat e023, cfloat e123) : Ext4_3Base(e012, e013, e023, e123) {}
		friend class Ext4_1;
		friend class Ext4_2;
		friend class AbsExt4_3;
	};
	// A dual operation takes a k-vector and returns a (4-k)-vector
	// A reverse dual operation inverts the dual operation
	// dual(X,Y) is not safe for X=Y (same with revdual)
	inline Ext4_3 Ext4_1::dual() const { return Ext4_3(e3_, -e2_, e1_, -e0_); }
	inline Ext4_3 Ext4_1::reverse_dual() const { return Ext4_3(-e3_, e2_, -e1_, e0_); }
	// A join takes a j-vector and a k-vector and returns a (j+k)-vector
	inline Ext4_2 Ext4_1::join(const Ext4_1& rhs) const
	{
		Ext4_2 out;

		out.e01_ = (e0_ * rhs.e1_) - (rhs.e0_ * e1_);
		out.e02_ = (e0_ * rhs.e2_) - (rhs.e0_ * e2_);
		out.e03_ = (e0_ * rhs.e3_) - (rhs.e0_ * e3_);
		out.e12_ = (e1_ * rhs.e2_) - (rhs.e1_ * e2_);
		out.e13_ = (e1_ * rhs.e3_) - (rhs.e1_ * e3_);
		out.e23_ = (e2_ * rhs.e3_) - (rhs.e2_ * e3_);

		return out;
	}
	inline Ext4_3 Ext4_1::join(const Ext4_2& rhs) const
	{
		// no negation since swapping the arguments requires two swaps of 1-vectors

		return rhs.join(*this);
	}
	inline Ext4_3 Ext4_2::join(const Ext4_1& rhs) const
	{
		Ext4_3 out;

		out.e012_ = (e01_ * rhs.e2_) - (e02_ * rhs.e1_) + (e12_ * rhs.e0_);
		out.e013_ = (e01_ * rhs.e3_) - (e03_ * rhs.e1_) + (e13_ * rhs.e0_);
		out.e023_ = (e02_ * rhs.e3_) - (e03_ * rhs.e2_) + (e23_ * rhs.e0_);
		out.e123_ = (e12_ * rhs.e3_) - (e13_ * rhs.e2_) + (e23_ * rhs.e1_);

		return out;
	}
	inline Ext4_1 Ext4_2::meet(const Ext4_3& rhs) const { return (dual().join(rhs.dual())).reverse_dual(); }
	//
	//  The AbsExt4_1 is just Ext4_1 with absolute values taken an no subtraction in operations.
	//      All values are positive all the time.
	//
	class AbsExt4_1 : public AbsExt4_1Base
	{
	public:
		AbsExt4_1() = default;
		AbsExt4_1(const AbsExt4_1& ext_to_copy) : AbsExt4_1Base(ext_to_copy) {}
		AbsExt4_1(AbsExt4_1&& ext_to_move) : AbsExt4_1Base(ext_to_move) {}
		explicit AbsExt4_1(const Ext4_1& element)
			: AbsExt4_1Base(fabs(element.e0()), fabs(element.e1()), fabs(element.e2()), fabs(element.e3()))
		{
		}
		explicit AbsExt4_1(Ext4_1&& element)
			: AbsExt4_1Base(fabs(element.e0()), fabs(element.e1()), fabs(element.e2()), fabs(element.e3()))
		{
		}
		AbsExt4_1& operator=(const AbsExt4_1& ext_to_copy) = default;
		AbsExt4_1& operator=(AbsExt4_1&& ext_to_move) = default;
		AbsExt4_1& operator=(const Ext4_1& element)
		{
			e0_ = fabs(element.e0());
			e1_ = fabs(element.e1());
			e2_ = fabs(element.e2());
			e3_ = fabs(element.e3());

			return *this;
		}
		AbsExt4_1& operator=(Ext4_1&& element)
		{
			e0_ = fabs(element.e0());
			e1_ = fabs(element.e1());
			e2_ = fabs(element.e2());
			e3_ = fabs(element.e3());

			return *this;
		}
		operator cvector3d() const
		{
			cvector3d vec(e0_, e1_, e2_);
			vec /= e3_;
			return vec;
		}
		//  Negation does not change anything for the AbsExt classes, it is a no-op.
		AbsExt4_1& negate() { return *this; }
		AbsExt4_1 negative() const { return AbsExt4_1(*this); }
		// A dual operation takes a k-vector and returns a (4-k)-vector
		// A reverse dual operation inverts the dual operation
		// dual(X,Y) is not safe for X=Y (same with revdual)
		AbsExt4_3 dual() const;
		AbsExt4_3 reverse_dual() const;
		// A join takes a j-vector and a k-vector and returns a (j+k)-vector
		AbsExt4_2 join(const AbsExt4_1& rhs) const;
		AbsExt4_3 join(const AbsExt4_2& rhs) const;
	private:
		AbsExt4_1(cfloat e0, cfloat e1, cfloat e2, cfloat e3) : AbsExt4_1Base(e0, e1, e2, e3) {}
		friend class AbsExt4_3;
	};

	class AbsExt4_2 : public AbsExt4_2Base
	{
	public:
		AbsExt4_2() = default;
		AbsExt4_2(const AbsExt4_2& ext_to_copy) : AbsExt4_2Base(ext_to_copy) {}
		AbsExt4_2(AbsExt4_2&& ext_to_move) : AbsExt4_2Base(ext_to_move) {}
		explicit AbsExt4_2(Ext4_2& ext_to_abs)
			: AbsExt4_2Base(fabs(ext_to_abs.e01()), fabs(ext_to_abs.e02()), fabs(ext_to_abs.e03()),
				fabs(ext_to_abs.e12()), fabs(ext_to_abs.e13()), fabs(ext_to_abs.e23()))
		{
		}
		AbsExt4_2& operator=(const AbsExt4_2& ext_to_copy) = default;
		AbsExt4_2& operator=(AbsExt4_2&& ext_to_move) = default;
		//  Negation does not change anything for the AbsExt classes
		AbsExt4_2& negate() { return *this; }
		AbsExt4_2 negative() const { return AbsExt4_2(*this); }
		// A dual operation takes a k-vector and returns a (4-k)-vector
		// A reverse dual operation inverts the dual operation
		// dual(X,Y) is not safe for X=Y (same with revdual)
		AbsExt4_2 dual() const { return AbsExt4_2(e23_, e13_, e12_, e03_, e02_, e01_); }
		AbsExt4_2 reverse_dual() const { return AbsExt4_2(e23_, e13_, e12_, e03_, e02_, e01_); }
		AbsExt4_3 join(const AbsExt4_1& rhs) const;
		AbsExt4_1 meet(const AbsExt4_3& rhs) const;
	private:
		AbsExt4_2(cfloat e01, cfloat e02, cfloat e03, cfloat e12, cfloat e13, cfloat e23)
			: AbsExt4_2Base(e01, e02, e03, e12, e13, e23)
		{
		}
		friend class AbsExt4_1;
	};

	class AbsExt4_3 : public AbsExt4_3Base
	{
	public:
		AbsExt4_3() = default;
		AbsExt4_3(const AbsExt4_3& ext_to_copy) : AbsExt4_3Base(ext_to_copy) {}
		AbsExt4_3(AbsExt4_3&& ext_to_move) : AbsExt4_3Base(ext_to_move) {}
		explicit AbsExt4_3(const Ext4_3& ext_to_abs)
			: AbsExt4_3Base(fabs(ext_to_abs.e012()), fabs(ext_to_abs.e013()), fabs(ext_to_abs.e023()),
				fabs(ext_to_abs.e123()))
		{
		}
		AbsExt4_3& operator=(const AbsExt4_3& ext_to_copy) = default;
		AbsExt4_3& operator=(AbsExt4_3&& ext_to_move) = default;
		//  Negation does not change anything for the AbsExt classes
		AbsExt4_3& negate() { return *this; }
		AbsExt4_3 negative() const { return AbsExt4_3(*this); }
		// A dual operation takes a k-vector and returns a (4-k)-vector
		// A reverse dual operation inverts the dual operation
		// dual(X,Y) is not safe for X=Y (same with revdual)
		//
		//  Dual and Reverse Dual are identical for the Abs... classes.
		AbsExt4_1 dual() const { return AbsExt4_1(e123_, e023_, e013_, e012_); }
		AbsExt4_1 reverse_dual() const { return AbsExt4_1(e123_, e023_, e013_, e012_); }
		// A meet takes a j-vector and a k-vector and returns a (j+k-4)-vector
		AbsExt4_2 meet(const AbsExt4_3& rhs) const { return (dual().join(rhs.dual())).reverse_dual(); }
		AbsExt4_1 meet(const AbsExt4_2& rhs) const { return (dual().join(rhs.dual())).reverse_dual(); }
	private:
		AbsExt4_3(cfloat e012, cfloat e013, cfloat e023, cfloat e123) : AbsExt4_3Base(e012, e013, e023, e123) {}

		friend class AbsExt4_1;
		friend class AbsExt4_2;
	};
	// A dual operation takes a k-vector and returns a (4-k)-vector
	// A reverse dual operation inverts the dual operation
	// dual(X,Y) is not safe for X=Y (same with revdual)
	inline AbsExt4_3 AbsExt4_1::dual() const { return AbsExt4_3(e3_, e2_, e1_, e0_); }
	inline AbsExt4_3 AbsExt4_1::reverse_dual() const { return AbsExt4_3(e3_, e2_, e1_, e0_); }
	inline AbsExt4_2 AbsExt4_1::join(const AbsExt4_1& rhs) const
	{
		AbsExt4_2 result;

		result.e01_ = (e0_ * rhs.e1_) + (rhs.e0_ * e1_);
		result.e02_ = (e0_ * rhs.e2_) + (rhs.e0_ * e2_);
		result.e03_ = (e0_ * rhs.e3_) + (rhs.e0_ * e3_);
		result.e12_ = (e1_ * rhs.e2_) + (rhs.e1_ * e2_);
		result.e13_ = (e1_ * rhs.e3_) + (rhs.e1_ * e3_);
		result.e23_ = (e2_ * rhs.e3_) + (rhs.e2_ * e3_);

		return result;
	}
	inline AbsExt4_3 AbsExt4_2::join(const AbsExt4_1& rhs) const
	{
		AbsExt4_3 result;

		result.e012_ = (e01_ * rhs.e2()) + (e02_ * rhs.e1()) + (e12_ * rhs.e0());
		result.e013_ = (e01_ * rhs.e3()) + (e03_ * rhs.e1()) + (e13_ * rhs.e0());
		result.e023_ = (e02_ * rhs.e3()) + (e03_ * rhs.e2()) + (e23_ * rhs.e0());
		result.e123_ = (e12_ * rhs.e3()) + (e13_ * rhs.e2()) + (e23_ * rhs.e1());

		return result;
	}
	inline AbsExt4_3 AbsExt4_1::join(const AbsExt4_2& rhs) const { return rhs.join(*this); }
	// A meet takes a j-vector and a k-vector and returns a (j+k-4)-vector
	inline AbsExt4_1 AbsExt4_2::meet(const AbsExt4_3& rhs) const { return (dual().join(rhs.dual())).reverse_dual(); }

}

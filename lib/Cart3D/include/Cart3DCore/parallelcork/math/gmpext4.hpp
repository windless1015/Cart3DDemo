// +-------------------------------------------------------------------------
// | gmpext4.h
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

/*
#ifdef _WIN32
#pragma warning(disable: 4800)
#pragma warning(disable: 4244)
#pragma warning(disable: 4146)
#include <mpirxx.h>
#pragma warning(default: 4146)
#pragma warning(default: 4244)
#pragma warning(default: 4800)
#else
#include <gmpxx.h>
#endif
*/

#include <mpirxx.h>
#include <math/ext4_base.hpp>
#include <math/quantization.h>

namespace Cart3D
{
	class GMPExt4_2;
	class GMPExt4_3;

	using GMPExt4_1Base = Bases::Ext4_1Base<mpz_class>;
	using GMPExt4_2Base = Bases::Ext4_2Base<mpz_class>;
	using GMPExt4_3Base = Bases::Ext4_3Base<mpz_class>;

	class GMPExt4_1 : public GMPExt4_1Base
	{
	public:
		GMPExt4_1(const GMPExt4_1& ext_to_copy) : GMPExt4_1Base(ext_to_copy) {}
		GMPExt4_1(GMPExt4_1&& ext_to_move) :GMPExt4_1Base(ext_to_move){}
		GMPExt4_1() :GMPExt4_1Base() {}
		GMPExt4_1& operator=(const GMPExt4_1& that) {
			if (this != &that) {
				e0_ = that.e0_;
				e1_ = that.e1_;
				e2_ = that.e2_;
				e3_ = that.e3_;
			}
			return *this;
		}

		explicit GMPExt4_1(const cvector3d& in, const Quantizer& quantizer)
		{
			e0_ = quantizer.quantize_to_int(in.x());
			e1_ = quantizer.quantize_to_int(in.y());
			e2_ = quantizer.quantize_to_int(in.z());
			e3_ = 1;
		}
		cvector3d operator()(const Quantizer& quantizer)
		{
			assert(e3_ != 0);  //  Trap any divisions by zero!

			return cvector3d(
				quantizer.reshrink(e0_.get_d() / e3_.get_d()),
				quantizer.reshrink(e1_.get_d() / e3_.get_d()),
				quantizer.reshrink(e2_.get_d() / e3_.get_d()));
		}
		// Negation takes a k-vector and returns its negation neg(X,Y) and is safe for X=Y
		const GMPExt4_1& negate()
		{
			e0_ = -e0_;
			e1_ = -e1_;
			e2_ = -e2_;
			e3_ = -e3_;

			return *this;
		}
		GMPExt4_1 negative() const { return GMPExt4_1(-e0_, -e1_, -e2_, -e3_); }
		//  A dual operation takes a k-vector and returns a (4-k)-vector
		//      A reverse dual operation inverts the dual operation
		//      dual(X,Y) is not safe for X=Y (same with revdual)
		GMPExt4_3 dual() const;
		GMPExt4_3 reverse_dual() const;
		//  Join takes a j-vector and a k-vector and returns a (j+k) vector
		//      Join is the wedge product.
		GMPExt4_3 join(const GMPExt4_2& rhs) const;
		GMPExt4_2 join(const GMPExt4_1& rhs) const;
	private:
		GMPExt4_1(mpz_class e0, mpz_class e1, mpz_class e2, mpz_class e3) :
			Ext4_1Base(e0, e1, e2, e3) 
		{};
		friend class GMPExt4_2;
		friend class GMPExt4_3;
	};

	class GMPExt4_2 : public GMPExt4_2Base
	{
	public:
		GMPExt4_2() :GMPExt4_2Base() {}
		GMPExt4_2(const GMPExt4_2& ext_to_copy) : GMPExt4_2Base(ext_to_copy) {}
		GMPExt4_2(GMPExt4_2&& ext_to_move) : GMPExt4_2Base(ext_to_move) {}
		//  Negation
		GMPExt4_2& negate()
		{
			e01_ = -e01_;
			e02_ = -e02_;
			e03_ = -e03_;
			e12_ = -e12_;
			e13_ = -e13_;
			e23_ = -e23_;
			return *this;
		}
		GMPExt4_2 negative() const {
			return GMPExt4_2(-e01_, -e02_, -e03_, -e12_, -e13_, -e23_);
		}
		//  Dual and Reverse Dual
		GMPExt4_2 dual() const { 
			return GMPExt4_2(e23_, -e13_, e12_, e03_, -e02_, e01_); 
		}
		GMPExt4_2 reverse_dual() const { 
			return GMPExt4_2(e23_, -e13_, e12_, e03_, -e02_, e01_);
		}
		//  Join
		GMPExt4_3 join(const GMPExt4_1& rhs) const;
		//  Meet
		GMPExt4_1 meet(const GMPExt4_3& rhs) const;
	private:
		GMPExt4_2(
			mpz_class e01, 
			mpz_class e02,
			mpz_class e03, 
			mpz_class e12, 
			mpz_class e13,
			mpz_class e23)
			: Ext4_2Base(e01, e02, e03, e12, e13, e23)
		{
		}
		friend class GMPExt4_1;
	};

	class GMPExt4_3 : public GMPExt4_3Base
	{
	public:
		GMPExt4_3():GMPExt4_3Base(){};
		GMPExt4_3(const GMPExt4_3& ext_to_copy) : GMPExt4_3Base(ext_to_copy) {}
		GMPExt4_3(GMPExt4_3&& ext_to_move) : GMPExt4_3Base(ext_to_move) {}
		GMPExt4_3& operator=(const GMPExt4_3&that) {
			if (this != &that) {
				e012_ = that.e012_;
				e013_ = that.e013_;
				e023_ = that.e023_;
				e123_ = that.e123_;
			}
			return *this;
		}

		//  Negation
		GMPExt4_3& negate()
		{
			e012_ = -e012_;
			e013_ = -e013_;
			e023_ = -e023_;
			e123_ = -e123_;
			return *this;
		}
		GMPExt4_3 negative() const { return GMPExt4_3(-e012_, -e013_, -e023_, -e123_); }
		//  Dual and reverse dual
		GMPExt4_1 dual() const { return GMPExt4_1(e123_, -e023_, e013_, -e012_); };
		GMPExt4_1 reverse_dual() const { return GMPExt4_1(-e123_, e023_, -e013_, e012_); }
		// A meet takes a j-vector and a k-vector and returns a (j+k-4)-vector
		GMPExt4_2 meet(const GMPExt4_3& rhs) const { return dual().join(rhs.dual()).reverse_dual(); }
		GMPExt4_1 meet(const GMPExt4_2& rhs) const { return dual().join(rhs.dual()).reverse_dual(); }
	private:
		GMPExt4_3(mpz_class e012, mpz_class e013, mpz_class e023, mpz_class e123) :
			Ext4_3Base(e012, e013, e023, e123)
		{
		}
		friend class GMPExt4_1;
		friend class GMPExt4_2;
	};

	// A dual operation takes a k-vector and returns a (4-k)-vector
	// A reverse dual operation inverts the dual operation
	// dual(X,Y) is not safe for X=Y (same with revdual)

	inline GMPExt4_3 GMPExt4_1::dual() const { 
		return GMPExt4_3(e3_, -e2_, e1_, -e0_);
	}

	inline GMPExt4_3 GMPExt4_1::reverse_dual() const {
		return GMPExt4_3(-e3_, e2_, -e1_, e0_); 
	}

	// A join takes a j-vector and a k-vector and returns a (j+k)-vector

	inline GMPExt4_2 GMPExt4_1::join(const GMPExt4_1& rhs) const
	{
		GMPExt4_2 out;
		out.e01_ = (e0_ * rhs.e1_) - (rhs.e0_ * e1_);
		out.e02_ = (e0_ * rhs.e2_) - (rhs.e0_ * e2_);
		out.e03_ = (e0_ * rhs.e3_) - (rhs.e0_ * e3_);
		out.e12_ = (e1_ * rhs.e2_) - (rhs.e1_ * e2_);
		out.e13_ = (e1_ * rhs.e3_) - (rhs.e1_ * e3_);
		out.e23_ = (e2_ * rhs.e3_) - (rhs.e2_ * e3_);
		return out;
	}

	inline GMPExt4_3 GMPExt4_1::join(const GMPExt4_2& rhs) const
	{
		// no negation since swapping the arguments requires two swaps of 1-vectors
		return rhs.join(*this);
	}

	inline GMPExt4_3 GMPExt4_2::join(const GMPExt4_1& rhs) const
	{
		GMPExt4_3 out;
		out.e012_ = (e01_ * rhs.e2_) - (e02_ * rhs.e1_) + (e12_ * rhs.e0_);
		out.e013_ = (e01_ * rhs.e3_) - (e03_ * rhs.e1_) + (e13_ * rhs.e0_);
		out.e023_ = (e02_ * rhs.e3_) - (e03_ * rhs.e2_) + (e23_ * rhs.e0_);
		out.e123_ = (e12_ * rhs.e3_) - (e13_ * rhs.e2_) + (e23_ * rhs.e1_);
		return out;
	}

	inline GMPExt4_1 GMPExt4_2::meet(const GMPExt4_3& rhs) const { 
		return (dual().join(rhs.dual())).reverse_dual(); 
	}

}  

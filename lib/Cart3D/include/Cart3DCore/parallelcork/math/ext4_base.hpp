#pragma once
#include <Util/EigenUtil.h>
namespace Cart3D
{
	namespace Bases
	{
		template <typename T>
		class Ext4_1Base
		{
		public:
			virtual ~Ext4_1Base() {};

			T e0() const { return e0_; }
			T e1() const { return e1_; }
			T e2() const { return e2_; }
			T e3() const { return e3_; }

			T& operator[](size_t index)
			{
				return edata[index];
			}
			T operator[](size_t index) const
			{
				return edata[index];
			}

			bool operator==(const Ext4_1Base& r4_to_compare) const
			{
				return (
					(e0_ == r4_to_compare.e0_) && 
					(e1_ == r4_to_compare.e1_) && 
					(e2_ == r4_to_compare.e2_) &&
					(e3_ == r4_to_compare.e3_));
			}

			bool operator!=(const Ext4_1Base& r4_to_compare) const
			{
				return (
					(e0_ != r4_to_compare.e0_) || 
					(e1_ != r4_to_compare.e1_) ||
					(e2_ != r4_to_compare.e2_) ||
					(e3_ != r4_to_compare.e3_));
			}
			T inner(const Ext4_1Base& rhs) const
			{
				T acc = e0_ * rhs.e0_;
				acc += e1_ * rhs.e1_;
				acc += e2_ * rhs.e2_;
				acc += e3_ * rhs.e3_;

				return (acc);
			}

		protected:
			Ext4_1Base() {};

			Ext4_1Base(const Ext4_1Base<T>&that):
				e0_(that.e0_),
				e1_(that.e1_),
				e2_(that.e2_),
				e3_(that.e3_)
			{
			}


			Ext4_1Base(T e0, T e1, T e2, T e3) :
				e0_(e0),
				e1_(e1), 
				e2_(e2), 
				e3_(e3) 
			{};
			Ext4_1Base(const cvectort<T, 4>& array_to_copy): 
				e0_(array_to_copy[0]),
				e1_(array_to_copy[1]), 
				e2_(array_to_copy[2]), 
				e3_(array_to_copy[3])
			{}
			union {
				struct{
					T e0_;
					T e1_;
					T e2_;
					T e3_;
				};
				struct {
					T edata[4];
				};
			};
		};

		template <typename T>
		class Ext4_2Base
		{
		public:
			virtual ~Ext4_2Base(){}

			T& operator[](size_t index)
			{
				return edata[index];
			}
			T operator[](size_t index) const
			{
				return edata[index];
			}

			T e01() const { return e01_; }
			T e02() const { return e02_; }
			T e03() const { return e03_; }
			T e12() const { return e12_; }
			T e13() const { return e13_; }
			T e23() const { return e23_; }

			bool operator==(const Ext4_2Base& r4_to_compare) const
			{
				return (
					(e01_ == r4_to_compare.e01_) &&
					(e02_ == r4_to_compare.e02_) && 
					(e03_ == r4_to_compare.e03_) &&
					(e12_ == r4_to_compare.e12_) && 
					(e13_ == r4_to_compare.e13_) &&
					(e23_ == r4_to_compare.e23_));
			}

			bool operator!=(const Ext4_2Base& r4_to_compare) const
			{
				return (
					(e01_ != r4_to_compare.e01_) ||
					(e02_ != r4_to_compare.e02_) || 
					(e03_ != r4_to_compare.e03_) ||
					(e12_ != r4_to_compare.e12_) || 
					(e13_ != r4_to_compare.e13_) || 
					(e23_ != r4_to_compare.e23_));
			}

			// An inner product takes two k-vectors and produces a single number

			T inner(const Ext4_2Base& rhs) const
			{
				T acc = e01_ * rhs.e01_;
				acc += e02_ * rhs.e02_;
				acc += e03_ * rhs.e03_;
				acc += e12_ * rhs.e12_;
				acc += e13_ * rhs.e13_;
				acc += e23_ * rhs.e23_;

				return (acc);
			}

		protected:
			Ext4_2Base() {};

			Ext4_2Base(const Ext4_2Base<T>& that):
				e01_(that.e01_),
				e02_(that.e02_),
				e03_(that.e03_),
				e12_(that.e12_),
				e13_(that.e13_),
				e23_(that.e23_)
			{

			}
			Ext4_2Base(T e01, T e02, T e03, T e12, T e13, T e23): 
				e01_(e01),
				e02_(e02), 
				e03_(e03),
				e12_(e12),
				e13_(e13), 
				e23_(e23)
			{}

			union {
				struct {
					T e01_;
					T e02_;
					T e03_;
					T e12_;
					T e13_;
					T e23_;
				};
				struct {
					T edata[6];
				};
			};
		};

		template <typename T>
		class Ext4_3Base
		{
		public:
			virtual ~Ext4_3Base() {}

			T e012() const { return e012_; }
			T e013() const { return e013_; }
			T e023() const { return e023_; }
			T e123() const { return e123_; }

			T& operator[](size_t index)
			{
				return edata[index];
			}
			T operator[](size_t index) const
			{
				return edata[index];
			}

			bool operator==(const Ext4_3Base& r4_to_compare) const
			{
				return (
					(e012_ == r4_to_compare.e012_) &&
					(e013_ == r4_to_compare.e013_) &&
					(e023_ == r4_to_compare.e023_) && 
					(e123_ == r4_to_compare.e123_));
			}

			bool operator!=(const Ext4_3Base& r4_to_compare) const
			{
				return (
					(e012_ != r4_to_compare.e012_) || 
					(e013_ != r4_to_compare.e013_) ||
					(e023_ != r4_to_compare.e023_) ||
					(e123_ != r4_to_compare.e123_));
			}

			//  Dot product

			T inner(const Ext4_3Base& rhs) const
			{
				T acc = e012_ * rhs.e012_;
				acc += e013_ * rhs.e013_;
				acc += e023_ * rhs.e023_;
				acc += e123_ * rhs.e123_;

				return (acc);
			}

		protected:
			Ext4_3Base() {};
			Ext4_3Base(const Ext4_3Base<T>&that):
				e012_(that.e012_),
				e013_(that.e013_),
				e023_(that.e023_),
				e123_(that.e123_)
			{

			}
			Ext4_3Base(T e012, T e013, T e023, T e123) : 
				e012_(e012), 
				e013_(e013), 
				e023_(e023),
				e123_(e123)
			{}
			T e012_;
			T e013_;
			T e023_;
			T e123_;

			union {
				struct {
					T e012_;
					T e013_;
					T e023_;
					T e123_;
				};
				struct {
					T edata[4];
				};
			};
		};
	}  // namespace Bases

	using Ext4_1Base = Bases::Ext4_1Base<cfloat>;
	using AbsExt4_1Base = Bases::Ext4_1Base<cfloat>;

	using Ext4_2Base = Bases::Ext4_2Base<cfloat>;
	using AbsExt4_2Base = Bases::Ext4_2Base<cfloat>;

	using Ext4_3Base = Bases::Ext4_3Base<cfloat>;
	using AbsExt4_3Base = Bases::Ext4_3Base<cfloat>;

}  // namespace Cork::ExteriorCalculusR4

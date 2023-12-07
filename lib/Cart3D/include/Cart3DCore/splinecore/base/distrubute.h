#ifndef CART3D_DISTRUBUTE_H
#define CART3D_DISTRUBUTE_H

#include <Cart3DSplineCore.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
	class CART3D_SPLINECORE_CLASS DistrubuteUtil
	{
	public:
		/**
         * Compute the binomial coefficient (nCk) using the formula
         * \product_{i=0}^k (n + 1 - i) / i
         */
		static unsigned int binomial(unsigned int n, unsigned int k);
	public:
		/**
         * Check if two numbers are close enough within eps
         * @param[in] a First number
         * @param[in] b Second number
         * @param[in] eps Tolerance for checking closeness
         * @return Whether the numbers are close w.r.t. the tolerance
         */
		template <typename T>
		static inline bool close(T a, T b, double eps = std::numeric_limits<T>::epsilon())
		{
			return (std::abs(a - b) < eps) ? true : false;
		}

		/**
		 * Map numbers from one interval to another
		 * @param[in] val Number to map to another range
		 * @param[in] old_min Minimum value of original range
		 * @param[in] old_max Maximum value of original range
		 * @param[in] new_min Minimum value of new range
		 * @param[in] new_max Maximum value of new range
		 * @return Number mapped to new range
		 */
		template <typename T> 
		static inline T map_to_range(T val, T old_min, T old_max, T new_min, T new_max)
		{
			T old_range = old_max - old_min;
			T new_range = new_max - new_min;
			return (((val - old_min) * new_range) / old_range) + new_min;
		}
	};


}


#endif // !CART3D_DISTRUBUTE_H

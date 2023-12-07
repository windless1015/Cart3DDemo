#ifndef CART3D_TOOLS_CONJUGATEGRADIENT_H
#define CART3D_TOOLS_CONJUGATEGRADIENT_H

#include <Cart3DToolsDefine.h>
#include <Util/EigenUtil.h>
#include <unordered_map>


namespace Cart3D {

	class CGMSolver
	{
	public:
		static int solve_symmetric_cg(
			const std::unordered_map<std::uint64_t,cfloat>& A,
			const std::vector<cfloat>& B, 
			std::vector<cfloat>& X, int maxIterations, cfloat tolerance);
		static int solve_symmetric_cg(const std::vector<std::pair<std::uint64_t,cfloat>>& A,
			const std::vector<cfloat>& B,
			std::vector<cfloat>& X, int maxIterations, cfloat tolerance);
	};
}


#endif
#ifndef MMG_WRAPPER_H
#define MMG_WRAPPER_H

#include <wrapper/OptimMesh.h>


namespace Cart3D
{

	struct MmgOptions {

		bool angle_detection = true;
		double angle_value = 45.;
		double hausd = 0.01;
		double hsiz = 0.;
		double hmin = 0.1;
		double hmax = 2.;
		double hgrad = 1.105171;
		bool enable_anisotropy = false;
		bool optim = false;
		bool optimLES = false;
		bool opnbdy = true;
		bool noinsert = false;
		bool noswap = false;
		bool nomove = false;
		bool nosurf = false;
		bool close_debug_info = false;
		std::string metric_attribute = "no_metric";
		bool level_set = false;
		std::string ls_attribute = "no_ls";
		double ls_value = 0.;
	};

	bool  mmgs_tri_remesh(const OptimMesh& M, OptimMesh& M_out, const MmgOptions& opt = MmgOptions());

}
#endif


#ifndef CURVATURE_H
#define CURVATURE_H

#include <Util/EigenUtil.h>


namespace Cart3D
{
	//三角网格曲率度量
	bool CurvatureRusinkiewicz(
		const std::vector<int> &triangles, const std::vector<std::array<double, 3>> &nodes,
		std::vector<std::pair<std::array<double, 3>, std::array<double, 3>> > &nodalCurvatures);
	bool CurvatureRusinkiewicz(
		const std::vector<int> &triangles, const std::vector<std::array<double, 3>> &nodes,
		std::vector<std::pair<std::array<double, 3>, std::array<double, 3>> > &nodalCurvatures,
		std::vector<double> &nodeNormals);
}

#endif

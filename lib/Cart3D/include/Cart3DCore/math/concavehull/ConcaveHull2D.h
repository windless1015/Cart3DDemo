#ifndef CART3D_CONCAVE_HULL_2D_H
#define CART3D_CONCAVE_HULL_2D_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{

	class CART3D_MATH_CLASS ConcaveHull2D
	{
	public:
		/*
		 * @brief ���㰼��
		 * @detail 
		 * @param[in]         pts �㼯��
		 * @param[in]        hull ͹��
		 * @param[out]    concave ����
		 * @param[in]   concavity ��������
		 * @param[in] lengththres 
		 */
		static bool concaveman_hull(
			const std::vector<cvector2d>& pts,
			const std::vector<int>& hull,
			std::vector<int>& concave,
			cfloat concavity,cfloat lengththres);

		/*
		 * @brief ���㰼��
		 * @detail
		 * @param[in]         pts �㼯��
		 * @param[out]    concave ����
		 * @param[in]   concavity ��������
		 * @param[in] lengththres
		 */
		static bool concaveman_hull(
			const std::vector<cvector2d>& pts,
			std::vector<int>& concave,
			cfloat concavity, cfloat lengththres);
	};


}

#endif
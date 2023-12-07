#ifndef CART3D_TOOLS_FILLERWEIGHT_H
#define CART3D_TOOLS_FILLERWEIGHT_H


#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	class CART3D_TOOLS_CLASS FillerWeight
	{
	public:
		enum Option { ANGLE, AREA, MIX_ANGLE_AREA };
		FillerWeight();
	public:
		FillerWeight operator+(const FillerWeight & _other) const;
	public:
		bool operator<(const FillerWeight & _rhs) const;
	private:
		Option m_opt;
		cfloat m_area;
		cfloat m_angle;
	};

	struct CART3D_TOOLS_CLASS AreaAngleWeight
	{
		AreaAngleWeight(cfloat _angle = 180,
			cfloat _area = 0);
		AreaAngleWeight operator+(const AreaAngleWeight& _rhs) const;
		bool operator<(const AreaAngleWeight& _rhs) const;
		cfloat m_angle;
		cfloat m_area;
	};


	struct CART3D_TOOLS_CLASS ChordWeight
	{
		ChordWeight();
		ChordWeight(
			const cfloat& dihedral, const cfloat& area, 
			const int& optTri = -1, const cvector3d& optNormal = cvector3d::Zero());
		ChordWeight operator + (const ChordWeight& other) const;
		bool operator < (const ChordWeight& other) const;
		static ChordWeight super();
		cfloat m_dihedral; 
		cfloat m_area; 
		int m_optTri; 
		cvector3d m_optNormal; 
	};



}


#endif
#pragma once

#include <memory>

// cart3D
#include <Util/OpenMeshUtil.h>


/**
 * @brief 通过经纬度的方式来构建一个球体.
 */
class FoxPolyData;
class FoxSphereSource
{
public:
	FoxSphereSource();
	~FoxSphereSource();
	/// <summary>
	/// 设置圆的半径
	/// </summary>
	/// <param name="radius">半径</param>
	void setRadius(double radius);

	/// <summary>
	/// 设置圆心坐标
	/// </summary>
	/// <param name="x">坐标</param>
	/// <param name="y">坐标</param>
	/// <param name="z">坐标</param>
	void setCenter(double x,double y,double z);

	/// <summary>
	/// 设置球网格的纬度
	/// </summary>
	/// <param name="latitude">纬度</param>
	void setLatitude(int latitude);

	/// <summary>
	///  设置球体的网格经度
	/// </summary>
	/// <param name="logitude">经度</param>
	void setLongitude(int logitude);

	/// <summary>
	///  获取生成的球体网格
	/// </summary>
	/// <param name="mesh">网格</param>
	/// <returns>true 生成成功 false 生成失败</returns>
	bool getSphereMesh(Cart3D::OpenTriMesh &mesh);

	/// <summary>
	///  获取多边形数据
	/// </summary>
	/// <returns> 返回多边形数据FoxPolyData </returns>
	std::shared_ptr<FoxPolyData> getOutputPolyData();

private:
	double m_radius; // 半径
	Cart3D::OpenTriMesh::Point m_center; // 圆心
	Cart3D::OpenTriMesh m_mesh;// 网格
	int m_latitude;  // 球的纬度
	int m_longitude;  //  球的经度
	std::shared_ptr<FoxPolyData> m_polyData; // 多边形数据
};


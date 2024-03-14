#pragma once
#pragma once

#include <QVector3D>
//#include <QPoint>
#include <QSharedPointer>
#include <QList>

#include <QVector>
#include <QPointF>
#include"geometry/foxplane.h"
#include "rendering/foxactor.h"
#include "rendering/foxpolydata.h"


struct RegionsInfo
{
	int NumberOfRegion;		 // 一个整型变量,可能表示区域的总数。
	int* PtIdRegionRelation; // 一个整型指针,可能存储每个点与区域的对应关系
	int* RegionFlag;		 // 一个整型指针,可能标记每个区域的状态或属性
	int* PtNumsInRegion;	 // 一个整型指针,可能存储每个区域内点的数量
	QList<QString> SortList; // 可能用于存储排序后的字符串列表

	~RegionsInfo()
	{
		delete PtIdRegionRelation;
		delete RegionFlag;
		delete PtNumsInRegion;
	}
};

class FoxCommonMethod
{
public:
	FoxCommonMethod();
	~FoxCommonMethod();

	/**
	 * @brief 通过给定的点集拟合一个平面
	 * @param FittingPoints 用于拟合平面的点集
	 * @return 拟合出的平面
	 */
	static QSharedPointer<FoxPlane> cvFitPlane(QPointF* FittingPoints);

	/**
	 * @brief 在网格数据DataPd中找到与目标法向量TargetNormal夹角小于FindPointAngThreshold的点,
	 *        从这些点出发沿着单元格链接进行区域扩展,每遇到一个点就标记为已访问,当遇到与当前区域点法向量夹角大于CellTravelAngThreshold的点时停止扩展,得到一个区域。
	 *        重复上述过程直到所有符合FindPointAngThreshold条件的点都被遍历过,得到多个区域。
	 *        将得到的区域按区域内点数量从大到小排序,返回前biggestRegionNum个最大区域的点ID列表。
	 * @param DataPd 网格数据
	 * @param PointsColor 用于存储点颜色的数组
	 * @param TargetNormal 目标法向量
	 * @param FindPointAngThreshold 寻找符合条件点的夹角阈值
	 * @param CellTravelAngThreshold 单元格扩展的夹角阈值
	 * @param ToTopDistance 距离顶部的最大距离
	 * @param biggestRegionNum 需要返回的最大区域数量
	 * @return 包含前biggestRegionNum个最大区域的点ID列表
	 */
	static QSharedPointer<QVector<int>> FindBiggestRegionWithSameNormal(FoxPolyData* DataPd, QVector<int>* PointsColor, QVector3D TargetNormal, double FindPointAngThreshold, double CellTravelAngThreshold, double ToTopDistance = 99999, int biggestRegionNum = 1);

	/**
	 * @brief 在网格数据DataPd中找到与目标法向量TargetNormal夹角小于FindPointAngThreshold的点,
	 *        从这些点出发沿着单元格链接进行区域扩展,每遇到一个点就标记为已访问,当遇到与当前区域点法向量夹角大于CellTravelAngThreshold或距离中心点距离大于CircleDistanceFromCenterFilter的点时停止扩展,得到一个区域。
	 *        重复上述过程直到所有符合FindPointAngThreshold条件的点都被遍历过,得到多个区域。
	 *        将得到的区域按区域内点数量从大到小排序,返回前biggestRegionNum个最大区域的详细信息。
	 * @param DataPd 网格数据
	 * @param PointsColor 用于存储点颜色的数组
	 * @param TargetNormal 目标法向量
	 * @param FindPointAngThreshold 寻找符合条件点的夹角阈值
	 * @param CellTravelAngThreshold 单元格扩展的夹角阈值
	 * @param ToTopDistance 距离顶部的最大距离
	 * @param biggestRegionNum 需要返回的最大区域数量
	 * @param CircleDistanceFromCenterFilter 距离中心点的最大距离
	 * @return 包含前biggestRegionNum个最大区域详细信息的结构体
	 */
	static RegionsInfo* FindBiggestRegionWithSameNormal(FoxPolyData* DataPd, QVector<int>* PointsColor, QVector3D TargetNormal, double FindPointAngThreshold, double CellTravelAngThreshold, double ToTopDistance, int biggestRegionNum, double CircleDistanceFromCenterFilter);

	/**
	 * @brief 根据给定的点集创建一条线段
	 * @param Pts 用于创建线段的点集
	 * @param isClose 是否为闭合线段
	 * @return 创建的线段数据
	 */
	static QSharedPointer<FoxPolyData> CreateLinePolyData(QSharedPointer<QPointF> Pts, bool isClose);

	/**
	 * @brief 从ASCII文件中读取点数据
	 * @param path ASCII文件路径
	 * @param pts 用于存储读取的点数据的点集
	 */
	static void ReadPointsFromAscFile(std::string path, QPointF* pts);

	/**
	 * @brief 将点数据写入ASCII文件
	 * @param path ASCII文件路径
	 * @param pts 需要写入的点数据
	 */
	static void WritePointsInToAscFile(QString path, QPointF* pts);

	/**
	 * @brief 将点数据写入ASCII文件
	 * @param path ASCII文件路径
	 * @param pts 需要写入的点数据
	 */
	static void WritePointsInToAscFile(QString path, std::vector<QVector3D>* pts);

	/**
	 * @brief 将点数据写入文本文件
	 * @param path 文本文件路径
	 * @param points 需要写入的点数据
	 */
	static void WritePointsInToTxtFile(QString path, QPointF* points);

	/**
	 * @brief 将线段数据写入文本文件
	 * @param path 文本文件路径
	 * @param linePd 需要写入的线段数据
	 */
	static void WritepdInToTxtFile(QString path, FoxPolyData* linePd);

	/**
	 * @brief 计算两个向量之间的夹角
	 * @param v 向量1
	 * @param u 向量2
	 * @return 两个向量之间的夹角（弧度）
	 */
	static double AngleOfTwoVector(QVector3D v, QVector3D u);

	/**
	 * @brief 计算两个平面之间的夹角
	 * @param axisPt 轴线上一点
	 * @param axisDir 轴线方向
	 * @param plane1PtOffAxis 平面1上一离轴线点
	 * @param plane1Normal 平面1法向量
	 * @param plane2Normal 平面2法向量
	 * @return 两个平面之间的夹角（弧度）
	 */
	static double AngleOfTwoPlane(QVector3D axisPt, QVector3D axisDir, QVector3D plane1PtOffAxis, QVector3D plane1Normal, QVector3D plane2Normal);

	/**
	 * @brief 计算点到平面的距离
	 * @param Pt 点
	 * @param PonPlane 平面上一点
	 * @param planeNormal 平面法向量
	 * @return 点到平面的距离
	 */
	static double DistanceOfPointToPlane(QVector3D Pt, QVector3D PonPlane, QVector3D planeNormal);

	/**
	 * @brief 计算点到线段的距离
	 * @param Pt 点
	 * @param PA 线段起点
	 * @param PB 线段终点
	 * @return 点到线段的距离
	 */
	static double DistanceOfPointToLine(QVector3D Pt, QVector3D PA, QVector3D PB);

	/**
	 * @brief 创建一个圆盘平面
	 * @param centerPos 圆盘中心点
	 * @param planeNormal 平面法向量
	 * @param radius 圆盘半径
	 * @return 创建的圆盘平面数据
	 */
	static QSharedPointer<FoxPolyData> CreateDiskPlane(QVector3D centerPos, QVector3D planeNormal, double radius);

	/**
	 * @brief 创建一个球体
	 * @param x 球体中心点x坐标
	 * @param y 球体中心点y坐标
	 * @param z 球体中心点z坐标
	 * @param radius 球体半径
	 * @param r 球体颜色红色分量
	 * @param g 球体颜色绿色分量
	 * @param b 球体颜色蓝色分量
	 * @param Opacity 球体不透明度
	 * @return 创建的球体Actor
	 */
	static QSharedPointer<FoxActor> CreateSphere(double x, double y, double z, double radius, double r, double g, double b, double Opacity);

	/**
	 * @brief 计算线段与平面的交点
	 * @param planeVector 平面法向量
	 * @param planePoint 平面上一点
	 * @param lineVector 线段方向向量
	 * @param linePoint 线段上一点
	 * @param IntersectionPoint 输出参数，存储交点坐标
	 * @return 是否有交点
	 */
	static bool CalcIntersectionOfLineAdnPlane(QVector3D planeVector, QVector3D planePoint, QVector3D lineVector, QVector3D linePoint, QVector3D& IntersectionPoint);

	/**
	 * @brief 将牙齿ID转换为区域ID
	 * @param toothid 牙齿ID
	 * @return 区域ID
	 */
	static QString ToothIdToRegionId(int toothid);

	/**
	 * @brief 创建一条线段Actor
	 * @param startPoint 起点坐标
	 * @param endPoint 终点坐标
	 * @param radius 线段半径
	 * @param r 颜色红色分量
	 * @param g 颜色绿色分量
	 * @param b 颜色蓝色分量
	 * @param Opacity 不透明度
	 * @return 创建的线段Actor
	 */
	static QSharedPointer<FoxActor> CreateLine(QVector3D startPoint, QVector3D endPoint, double radius, double r, double g, double b, double Opacity);

	/**
	 * @brief 判断两个矩阵是否相等
	 * @param Matrix1 矩阵1
	 * @param Matrix2 矩阵2
	 * @return 是否相等
	 */
	static bool isMatrixEqual(QMatrix4x4* Matrix1, QMatrix4x4* Matrix2);

	/**
	 * @brief 根据给定的点集创建一条样条曲线
	 * @param points 用于创建样条曲线的点集
	 * @param splinePointCount 样条曲线上的点数
	 * @param isClose 是否为闭合曲线
	 * @return 创建的样条曲线数据
	 */
	static QSharedPointer<FoxPolyData> CreateSpline(QSharedPointer<QPointF> points, int splinePointCount, bool isClose);

	/**
	 * @brief 计算两点之间的距离
	 * @param p1 点1
	 * @param p2 点2
	 * @return 两点之间的距离
	 */
	static double DistanceOfTwoPoints(QVector3D p1, QVector3D p2);

	/**
	 * @brief 对线段上的点进行排序
	 * @param sortLine 需要排序的线段数据
	 */
	static void SortLinePoints(QSharedPointer<FoxPolyData> sortLine);

	/**
	 * @brief 对给定的点集进行邻域扩展
	 * @param meshPd 网格数据
	 * @param points 点集
	 * @param PtIdList 需要进行扩展的点ID列表
	 * @param LoopCount 扩展的层数
	 */
	static void PointsNeighborhood(QSharedPointer<FoxPolyData> meshPd, QPointF* points, QSharedPointer<QVector<int>> PtIdList, int LoopCount = 1);

	/**
	 * @brief 对给定的单元集进行邻域扩展
	 * @param meshPd 网格数据
	 * @param points 点集
	 * @param cellIdList 需要进行扩展的单元ID列表
	 * @param LoopCount 扩展的层数
	 */
	static void CellsNeighborhood(QSharedPointer<FoxPolyData> meshPd, QPointF* points, QSharedPointer<QVector<int>> cellIdList, int LoopCount = 1);

	/**
	 * @brief 删除指定路径下的文件夹及其内容
	 * @param path 文件夹路径
	 */
	static void DeleteDirectory(std::string path);

	/**
	 * @brief 判断文件是否存在
	 * @param name 文件路径
	 * @return 文件是否存在
	 */
	static bool IsFileExists(std::string& name);
};